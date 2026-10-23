#include "mesh_net.h"
#include "mesh_hojas.h"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "cJSON.h"

static const char *TAG = "mesh_net";
static const char *NVS_NAMESPACE = "concentrador";
static const char *NVS_KEY_AULA = "aula";

static char s_aula[AURA_AULA_MAX] = {0};
static uint8_t s_mi_mac[6] = {0};
static bool s_inicializado = false;

esp_err_t mesh_net_init(void)
{
    if (s_inicializado) {
        return ESP_OK;
    }

    esp_err_t err = esp_read_mac(s_mi_mac, ESP_MAC_WIFI_STA);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error leyendo MAC STA: %s", esp_err_to_name(err));
        return err;
    }

    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(s_mi_mac, hw);
    ESP_LOGI(TAG, "Centralizador hw_id: %s", hw);

    nvs_handle_t h;
    err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &h);
    if (err == ESP_OK) {
        size_t len = sizeof(s_aula);
        err = nvs_get_str(h, NVS_KEY_AULA, s_aula, &len);
        if (err != ESP_OK || s_aula[0] == '\0' || !aura_aula_valida(s_aula)) {
            ESP_LOGW(TAG, "Aula no persistida o invalida en NVS. Usando por defecto: '%s'", CONFIG_AURA_AULA_DEFAULT);
            strlcpy(s_aula, CONFIG_AURA_AULA_DEFAULT, sizeof(s_aula));
            nvs_set_str(h, NVS_KEY_AULA, s_aula);
            nvs_commit(h);
        } else {
            ESP_LOGI(TAG, "Aula recuperada de NVS: '%s'", s_aula);
        }
        nvs_close(h);
    } else {
        ESP_LOGW(TAG, "No se pudo abrir NVS (%s). Usando aula por defecto: '%s'", esp_err_to_name(err), CONFIG_AURA_AULA_DEFAULT);
        strlcpy(s_aula, CONFIG_AURA_AULA_DEFAULT, sizeof(s_aula));
    }

    s_inicializado = true;
    return ESP_OK;
}

const char *mesh_net_get_aula(void)
{
    return s_aula;
}

esp_err_t mesh_net_anunciar_aula(void)
{
    if (!s_inicializado) {
        mesh_net_init();
    }

    esp_wifi_set_vendor_ie(false, WIFI_VND_IE_TYPE_BEACON, WIFI_VND_IE_ID_1, NULL);
    esp_wifi_set_vendor_ie(false, WIFI_VND_IE_TYPE_PROBE_RESP, WIFI_VND_IE_ID_1, NULL);

    if (s_aula[0] == '\0') {
        ESP_LOGW(TAG, "Sin aula configurada: no se anuncian beacons Vendor IE");
        return ESP_OK;
    }

    uint8_t ie_buf[sizeof(vendor_ie_data_t) + 6 + AURA_AULA_MAX];
    vendor_ie_data_t *v = (vendor_ie_data_t *)ie_buf;

    size_t aula_len = strlen(s_aula);
    v->element_id = WIFI_VENDOR_IE_ELEMENT_ID;
    v->length = 4 + 6 + aula_len;
    v->vendor_oui[0] = AURA_OUI_0;
    v->vendor_oui[1] = AURA_OUI_1;
    v->vendor_oui[2] = AURA_OUI_2;
    v->vendor_oui_type = AURA_IE_CONCENTRADOR;

    memcpy(v->payload, s_mi_mac, 6);
    memcpy(v->payload + 6, s_aula, aula_len);

    esp_err_t e1 = esp_wifi_set_vendor_ie(true, WIFI_VND_IE_TYPE_BEACON, WIFI_VND_IE_ID_1, v);
    esp_err_t e2 = esp_wifi_set_vendor_ie(true, WIFI_VND_IE_TYPE_PROBE_RESP, WIFI_VND_IE_ID_1, v);

    if (e1 == ESP_OK && e2 == ESP_OK) {
        ESP_LOGI(TAG, "Anunciando aula '%s' en beacons Wi-Fi (Vendor IE activo)", s_aula);
        return ESP_OK;
    } else {
        ESP_LOGW(TAG, "Fallo al inyectar Vendor IE: beacon=%s, probe_resp=%s",
                 esp_err_to_name(e1), esp_err_to_name(e2));
        return (e1 != ESP_OK) ? e1 : e2;
    }
}

