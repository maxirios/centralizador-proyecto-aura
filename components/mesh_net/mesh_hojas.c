#include "mesh_hojas.h"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "esp_mac.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

static const char *TAG = "mesh_hojas";
static const char *NVS_NAMESPACE = "concentrador";
static const char *NVS_KEY_HOJAS = "hojas";

static mesh_hoja_info_t s_hojas[MESH_HOJAS_MAX];
static int s_cant_hojas = 0;
static char s_aula[AURA_AULA_MAX] = {0};
static SemaphoreHandle_t s_lock = NULL;
static TaskHandle_t s_tarea_handle = NULL;
static mesh_hoja_evento_cb_t s_evento_cb = NULL;
static mesh_hoja_telemetria_cb_t s_telemetria_cb = NULL;

static void hojas_guardar_nvs(void)
{
    uint8_t macs[MESH_HOJAS_MAX][6];
    int n = 0;
    for (int i = 0; i < s_cant_hojas; i++) {
        if (s_hojas[i].aula[0] == '\0' || strcmp(s_hojas[i].aula, s_aula) == 0) {
            memcpy(macs[n++], s_hojas[i].mac, 6);
        }
    }
    nvs_handle_t h;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &h) == ESP_OK) {
        nvs_set_blob(h, NVS_KEY_HOJAS, macs, n * 6);
        nvs_commit(h);
        nvs_close(h);
    }
}

static void hojas_cargar_nvs(void)
{
    uint8_t macs[MESH_HOJAS_MAX][6];
    size_t tam = sizeof(macs);
    nvs_handle_t h;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &h) != ESP_OK) {
        return;
    }
    if (nvs_get_blob(h, NVS_KEY_HOJAS, macs, &tam) == ESP_OK) {
        int count = (int)(tam / 6);
        for (int k = 0; k < count && s_cant_hojas < MESH_HOJAS_MAX; k++) {
            mesh_hoja_info_t *x = &s_hojas[s_cant_hojas++];
            memset(x, 0, sizeof(*x));
            memcpy(x->mac, macs[k], 6);
            strlcpy(x->aula, s_aula, sizeof(x->aula));
            x->visto = xTaskGetTickCount();
            x->desconectada_desde = xTaskGetTickCount() | 1;
            x->intervalo_s = MESH_HOJAS_INTERVALO_DEFECTO_S;
        }
        ESP_LOGI(TAG, "Hojas del aula recuperadas de NVS: %d", s_cant_hojas);
    }
    nvs_close(h);
}

static mesh_hoja_info_t *hoja_buscar_o_crear(const uint8_t mac[6])
{
    for (int i = 0; i < s_cant_hojas; i++) {
        if (memcmp(s_hojas[i].mac, mac, 6) == 0) {
            return &s_hojas[i];
        }
    }
    if (s_cant_hojas >= MESH_HOJAS_MAX) {
        return NULL;
    }
    mesh_hoja_info_t *h = &s_hojas[s_cant_hojas++];
    memset(h, 0, sizeof(*h));
    memcpy(h->mac, mac, 6);
    h->visto = xTaskGetTickCount();
    h->desconectada_desde = 0;
    h->intervalo_s = MESH_HOJAS_INTERVALO_DEFECTO_S;
    h->ausente = false;
    strlcpy(h->aula, s_aula, sizeof(h->aula));

    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(mac, hw);
    ESP_LOGI(TAG, "Nueva hoja registrada: %s", hw);
    hojas_guardar_nvs();
    return h;
}

static void aprender_reporte(mesh_hoja_info_t *h, const char *json_txt)
{
    cJSON *root = cJSON_Parse(json_txt);
    if (!root) {
        return;
    }
    cJSON *cfg = cJSON_GetObjectItemCaseSensitive(root, "config");
    if (cfg) {
        cJSON *a = cJSON_GetObjectItemCaseSensitive(cfg, "aula");
        if (cJSON_IsString(a) && aura_aula_valida(a->valuestring)) {
            if (strcmp(h->aula, a->valuestring) != 0) {
                strlcpy(h->aula, a->valuestring, sizeof(h->aula));
                hojas_guardar_nvs();
            }
        }
        cJSON *iv = cJSON_GetObjectItemCaseSensitive(cfg, "intervalo_s");
        if (cJSON_IsNumber(iv) && iv->valueint > 0) {
            h->intervalo_s = (uint32_t)iv->valueint;
        }
    }
    cJSON_Delete(root);
}

