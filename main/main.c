#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mesh_net.h"

#if __has_include("config_local.h")
#include "config_local.h"
#else
#define CONFIG_MESH_ID_BYTES 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc
#ifndef CONFIG_MESH_AP_PASSWORD
#define CONFIG_MESH_AP_PASSWORD "clave-mesh-aura"
#endif
#ifndef CONFIG_MESH_AULA_DEFECTO
#define CONFIG_MESH_AULA_DEFECTO "aula1"
#endif
#endif

static const char *TAG = "CENTRALIZADOR_APP";

static void on_telemetria_recibida(const uint8_t mac[6], const char *hw_id, const char *values_json, uint64_t ts_ms)
{
    ESP_LOGI(TAG, "[UI_FEED] Telemetria de %s: %s (ts=%llu)", hw_id, values_json, ts_ms);
}

static void on_estado_malla(bool conectado_raiz, int cantidad_hijos)
{
    ESP_LOGI(TAG, "[RED_STATUS] Conectado a raiz: %s | Hojas activas: %d",
             conectado_raiz ? "SI" : "NO", cantidad_hijos);
}

static bool on_filtro_local(const uint8_t mac[6], const aura_trama_t *trama)
{
    /*
     * Hook preparado para logica propia local y horarios de uso asignados (Offline):
     * Permite actuar sobre actuadores de las hojas localmente segun el calendario
     * o filtrar/agregar muestras antes del reenvio a la nube.
     */
    return true;
}

static void tarea_interaccion_centralizador(void *arg)
{
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(15000));

        if (mesh_net_is_conectado()) {
            ESP_LOGI(TAG, "[CENTRALIZADOR] Operando normalmente en aula: '%s' | Hijos: %d",
                     mesh_net_get_aula(), mesh_net_get_hijos());
        } else {
            ESP_LOGW(TAG, "[CENTRALIZADOR] Esperando asociacion a nodo raiz...");
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando Centralizador de Aula (ESP32-S3 + ESP-MESH)...");

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    const uint8_t mesh_id[6] = {CONFIG_MESH_ID_BYTES};
    mesh_net_config_t net_cfg = {
        .mesh_password = CONFIG_MESH_AP_PASSWORD,
        .aula_por_defecto = CONFIG_MESH_AULA_DEFECTO,
        .max_capas = 6,
        .max_hijos = 6,
    };
    memcpy(net_cfg.mesh_id, mesh_id, 6);

    mesh_net_set_telemetria_cb(on_telemetria_recibida);
    mesh_net_set_estado_cb(on_estado_malla);
    mesh_net_set_filtro_local_cb(on_filtro_local);

    ESP_ERROR_CHECK(mesh_net_init(&net_cfg));
    ESP_ERROR_CHECK(mesh_net_start());

    xTaskCreate(tarea_interaccion_centralizador, "ui_coordinator", 3072, NULL, 3, NULL);
}