esp_err_t mesh_net_set_aula(const char *nueva_aula)
{
    if (!aura_aula_valida(nueva_aula)) {
        ESP_LOGE(TAG, "Nombre de aula invalido: '%s'", nueva_aula ? nueva_aula : "NULL");
        return ESP_ERR_INVALID_ARG;
    }

    nvs_handle_t h;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &h);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error abriendo NVS: %s", esp_err_to_name(err));
        return err;
    }

    err = nvs_set_str(h, NVS_KEY_AULA, nueva_aula);
    if (err == ESP_OK) {
        err = nvs_commit(h);
    }
    nvs_close(h);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error guardando en NVS: %s", esp_err_to_name(err));
        return err;
    }

    bool cambio = (strcmp(s_aula, nueva_aula) != 0);
    strlcpy(s_aula, nueva_aula, sizeof(s_aula));

    if (cambio) {
        ESP_LOGW(TAG, "Aula actualizada a '%s'. Deautenticando nodos hijos...", s_aula);
        mesh_hojas_set_aula(s_aula);
        esp_wifi_deauth_sta(0);
    }

    return mesh_net_anunciar_aula();
}

esp_err_t mesh_net_procesar_comando_config(const char *json_str, char *respuesta, size_t max_len)
{
    if (json_str == NULL || respuesta == NULL || max_len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    cJSON *root = cJSON_Parse(json_str);
    if (!cJSON_IsObject(root)) {
        if (root) cJSON_Delete(root);
        snprintf(respuesta, max_len, "{\"aplicado\":false,\"motivo\":\"json_invalido\"}");
        return ESP_OK;
    }

    const cJSON *cmd = cJSON_GetObjectItemCaseSensitive(root, "command");
    const cJSON *ci = cJSON_GetObjectItemCaseSensitive(root, "command_id");
    const cJSON *params = cJSON_GetObjectItemCaseSensitive(root, "params");

    bool ok = false;
    const char *motivo = "comando_desconocido";

    if (cJSON_IsString(cmd) && strcmp(cmd->valuestring, "set_config") == 0) {
        const cJSON *item_aula = cJSON_GetObjectItemCaseSensitive(params, "aula");
        if (item_aula == NULL || !cJSON_IsString(item_aula)) {
            motivo = "parametro_invalido";
        } else if (!aura_aula_valida(item_aula->valuestring)) {
            motivo = "aula_invalida";
        } else {
            esp_err_t err = mesh_net_set_aula(item_aula->valuestring);
            if (err == ESP_OK) {
                ok = true;
            } else {
                motivo = "error_persistencia";
            }
        }
    }

    cJSON *res = cJSON_CreateObject();
    if (cJSON_IsString(ci)) {
        cJSON_AddStringToObject(res, "command_id", ci->valuestring);
    }
    cJSON_AddBoolToObject(res, "aplicado", ok);
    if (!ok) {
        cJSON_AddStringToObject(res, "motivo", motivo);
    }

    cJSON *cfg = cJSON_AddObjectToObject(res, "config");
    cJSON_AddStringToObject(cfg, "aula", s_aula);

    char *txt = cJSON_PrintUnformatted(res);
    if (txt) {
        strlcpy(respuesta, txt, max_len);
        cJSON_free(txt);
    } else {
        snprintf(respuesta, max_len, "{\"aplicado\":false,\"motivo\":\"error_memoria\"}");
    }

    cJSON_Delete(res);
    cJSON_Delete(root);
    return ESP_OK;
}