static void revisar_ausentes(void)
{
    TickType_t ahora = xTaskGetTickCount();
    if (ahora < pdMS_TO_TICKS(MESH_HOJAS_GRACIA_ARRANQUE_MS)) {
        return;
    }
    if (xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return;
    }
    for (int i = 0; i < s_cant_hojas; i++) {
        mesh_hoja_info_t *x = &s_hojas[i];
        if (x->ausente || (x->aula[0] && strcmp(x->aula, s_aula) != 0)) {
            continue;
        }
        uint32_t iv = x->intervalo_s ? x->intervalo_s : MESH_HOJAS_INTERVALO_DEFECTO_S;
        const char *motivo = NULL;
        if (x->desconectada_desde && ahora - x->desconectada_desde >= pdMS_TO_TICKS(MESH_HOJAS_AUSENTE_MS)) {
            motivo = "se desconecto y no volvio";
        } else if (ahora - x->visto >= pdMS_TO_TICKS(3 * iv * 1000)) {
            motivo = "3 intervalos sin datos";
        }
        if (motivo) {
            x->ausente = true;
            char hw[AURA_HW_ID_BYTES];
            aura_hw_id_de_mac(x->mac, hw);
            ESP_LOGW(TAG, "Hoja %s AUSENTE (%s) en aula %s", hw, motivo, s_aula);
            if (s_evento_cb) {
                s_evento_cb(x->mac, true, motivo);
            }
        }
    }
    xSemaphoreGive(s_lock);
}

static void tarea_monitoreo_hojas(void *arg)
{
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(2000));
        revisar_ausentes();
    }
}

esp_err_t mesh_hojas_init(const char *aula, mesh_hoja_evento_cb_t evento_cb, mesh_hoja_telemetria_cb_t telemetria_cb)
{
    if (aula) {
        strlcpy(s_aula, aula, sizeof(s_aula));
    }
    s_evento_cb = evento_cb;
    s_telemetria_cb = telemetria_cb;

    if (s_lock == NULL) {
        s_lock = xSemaphoreCreateMutex();
        if (s_lock == NULL) {
            ESP_LOGE(TAG, "Error creando mutex para mesh_hojas");
            return ESP_ERR_NO_MEM;
        }
    }

    hojas_cargar_nvs();

    if (s_tarea_handle == NULL) {
        BaseType_t res = xTaskCreate(tarea_monitoreo_hojas, "mesh_hojas", 3072, NULL, 3, &s_tarea_handle);
        if (res != pdPASS) {
            ESP_LOGE(TAG, "Error creando tarea de monitoreo de hojas");
            return ESP_FAIL;
        }
    }

    ESP_LOGI(TAG, "Modulo mesh_hojas inicializado para aula '%s'", s_aula);
    return ESP_OK;
}

void mesh_hojas_set_aula(const char *nueva_aula)
{
    if (!nueva_aula || xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return;
    }
    strlcpy(s_aula, nueva_aula, sizeof(s_aula));
    s_cant_hojas = 0;
    hojas_guardar_nvs();
    xSemaphoreGive(s_lock);
}

void mesh_hojas_notificar_child_connected(const uint8_t mac[6])
{
    if (!mac || xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return;
    }
    mesh_hoja_info_t *h = hoja_buscar_o_crear(mac);
    if (h) {
        h->desconectada_desde = 0;
    }
    xSemaphoreGive(s_lock);
}

void mesh_hojas_notificar_child_disconnected(const uint8_t mac[6])
{
    if (!mac || xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return;
    }
    for (int i = 0; i < s_cant_hojas; i++) {
        if (memcmp(s_hojas[i].mac, mac, 6) == 0 && s_hojas[i].desconectada_desde == 0) {
            s_hojas[i].desconectada_desde = xTaskGetTickCount() | 1;
            char hw[AURA_HW_ID_BYTES];
            aura_hw_id_de_mac(mac, hw);
            ESP_LOGI(TAG, "Hoja desconectada del concentrador: %s", hw);
            break;
        }
    }
    xSemaphoreGive(s_lock);
}

