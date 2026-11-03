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

#define RTC_ISLA_MAGIC 0x49534C41u

static RTC_NOINIT_ATTR uint32_t s_rtc_isla;
static RTC_NOINIT_ATTR uint8_t s_rtc_canal_isla;

static bool s_isla_activa = false;
static uint8_t s_canal_isla = 0;
static uint8_t s_canal_conocido = 0;
static volatile TickType_t s_sin_padre_desde = 0;
static uint8_t s_mesh_id[6] = {0};
static TaskHandle_t s_tarea_handle = NULL;

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

void mesh_isla_entrar(void)
{
    uint8_t canal = s_canal_conocido ? s_canal_conocido : 1;
    ESP_LOGW(TAG, "%d s sin raiz: me reinicio como raiz de la isla del aula (canal %u)",
             MESH_ISLA_TRAS_S, canal);
    s_rtc_isla = RTC_ISLA_MAGIC;
    s_rtc_canal_isla = canal;
    vTaskDelay(pdMS_TO_TICKS(200));
    esp_restart();
}

void mesh_isla_salir(void)
{
    ESP_LOGW(TAG, "Volvio el gateway: me reinicio en modo normal");
    s_rtc_isla = 0;
    s_rtc_canal_isla = 0;
    vTaskDelay(pdMS_TO_TICKS(200));
    esp_restart();
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
    while (true) {
        if (s_isla_activa) {
            vTaskDelay(pdMS_TO_TICKS(MESH_ISLA_REVISAR_S * 1000));
            bool todos = (++vueltas * MESH_ISLA_REVISAR_S >= MESH_ISLA_REVISAR_TODO_S);
            if (todos) {
                vueltas = 0;
            }
            isla_buscar_gateway(todos);
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

    s_isla_activa = (s_rtc_isla == RTC_ISLA_MAGIC && s_rtc_canal_isla >= 1 && s_rtc_canal_isla <= 13);
    if (s_isla_activa) {
        s_canal_isla = s_rtc_canal_isla;
        ESP_LOGW(TAG, "Iniciando en MODO ISLA (canal %u, sin gateway)", s_canal_isla);
    } else {
        s_rtc_isla = 0;
        s_canal_isla = 0;
        s_sin_padre_desde = xTaskGetTickCount() | 1;
    }

    if (s_tarea_handle == NULL) {
        BaseType_t res = xTaskCreate(tarea_monitoreo_isla, "mesh_isla", 3072, NULL, 3, &s_tarea_handle);
        if (res != pdPASS) {
            ESP_LOGE(TAG, "Error creando tarea de monitoreo de isla");
            return ESP_FAIL;
        }
    }

    return ESP_OK;
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
