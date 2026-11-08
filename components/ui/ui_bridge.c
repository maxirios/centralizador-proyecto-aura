#include "ui_bridge.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "esp_log.h"
#include "cJSON.h"
#include "freertos/semphr.h"

static const char *TAG = "ui_bridge";

static ui_estado_aula_t s_estado;
static SemaphoreHandle_t s_lock = NULL;
static ui_notif_cb_t s_notif_cb = NULL;
static void *s_user_data = NULL;

static const char *const CLAVES_TEMP[]        = { "temp_c", "temp", "temperatura" };
static const char *const CLAVES_HUM[]         = { "humedad_pct", "hum_pct", "hum", "humedad" };
static const char *const CLAVES_CO2[]         = { "co2_ppm", "co2" };
static const char *const CLAVES_LUZ_VENTANA[] = { "luz_ventana_lx", "luz_lx", "iluminancia" };
static const char *const CLAVES_LUZ_AULA[]    = { "luz_aula_lx", "luz_int_lx" };
static const char *const CLAVES_ACTUADOR[]    = { "rele_canal1", "led", "rele", "actuador" };

static bool leer_medida(const cJSON *obj, const char *const *claves, size_t cant, float *out)
{
    for (size_t i = 0; i < cant; i++) {
        const cJSON *it = cJSON_GetObjectItemCaseSensitive(obj, claves[i]);
        if (cJSON_IsNumber(it)) {
            *out = (float)it->valuedouble;
            return true;
        }
    }
    return false;
}

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
    n->temp = NAN;
    n->hum = NAN;
    n->co2 = NAN;
    n->luz_ventana = NAN;
    n->luz_aula = NAN;
    n->presencia = -1;
    memcpy(n->mac, mac, 6);
    aura_hw_id_de_mac(mac, n->hw_id);
    n->conectado = true;
    return n;
}

static void formatear_ticker_nodo(ui_nodo_t *n)
{
    char buf[160] = "";
    size_t len = 0;

    if (n->adaptador[0] != '\0') {
        len += snprintf(buf + len, sizeof(buf) - len, "[%s] ", n->adaptador);
    }

    bool primero = true;
    if (!isnan(n->temp)) {
        len += snprintf(buf + len, sizeof(buf) - len, "%s%.1f °C", primero ? "" : "  |  ", n->temp);
        primero = false;
    }
    if (!isnan(n->hum)) {
        len += snprintf(buf + len, sizeof(buf) - len, "%s%.0f %%", primero ? "" : "  |  ", n->hum);
        primero = false;
    }
    if (!isnan(n->co2)) {
        len += snprintf(buf + len, sizeof(buf) - len, "%s%.0f ppm", primero ? "" : "  |  ", n->co2);
        primero = false;
    }
    if (!isnan(n->luz_ventana)) {
        len += snprintf(buf + len, sizeof(buf) - len, "%sVent: %.0f lx", primero ? "" : "  |  ", n->luz_ventana);
        primero = false;
    }
    if (!isnan(n->luz_aula)) {
        len += snprintf(buf + len, sizeof(buf) - len, "%sAula: %.0f lx", primero ? "" : "  |  ", n->luz_aula);
        primero = false;
    }
    if (n->presencia >= 0) {
        len += snprintf(buf + len, sizeof(buf) - len, "%sPres: %s", primero ? "" : "  |  ", n->presencia ? "SI" : "NO");
        primero = false;
    }
    if (n->tiene_actuador) {
        len += snprintf(buf + len, sizeof(buf) - len, "%s%s: %s",
                        primero ? "" : "  |  ",
                        n->actuador_key[0] ? n->actuador_key : "act",
                        n->actuador_estado ? "ON" : "OFF");
    }

    strlcpy(n->ticker_line, buf, sizeof(n->ticker_line));
    strlcpy(s_estado.ultimo_ticker, buf, sizeof(s_estado.ultimo_ticker));
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
        strlcpy(s_estado.ultimo_ticker, "Sin lecturas en malla", sizeof(s_estado.ultimo_ticker));
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
        // Extraer procedencia si viene en el sobre JSON
        const cJSON *j_adap = cJSON_GetObjectItemCaseSensitive(root, "adaptador");
        if (!j_adap) j_adap = cJSON_GetObjectItemCaseSensitive(root, "node_id");
        if (cJSON_IsString(j_adap) && j_adap->valuestring) {
            strlcpy(n->adaptador, j_adap->valuestring, sizeof(n->adaptador));
        }

        // Soportar tanto sobre con subobjeto "values" como JSON plano directo
        const cJSON *vals = cJSON_GetObjectItemCaseSensitive(root, "values");
        if (!cJSON_IsObject(vals)) {
            vals = root;
        }

        leer_medida(vals, CLAVES_TEMP, sizeof(CLAVES_TEMP) / sizeof(CLAVES_TEMP[0]), &n->temp);
        leer_medida(vals, CLAVES_HUM, sizeof(CLAVES_HUM) / sizeof(CLAVES_HUM[0]), &n->hum);
        leer_medida(vals, CLAVES_CO2, sizeof(CLAVES_CO2) / sizeof(CLAVES_CO2[0]), &n->co2);
        leer_medida(vals, CLAVES_LUZ_VENTANA, sizeof(CLAVES_LUZ_VENTANA) / sizeof(CLAVES_LUZ_VENTANA[0]), &n->luz_ventana);
        leer_medida(vals, CLAVES_LUZ_AULA, sizeof(CLAVES_LUZ_AULA) / sizeof(CLAVES_LUZ_AULA[0]), &n->luz_aula);

        const cJSON *j_pres = cJSON_GetObjectItemCaseSensitive(vals, "presencia");
        if (cJSON_IsBool(j_pres)) {
            n->presencia = cJSON_IsTrue(j_pres) ? 1 : 0;
        } else if (cJSON_IsNumber(j_pres)) {
            n->presencia = (j_pres->valueint != 0) ? 1 : 0;
        }

        for (size_t i = 0; i < sizeof(CLAVES_ACTUADOR) / sizeof(CLAVES_ACTUADOR[0]); i++) {
            const cJSON *it = cJSON_GetObjectItemCaseSensitive(vals, CLAVES_ACTUADOR[i]);
            if (it) {
                n->tiene_actuador = true;
                strlcpy(n->actuador_key, CLAVES_ACTUADOR[i], sizeof(n->actuador_key));
                if (cJSON_IsBool(it)) {
                    n->actuador_estado = cJSON_IsTrue(it);
                } else if (cJSON_IsNumber(it)) {
                    n->actuador_estado = (it->valueint != 0);
                }
                break;
            }
        }

        formatear_ticker_nodo(n);
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
