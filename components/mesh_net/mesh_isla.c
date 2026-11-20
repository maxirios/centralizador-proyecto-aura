#include "mesh_isla.h"
#include <string.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_mesh.h"
#include "esp_attr.h"
#include "esp_system.h"
#include "esp_mac.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "mesh_isla";
static const char *NVS_NAMESPACE = "concentrador";
static const char *NVS_KEY_CANAL = "canal";

static volatile bool s_isla_activa = false;
static volatile bool s_salir_pendiente = false;
static uint8_t s_canal_isla = 0;
static uint8_t s_canal_conocido = 0;
static volatile TickType_t s_sin_padre_desde = 0;
static uint8_t s_mesh_id[6] = {0};
static TaskHandle_t s_tarea_handle = NULL;
static mesh_isla_estado_cb_t s_estado_cb = NULL;

static void canal_guardar(uint8_t canal)
{
    if (canal == 0 || canal == s_canal_conocido) {
        return;
    }
    s_canal_conocido = canal;
    nvs_handle_t h;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &h) == ESP_OK) {
        nvs_set_u8(h, NVS_KEY_CANAL, canal);
        nvs_commit(h);
        nvs_close(h);
        ESP_LOGI(TAG, "Canal de malla guardado en NVS: %u", canal);
    }
}

static void isla_buscar_gateway(bool todos_los_canales)
{
    wifi_scan_config_t sc = {
        .show_hidden = true,
        .scan_type = WIFI_SCAN_TYPE_PASSIVE,
        .scan_time.passive = 600,
        .channel = todos_los_canales ? 0 : s_canal_isla,
    };
    esp_wifi_scan_stop();
    esp_err_t err = esp_wifi_scan_start(&sc, false);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Isla: fallo al iniciar escaneo Wi-Fi: %s", esp_err_to_name(err));
    }
}

static esp_err_t conmutar_malla(bool activar_isla)
{
    mesh_cfg_t cfg;
    esp_err_t err = esp_mesh_get_config(&cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "No se pudo leer config de malla: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGW(TAG, "Conmutando malla en caliente a %s...",
             activar_isla ? "MODO ISLA (MESH_ROOT)" : "MODO NORMAL (MESH_IDLE)");

    err = esp_mesh_stop();
    if (err != ESP_OK && err != ESP_ERR_MESH_NOT_START) {
        ESP_LOGE(TAG, "Error en esp_mesh_stop: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_mesh_deinit();
    if (err != ESP_OK && err != ESP_ERR_MESH_NOT_INIT) {
        ESP_LOGE(TAG, "Error en esp_mesh_deinit: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_mesh_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error en esp_mesh_init: %s", esp_err_to_name(err));
        return err;
    }

    esp_mesh_fix_root(true);
    esp_mesh_set_max_layer(6);
    esp_mesh_disable_ps();
    esp_mesh_set_ap_authmode(WIFI_AUTH_WPA2_PSK);

    if (activar_isla) {
        uint8_t canal = s_canal_conocido ? s_canal_conocido : 1;
        s_canal_isla = canal;
        s_isla_activa = true;
        s_salir_pendiente = false;
        s_sin_padre_desde = 0;

        const char *router = MESH_ROUTER_ISLA;
        cfg.router.ssid_len = strlen(router);
        memset(cfg.router.ssid, 0, sizeof(cfg.router.ssid));
        memcpy(cfg.router.ssid, router, cfg.router.ssid_len);
        cfg.channel = canal;
        cfg.allow_channel_switch = false;

        err = esp_mesh_set_type(MESH_ROOT);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error en esp_mesh_set_type(MESH_ROOT): %s", esp_err_to_name(err));
        }
    } else {
        s_isla_activa = false;
        s_salir_pendiente = false;
        s_canal_isla = 0;
        s_sin_padre_desde = xTaskGetTickCount() | 1;

        const char *router = "aura-sin-router";
        cfg.router.ssid_len = strlen(router);
        memset(cfg.router.ssid, 0, sizeof(cfg.router.ssid));
        memcpy(cfg.router.ssid, router, cfg.router.ssid_len);
        cfg.channel = 0;
        cfg.allow_channel_switch = true;

        err = esp_mesh_set_type(MESH_IDLE);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error en esp_mesh_set_type(MESH_IDLE): %s", esp_err_to_name(err));
        }
    }

    err = esp_mesh_set_config(&cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error en esp_mesh_set_config: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_mesh_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error en esp_mesh_start: %s", esp_err_to_name(err));
        return err;
    }

    if (!activar_isla) {
        esp_mesh_set_self_organized(true, true);
    }

    if (s_estado_cb) {
        s_estado_cb(s_isla_activa, mesh_isla_get_canal());
    }
    return ESP_OK;
}