bool mesh_hojas_procesar_trama(const uint8_t de_mac[6], const aura_trama_t *trama, bool *out_descartar_reenvio)
{
    if (out_descartar_reenvio) {
        *out_descartar_reenvio = false;
    }
    if (!trama || !de_mac) {
        return false;
    }

    if (xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return false;
    }

    mesh_hoja_info_t *h = hoja_buscar_o_crear(de_mac);
    if (!h) {
        xSemaphoreGive(s_lock);
        return false;
    }

    h->visto = xTaskGetTickCount();
    h->desconectada_desde = 0;
    if (h->ausente) {
        h->ausente = false;
        char hw[AURA_HW_ID_BYTES];
        aura_hw_id_de_mac(de_mac, hw);
        ESP_LOGI(TAG, "Hoja %s VOLVIO al aula %s", hw, s_aula);
        if (s_evento_cb) {
            s_evento_cb(de_mac, false, "volvio");
        }
    }

    if (trama->tipo == AURA_TIPO_REPORTE) {
        char txt[AURA_PAYLOAD_MAX + 1];
        size_t n = trama->largo < AURA_PAYLOAD_MAX ? trama->largo : AURA_PAYLOAD_MAX;
        memcpy(txt, trama->payload, n);
        txt[n] = '\0';
        aprender_reporte(h, txt);
    }

    size_t cab = (trama->tipo == AURA_TIPO_TELEMETRIA) ? AURA_TELEMETRIA_CABECERA : 4;
    if ((trama->tipo == AURA_TIPO_TELEMETRIA || trama->tipo == AURA_TIPO_ESTADO) && trama->largo >= cab) {
        uint32_t ts = aura_u32_leer(trama->payload + cab - 4);
        if (ts != 0 && h->ts_mostrado != 0 && ts < h->ts_mostrado) {
            ESP_LOGD(TAG, "Descartando telemetria obsoleta ts=%lu < ts_mostrado=%lu",
                     (unsigned long)ts, (unsigned long)h->ts_mostrado);
            if (trama->tipo == AURA_TIPO_ESTADO) {
                if (out_descartar_reenvio) {
                    *out_descartar_reenvio = true;
                }
            }
            xSemaphoreGive(s_lock);
            return true;
        }

        if (ts != 0) {
            h->ts_mostrado = ts;
        }

        char values[AURA_VALUES_MAX + 1];
        size_t n = trama->largo - cab;
        if (n > AURA_VALUES_MAX) {
            n = AURA_VALUES_MAX;
        }
        memcpy(values, trama->payload + cab, n);
        values[n] = '\0';

        char hw[AURA_HW_ID_BYTES];
        aura_hw_id_de_mac(de_mac, hw);
        ESP_LOGI(TAG, "Telemetria %s de %s: %s",
                 (trama->tipo == AURA_TIPO_ESTADO) ? "ESTADO" : "TELEMETRIA", hw, values);

        if (s_telemetria_cb) {
            s_telemetria_cb(de_mac, ts, values, (trama->tipo == AURA_TIPO_ESTADO));
        }
    }

    if (trama->tipo == AURA_TIPO_ESTADO) {
        if (out_descartar_reenvio) {
            *out_descartar_reenvio = true;
        }
    }

    xSemaphoreGive(s_lock);
    return true;
}

bool mesh_hojas_hay_ausentes(void)
{
    if (xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return false;
    }
    bool hay = false;
    for (int i = 0; i < s_cant_hojas; i++) {
        if (s_hojas[i].ausente && (s_hojas[i].aula[0] == '\0' || strcmp(s_hojas[i].aula, s_aula) == 0)) {
            hay = true;
            break;
        }
    }
    xSemaphoreGive(s_lock);
    return hay;
}

int mesh_hojas_get_lista(mesh_hoja_info_t *lista, size_t max_elementos)
{
    if (!lista || max_elementos == 0 || xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) != pdTRUE) {
        return 0;
    }
    int copiados = 0;
    for (int i = 0; i < s_cant_hojas && copiados < (int)max_elementos; i++) {
        memcpy(&lista[copiados++], &s_hojas[i], sizeof(mesh_hoja_info_t));
    }
    xSemaphoreGive(s_lock);
    return copiados;
}
