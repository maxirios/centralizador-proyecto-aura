#include "mesh_lote.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

static const char *TAG = "mesh_lote";

static aura_lote_t s_lote;
static TickType_t s_lote_desde = 0;
static SemaphoreHandle_t s_lock_lote = NULL;
static mesh_lote_enviar_cb_t s_enviar_cb = NULL;
static TaskHandle_t s_tarea_handle = NULL;

static void tarea_lote(void *arg)
{
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(10));
        if (s_lock_lote && xSemaphoreTake(s_lock_lote, pdMS_TO_TICKS(5)) == pdTRUE) {
            if (s_lote.cantidad > 0 && (xTaskGetTickCount() - s_lote_desde) >= pdMS_TO_TICKS(MESH_LOTE_VENTANA_MS)) {
                ESP_LOGD(TAG, "Ventana de %d ms expirada: despachando lote de %u tramas (%u bytes)",
                         MESH_LOTE_VENTANA_MS, s_lote.cantidad, (unsigned)s_lote.largo);
                if (s_enviar_cb) {
                    if (!s_enviar_cb(s_lote.buf, s_lote.largo)) {
                        ESP_LOGW(TAG, "Fallo al enviar lote de %u tramas hacia la raiz", s_lote.cantidad);
                    }
                }
                aura_lote_vaciar(&s_lote);
            }
            xSemaphoreGive(s_lock_lote);
        }
    }
}

esp_err_t mesh_lote_init(mesh_lote_enviar_cb_t callback)
{
    if (s_lock_lote == NULL) {
        s_lock_lote = xSemaphoreCreateMutex();
        if (s_lock_lote == NULL) {
            ESP_LOGE(TAG, "Error creando mutex para lote");
            return ESP_ERR_NO_MEM;
        }
    }

    xSemaphoreTake(s_lock_lote, portMAX_DELAY);
    s_enviar_cb = callback;
    aura_lote_vaciar(&s_lote);
    s_lote_desde = 0;
    xSemaphoreGive(s_lock_lote);

    if (s_tarea_handle == NULL) {
        BaseType_t res = xTaskCreate(tarea_lote, "tarea_lote", 3072, NULL, 5, &s_tarea_handle);
        if (res != pdPASS) {
            ESP_LOGE(TAG, "Error iniciando tarea_lote");
            return ESP_FAIL;
        }
    }

    ESP_LOGI(TAG, "Modulo de lotes AURA inicializado (ventana: %d ms, max size: %d B)",
             MESH_LOTE_VENTANA_MS, AURA_LOTE_MAX);
    return ESP_OK;
}

void mesh_lote_flush(void)
{
    if (!s_lock_lote) return;
    xSemaphoreTake(s_lock_lote, portMAX_DELAY);
    if (s_lote.cantidad > 0) {
        ESP_LOGD(TAG, "Flush forzado de lote: %u tramas", s_lote.cantidad);
        if (s_enviar_cb) {
            if (!s_enviar_cb(s_lote.buf, s_lote.largo)) {
                ESP_LOGW(TAG, "Fallo al enviar lote forzado de %u tramas", s_lote.cantidad);
            }
        }
        aura_lote_vaciar(&s_lote);
    }
    xSemaphoreGive(s_lock_lote);
}

esp_err_t mesh_lote_agregar(const uint8_t mac[6], const uint8_t *trama, size_t largo, bool prioritario)
{
    if (!s_lock_lote) return ESP_ERR_INVALID_STATE;
    if (trama == NULL || largo == 0 || largo > AURA_TRAMA_MAX) {
        return ESP_ERR_INVALID_ARG;
    }

    xSemaphoreTake(s_lock_lote, portMAX_DELAY);
    if (s_lote.cantidad == 0) {
        s_lote_desde = xTaskGetTickCount();
    }

    bool cabe = aura_lote_agregar(&s_lote, mac, trama, largo);
    if (!cabe) {
        /* Si no entra en el lote actual, despachamos el que hay y creamos uno nuevo */
        if (s_lote.cantidad > 0 && s_enviar_cb) {
            s_enviar_cb(s_lote.buf, s_lote.largo);
        }
        aura_lote_vaciar(&s_lote);
        s_lote_desde = xTaskGetTickCount();
        aura_lote_agregar(&s_lote, mac, trama, largo);
    }

    /* Si es prioritario, no esperamos a la ventana de 50 ms */
    if (prioritario && s_lote.cantidad > 0) {
        if (s_enviar_cb) {
            s_enviar_cb(s_lote.buf, s_lote.largo);
        }
        aura_lote_vaciar(&s_lote);
    }

    xSemaphoreGive(s_lock_lote);
    return ESP_OK;
}

uint8_t mesh_lote_cantidad_actual(void)
{
    uint8_t cant = 0;
    if (s_lock_lote && xSemaphoreTake(s_lock_lote, pdMS_TO_TICKS(10)) == pdTRUE) {
        cant = s_lote.cantidad;
        xSemaphoreGive(s_lock_lote);
    }
    return cant;
}