void mesh_isla_entrar(void)
{
    uint8_t canal = s_canal_conocido ? s_canal_conocido : 1;
    ESP_LOGW(TAG, "%d s sin raiz: conmutando en caliente a MODO ISLA (canal %u)",
             MESH_ISLA_TRAS_S, canal);
    conmutar_malla(true);
}

void mesh_isla_salir(void)
{
    ESP_LOGW(TAG, "Volvio el gateway: solicitando retorno en caliente a modo normal");
    s_salir_pendiente = true;
}

void mesh_isla_procesar_escaneo(int num_aps)
{
    if (!s_isla_activa) {
        return;
    }
    mesh_assoc_t assoc;
    wifi_ap_record_t rec;
    int ie_len = 0;
    bool gateway = false;
    for (int i = 0; i < num_aps; i++) {
        esp_mesh_scan_get_ap_ie_len(&ie_len);
        esp_mesh_scan_get_ap_record(&rec, &assoc);
        if (ie_len == sizeof(assoc) && assoc.layer == 1 && memcmp(assoc.mesh_id, s_mesh_id, 6) == 0) {
            ESP_LOGI(TAG, "Isla: detectada raiz de la malla en " MACSTR " (canal %d)",
                     MAC2STR(rec.bssid), rec.primary);
            gateway = true;
        }
    }
    esp_mesh_flush_scan_result();
    if (gateway) {
        mesh_isla_salir();
    }
}

static void tarea_monitoreo_isla(void *arg)
{
    int vueltas = 0;
    TickType_t ultimo_escaneo = 0;
    while (true) {
        if (s_isla_activa) {
            if (s_salir_pendiente) {
                conmutar_malla(false);
                vueltas = 0;
                ultimo_escaneo = 0;
                continue;
            }
            TickType_t ahora = xTaskGetTickCount();
            if (ultimo_escaneo == 0 || (ahora - ultimo_escaneo) >= pdMS_TO_TICKS(MESH_ISLA_REVISAR_S * 1000)) {
                ultimo_escaneo = ahora;
                bool todos = (++vueltas * MESH_ISLA_REVISAR_S >= MESH_ISLA_REVISAR_TODO_S);
                if (todos) {
                    vueltas = 0;
                }
                isla_buscar_gateway(todos);
            }
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            vTaskDelay(pdMS_TO_TICKS(1000));
            TickType_t desde = s_sin_padre_desde;
            if (desde != 0 && s_canal_conocido != 0) {
                TickType_t ahora = xTaskGetTickCount();
                if (ahora - desde >= pdMS_TO_TICKS(MESH_ISLA_TRAS_S * 1000)) {
                    mesh_isla_entrar();
                }
            }
        }
    }
}

esp_err_t mesh_isla_init(const uint8_t mesh_id[6])
{
    if (mesh_id) {
        memcpy(s_mesh_id, mesh_id, 6);
    }

    nvs_handle_t h;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &h) == ESP_OK) {
        nvs_get_u8(h, NVS_KEY_CANAL, &s_canal_conocido);
        nvs_close(h);
    }

    s_isla_activa = false;
    s_salir_pendiente = false;
    s_canal_isla = 0;
    s_sin_padre_desde = xTaskGetTickCount() | 1;

    if (s_tarea_handle == NULL) {
        BaseType_t res = xTaskCreate(tarea_monitoreo_isla, "mesh_isla", 4096, NULL, 3, &s_tarea_handle);
        if (res != pdPASS) {
            ESP_LOGE(TAG, "Error creando tarea de monitoreo de isla");
            return ESP_FAIL;
        }
    }

    return ESP_OK;
}

void mesh_isla_set_estado_cb(mesh_isla_estado_cb_t cb)
{
    s_estado_cb = cb;
}

bool mesh_isla_esta_activa(void)
{
    return s_isla_activa;
}

uint8_t mesh_isla_get_canal(void)
{
    return s_isla_activa ? s_canal_isla : s_canal_conocido;
}

void mesh_isla_notificar_padre_conectado(uint8_t canal)
{
    s_sin_padre_desde = 0;
    canal_guardar(canal);
}

void mesh_isla_notificar_padre_desconectado(void)
{
    if (!s_isla_activa && s_sin_padre_desde == 0) {
        s_sin_padre_desde = xTaskGetTickCount() | 1;
        ESP_LOGW(TAG, "Desconectado del padre, iniciando temporizador de modo isla (%d s)", MESH_ISLA_TRAS_S);
    }
}
