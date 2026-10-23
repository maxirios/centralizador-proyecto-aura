#include "mesh_hora.h"
#include <sys/time.h>
#include <string.h>
#include "esp_log.h"
#include "esp_mac.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

static const char *TAG = "mesh_hora";

static mesh_hora_enviar_cb_t s_enviar_cb = NULL;
static SemaphoreHandle_t s_lock_hora = NULL;
static TaskHandle_t s_tarea_handle = NULL;
static uint16_t s_seq = 0;

uint64_t mesh_hora_ahora_ms(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) {
        return 0;
    }
    uint64_t ms = (uint64_t)tv.tv_sec * 1000 + (tv.tv_usec / 1000);
    return aura_hora_valida((uint32_t)(ms / 1000)) ? ms : 0;
}

bool mesh_hora_es_valida(void)
{
    return mesh_hora_ahora_ms() > 0;
}

void mesh_hora_ajustar(uint64_t ms_utc)
{
    uint32_t seg = (uint32_t)(ms_utc / 1000);
    if (!aura_hora_valida(seg)) {
        ESP_LOGW(TAG, "Rechazando ajuste con timestamp UTC invalido: %lu s", (unsigned long)seg);
        return;
    }

    bool primera = !mesh_hora_es_valida();
    struct timeval tv = {
        .tv_sec = (time_t)seg,
        .tv_usec = (suseconds_t)((ms_utc % 1000) * 1000),
    };
    settimeofday(&tv, NULL);

    if (primera) {
        ESP_LOGI(TAG, "Hora UTC sincronizada exitosamente con la raiz: %lu s", (unsigned long)seg);
    } else {
        ESP_LOGD(TAG, "Hora UTC actualizada: %lu s", (unsigned long)seg);
    }
}

static void solicitar_hora_a_raiz(void)
{
    if (!s_enviar_cb) {
        return;
    }

    aura_trama_t req;
    uint16_t seq = 0;
    if (s_lock_hora && xSemaphoreTake(s_lock_hora, pdMS_TO_TICKS(50)) == pdTRUE) {
        seq = s_seq++;
        xSemaphoreGive(s_lock_hora);
    }

    aura_hora_armar(&req, seq, 0);
    ESP_LOGD(TAG, "Solicitando hora UTC a la raiz (seq=%u)...", seq);
    s_enviar_cb(NULL, (const uint8_t *)&req, aura_trama_bytes(&req));
}

void mesh_hora_pedir_sincronizacion(void)
{
    if (s_tarea_handle) {
        xTaskNotifyGive(s_tarea_handle);
    } else {
        solicitar_hora_a_raiz();
    }
}

static void tarea_sincronizacion_hora(void *arg)
{
    while (true) {
        uint32_t espera_ms = mesh_hora_es_valida() ? MESH_HORA_RESYNC_MS : MESH_HORA_REINTENTO_MS;
        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(espera_ms));

        if (!mesh_hora_es_valida()) {
            solicitar_hora_a_raiz();
        }
    }
}

esp_err_t mesh_hora_init(mesh_hora_enviar_cb_t callback)
{
    if (s_lock_hora == NULL) {
        s_lock_hora = xSemaphoreCreateMutex();
        if (s_lock_hora == NULL) {
            ESP_LOGE(TAG, "Error creando mutex para mesh_hora");
            return ESP_ERR_NO_MEM;
        }
    }

    s_enviar_cb = callback;

    if (s_tarea_handle == NULL) {
        BaseType_t res = xTaskCreate(tarea_sincronizacion_hora, "mesh_hora", 3072, NULL, 5, &s_tarea_handle);
        if (res != pdPASS) {
            ESP_LOGE(TAG, "Error creando tarea mesh_hora");
            return ESP_FAIL;
        }
    }

    ESP_LOGI(TAG, "Modulo mesh_hora inicializado");
    return ESP_OK;
}

bool mesh_hora_procesar_trama(const uint8_t de_mac[6], const aura_trama_t *trama)
{
    if (!trama || !de_mac || trama->tipo != AURA_TIPO_HORA) {
        return false;
    }

    uint8_t mi_mac[6];
    if (esp_read_mac(mi_mac, ESP_MAC_WIFI_STA) == ESP_OK && memcmp(de_mac, mi_mac, 6) == 0) {
        return true;
    }

    if (trama->largo == sizeof(uint64_t)) {
        uint64_t ms_utc = aura_u64_leer(trama->payload);
        mesh_hora_ajustar(ms_utc);
        return true;
    }

    if (trama->largo == 0) {
        uint64_t ms_actual = mesh_hora_ahora_ms();
        if (ms_actual > 0) {
            aura_trama_t resp;
            uint16_t seq = 0;
            if (s_lock_hora && xSemaphoreTake(s_lock_hora, pdMS_TO_TICKS(50)) == pdTRUE) {
                seq = s_seq++;
                xSemaphoreGive(s_lock_hora);
            }

            aura_hora_armar(&resp, seq, ms_actual);
            if (s_enviar_cb) {
                s_enviar_cb(de_mac, (const uint8_t *)&resp, aura_trama_bytes(&resp));
                ESP_LOGI(TAG, "Hora UTC respondida localmente a " MACSTR " (%llu ms)",
                         MAC2STR(de_mac), (unsigned long long)ms_actual);
            }
            return true;
        } else {
            ESP_LOGW(TAG, "Peticion de hora de " MACSTR " recibida pero reloj local no sincronizado aun",
                     MAC2STR(de_mac));
            return false;
        }
    }

    return false;
}
