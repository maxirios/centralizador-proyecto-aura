#include "ui_bridge.h"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "cJSON.h"
#include "freertos/semphr.h"

static const char *TAG = "ui_bridge";

static ui_estado_aula_t s_estado;
static SemaphoreHandle_t s_lock = NULL;
static ui_notif_cb_t s_notif_cb = NULL;
static void *s_user_data = NULL;

static ui_nodo_t *buscar_o_crear_nodo(const uint8_t mac[6])
{
    for (int i = 0; i < s_estado.cant_nodos; i++) {
        if (memcmp(s_estado.nodos[i].mac, mac, 6) == 0) {
            return &s_estado.nodos[i];
        }
    }
    if (s_estado.cant_nodos >= MESH_HOJAS_MAX) {
        return NULL;
    }
    ui_nodo_t *n = &s_estado.nodos[s_estado.cant_nodos++];
    memset(n, 0, sizeof(*n));
    memcpy(n->mac, mac, 6);
    aura_hw_id_de_mac(mac, n->hw_id);
    n->conectado = true;
    return n;
}

esp_err_t ui_bridge_init(void)
{
    if (s_lock == NULL) {
        s_lock = xSemaphoreCreateMutex();
        if (s_lock == NULL) {
            ESP_LOGE(TAG, "Error creando mutex para ui_bridge");
            return ESP_ERR_NO_MEM;
        }
    }

    if (xSemaphoreTake(s_lock, portMAX_DELAY) == pdTRUE) {
        memset(&s_estado, 0, sizeof(s_estado));
        xSemaphoreGive(s_lock);
    }

    ESP_LOGI(TAG, "Modulo ui_bridge inicializado correctamente");
    return ESP_OK;
}

void ui_bridge_registrar_observador(ui_notif_cb_t cb, void *user_data)
{
    s_notif_cb = cb;
    s_user_data = user_data;
}

bool ui_bridge_lock(TickType_t timeout_ticks)
{
    if (s_lock == NULL) {
        return false;
    }
    return (xSemaphoreTake(s_lock, timeout_ticks) == pdTRUE);
}

void ui_bridge_unlock(void)
{
    if (s_lock != NULL) {
        xSemaphoreGive(s_lock);
    }
}

esp_err_t ui_bridge_get_snapshot(ui_estado_aula_t *out_estado)
{
    if (!out_estado) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!ui_bridge_lock(pdMS_TO_TICKS(100))) {
        return ESP_ERR_TIMEOUT;
    }
    memcpy(out_estado, &s_estado, sizeof(ui_estado_aula_t));
    ui_bridge_unlock();
    return ESP_OK;
}

const ui_estado_aula_t *ui_bridge_get_estado_ref(void)
{
    return &s_estado;
}

void ui_bridge_actualizar_red(bool gateway_conectado, bool modo_isla, uint8_t canal, const char *aula)
{
    if (!ui_bridge_lock(pdMS_TO_TICKS(100))) {
        return;
    }
    s_estado.red.gateway_conectado = gateway_conectado;
    s_estado.red.modo_isla = modo_isla;
    s_estado.red.canal = canal;
    if (aula) {
        strlcpy(s_estado.red.aula, aula, sizeof(s_estado.red.aula));
    }
    ui_bridge_unlock();

    if (s_notif_cb) {
        s_notif_cb(UI_EVENTO_RED_CAMBIO, &s_estado.red, s_user_data);
    }
}

void ui_bridge_on_mesh_evento_hoja(const uint8_t mac[6], bool ausente, const char *motivo)
{
    if (!mac || !ui_bridge_lock(pdMS_TO_TICKS(100))) {
        return;
    }

    ui_nodo_t *n = buscar_o_crear_nodo(mac);
    ui_nodo_t snap;
    if (n) {
        n->conectado = !ausente;
        memcpy(&snap, n, sizeof(snap));
    }
    ui_bridge_unlock();

    if (n && s_notif_cb) {
        ui_evento_tipo_t ev = ausente ? UI_EVENTO_NODO_DESCONECTADO : UI_EVENTO_NODO_CONECTADO;
        s_notif_cb(ev, &snap, s_user_data);
    }
}

void ui_bridge_on_mesh_telemetria(const uint8_t mac[6], uint32_t ts, const char *values_json, bool es_estado)
{
    if (!mac || !values_json || !ui_bridge_lock(pdMS_TO_TICKS(100))) {
        return;
    }

    ui_nodo_t *n = buscar_o_crear_nodo(mac);
    if (!n) {
        ui_bridge_unlock();
        return;
    }

    n->conectado = true;
    n->tiene_telemetria = true;
    n->ts_ultimo = ts;
    strlcpy(n->raw_values, values_json, sizeof(n->raw_values));

    cJSON *root = cJSON_Parse(values_json);
    if (root) {
        cJSON *it = cJSON_GetObjectItemCaseSensitive(root, "temp");
        if (!it) it = cJSON_GetObjectItemCaseSensitive(root, "temperatura");
        if (cJSON_IsNumber(it)) n->temp = (float)it->valuedouble;

        it = cJSON_GetObjectItemCaseSensitive(root, "hum");
        if (!it) it = cJSON_GetObjectItemCaseSensitive(root, "humedad");
        if (cJSON_IsNumber(it)) n->hum = (float)it->valuedouble;

        it = cJSON_GetObjectItemCaseSensitive(root, "co2");
        if (cJSON_IsNumber(it)) n->co2 = (float)it->valuedouble;

        it = cJSON_GetObjectItemCaseSensitive(root, "led");
        if (!it) it = cJSON_GetObjectItemCaseSensitive(root, "rele");
        if (!it) it = cJSON_GetObjectItemCaseSensitive(root, "actuador");
        if (it) {
            n->tiene_actuador = true;
            if (cJSON_IsBool(it)) {
                n->actuador_estado = cJSON_IsTrue(it);
            } else if (cJSON_IsNumber(it)) {
                n->actuador_estado = (it->valueint != 0);
            }
        }
        cJSON_Delete(root);
    }

    ui_nodo_t snap;
    memcpy(&snap, n, sizeof(snap));
    ui_bridge_unlock();

    if (s_notif_cb) {
        s_notif_cb(UI_EVENTO_NODO_TELEMETRIA, &snap, s_user_data);
    }
}

void ui_bridge_on_control_resultado(const mesh_control_resultado_t *res)
{
    if (!res || !ui_bridge_lock(pdMS_TO_TICKS(100))) {
        return;
    }

    ui_nodo_t *n = buscar_o_crear_nodo(res->de_mac);
    if (n && res->aplicado) {
        n->tiene_actuador = true;
    }
    ui_bridge_unlock();

    if (s_notif_cb) {
        s_notif_cb(UI_EVENTO_CONTROL_RESULTADO, res, s_user_data);
    }
}

esp_err_t ui_bridge_enviar_comando(const uint8_t dest_mac[6], const char *actuador, const char *payload_json)
{
    if (!dest_mac || !actuador || !payload_json) {
        return ESP_ERR_INVALID_ARG;
    }
    return mesh_control_enviar_comando(dest_mac, actuador, payload_json, NULL, "ui_bridge");
}

esp_err_t ui_bridge_conmutar_actuador(const uint8_t dest_mac[6], const char *actuador)
{
    if (!dest_mac) {
        return ESP_ERR_INVALID_ARG;
    }
    const char *act = (actuador && actuador[0]) ? actuador : "led";
    return mesh_control_enviar_comando(dest_mac, act, "{\"invertir\":true}", NULL, "ui_bridge");
}
