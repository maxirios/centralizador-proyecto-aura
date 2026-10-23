#include "mesh_control.h"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "esp_mesh.h"
#include "esp_mac.h"
#include "aura_util.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

static const char *TAG = "mesh_control";

typedef struct {
    uint8_t mac[6];
    uint8_t largo;
    char json[AURA_PAYLOAD_MAX + 1];
} mesh_control_item_t;

static QueueHandle_t s_cola_tx = NULL;
static TaskHandle_t s_tarea_tx_handle = NULL;
static mesh_control_resultado_cb_t s_resultado_cb = NULL;
static SemaphoreHandle_t s_lock = NULL;
static uint16_t s_seq = 1;

uint16_t mesh_control_siguiente_seq(void)
{
    uint16_t seq;
    if (s_lock != NULL && xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) == pdTRUE) {
        seq = s_seq++;
        if (s_seq == 0) {
            s_seq = 1;
        }
        xSemaphoreGive(s_lock);
    } else {
        seq = s_seq++;
    }
    return seq;
}

static void tarea_control_tx(void *arg)
{
    mesh_control_item_t item;
    while (true) {
        if (xQueueReceive(s_cola_tx, &item, portMAX_DELAY) == pdTRUE) {
            aura_trama_t t;
            uint16_t seq = mesh_control_siguiente_seq();
            aura_trama_init(&t, AURA_TIPO_COMANDO, seq, item.json, item.largo);

            mesh_addr_t dest;
            memcpy(dest.addr, item.mac, 6);
            mesh_data_t d = {
                .data = (uint8_t *)&t,
                .size = aura_trama_bytes(&t),
                .proto = MESH_PROTO_BIN,
                .tos = MESH_TOS_P2P,
            };

            esp_err_t err = esp_mesh_send(&dest, &d, MESH_DATA_P2P, NULL, 0);
            char hw[AURA_HW_ID_BYTES];
            aura_hw_id_de_mac(item.mac, hw);

            if (err == ESP_OK) {
                ESP_LOGI(TAG, "Comando enviado a %s (seq %u): %s", hw, seq, item.json);
            } else {
                ESP_LOGW(TAG, "Error enviando comando a %s: %s", hw, esp_err_to_name(err));
            }
        }
    }
}

esp_err_t mesh_control_init(mesh_control_resultado_cb_t resultado_cb)
{
    s_resultado_cb = resultado_cb;

    if (s_lock == NULL) {
        s_lock = xSemaphoreCreateMutex();
        if (s_lock == NULL) {
            ESP_LOGE(TAG, "Error creando mutex para mesh_control");
            return ESP_ERR_NO_MEM;
        }
    }

    if (s_cola_tx == NULL) {
        s_cola_tx = xQueueCreate(MESH_CONTROL_COLA_TX_LEN, sizeof(mesh_control_item_t));
        if (s_cola_tx == NULL) {
            ESP_LOGE(TAG, "Error creando cola tx para mesh_control");
            return ESP_ERR_NO_MEM;
        }
    }

    if (s_tarea_tx_handle == NULL) {
        BaseType_t res = xTaskCreate(tarea_control_tx, "mesh_ctrl_tx", 3072, NULL, 4, &s_tarea_tx_handle);
        if (res != pdPASS) {
            ESP_LOGE(TAG, "Error creando tarea de despacho mesh_ctrl_tx");
            return ESP_FAIL;
        }
    }

    ESP_LOGI(TAG, "Modulo mesh_control inicializado (cola tx: %d items)", MESH_CONTROL_COLA_TX_LEN);
    return ESP_OK;
}

void mesh_control_set_resultado_cb(mesh_control_resultado_cb_t resultado_cb)
{
    if (s_lock != NULL && xSemaphoreTake(s_lock, pdMS_TO_TICKS(50)) == pdTRUE) {
        s_resultado_cb = resultado_cb;
        xSemaphoreGive(s_lock);
    } else {
        s_resultado_cb = resultado_cb;
    }
}

esp_err_t mesh_control_enviar_raw(const uint8_t mac_destino[6], const char *json_cmd)
{
    if (!mac_destino || !json_cmd) {
        return ESP_ERR_INVALID_ARG;
    }
    size_t len = strlen(json_cmd);
    if (len > AURA_PAYLOAD_MAX) {
        ESP_LOGE(TAG, "Payload excede maximo permitido (%u > %d)", (unsigned)len, AURA_PAYLOAD_MAX);
        return ESP_ERR_INVALID_SIZE;
    }
    if (s_cola_tx == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    mesh_control_item_t item;
    memcpy(item.mac, mac_destino, 6);
    item.largo = (uint8_t)len;
    memcpy(item.json, json_cmd, len);
    item.json[len] = '\0';

    if (xQueueSend(s_cola_tx, &item, 0) != pdTRUE) {
        ESP_LOGW(TAG, "Cola de comandos llena, descartando envio");
        return ESP_ERR_NO_MEM;
    }
    return ESP_OK;
}

esp_err_t mesh_control_enviar_comando(const uint8_t mac_destino[6],
                                      const char *comando,
                                      const char *params_json,
                                      const char *command_id,
                                      const char *origen)
{
    if (!mac_destino || !comando) {
        return ESP_ERR_INVALID_ARG;
    }

    char cid_buf[MESH_CONTROL_CMD_ID_MAX];
    if (!command_id || command_id[0] == '\0') {
        snprintf(cid_buf, sizeof(cid_buf), "cmd-%u", mesh_control_siguiente_seq());
        command_id = cid_buf;
    }

    const char *orig = (origen && origen[0] != '\0') ? origen : "centralizador";

    cJSON *root = cJSON_CreateObject();
    if (!root) {
        return ESP_ERR_NO_MEM;
    }

    cJSON_AddStringToObject(root, "command", comando);
    cJSON_AddStringToObject(root, "command_id", command_id);
    cJSON_AddStringToObject(root, "origen", orig);

    if (params_json && params_json[0] != '\0') {
        cJSON *params = cJSON_Parse(params_json);
        if (params) {
            cJSON_AddItemToObject(root, "params", params);
        }
    }

    char *txt = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);

    if (!txt) {
        return ESP_ERR_NO_MEM;
    }

    esp_err_t err = mesh_control_enviar_raw(mac_destino, txt);
    cJSON_free(txt);
    return err;
}

bool mesh_control_procesar_resultado(const uint8_t de_mac[6], const aura_trama_t *trama)
{
    if (!de_mac || !trama || trama->tipo != AURA_TIPO_RESULTADO) {
        return false;
    }

    char txt[AURA_PAYLOAD_MAX + 1];
    aura_payload_texto(trama, txt, sizeof(txt));

    cJSON *root = cJSON_Parse(txt);
    if (!root) {
        ESP_LOGW(TAG, "Resultado JSON no parseable de " MACSTR ": %s", MAC2STR(de_mac), txt);
        return false;
    }

    mesh_control_resultado_t res;
    memset(&res, 0, sizeof(res));
    memcpy(res.de_mac, de_mac, 6);
    res.raw_json = txt;

    cJSON *ci = cJSON_GetObjectItemCaseSensitive(root, "command_id");
    if (cJSON_IsString(ci) && ci->valuestring) {
        strlcpy(res.command_id, ci->valuestring, sizeof(res.command_id));
    }

    cJSON *ap = cJSON_GetObjectItemCaseSensitive(root, "aplicado");
    res.aplicado = cJSON_IsTrue(ap);

    cJSON *mot = cJSON_GetObjectItemCaseSensitive(root, "motivo");
    if (cJSON_IsString(mot) && mot->valuestring) {
        strlcpy(res.motivo, mot->valuestring, sizeof(res.motivo));
    }

    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(de_mac, hw);
    ESP_LOGI(TAG, "Resultado recibido de %s: cid='%s' aplicado=%s motivo='%s'",
             hw, res.command_id, res.aplicado ? "SI" : "NO", res.motivo);

    mesh_control_resultado_cb_t cb = s_resultado_cb;
    if (cb) {
        cb(&res);
    }

    cJSON_Delete(root);
    return true;
}
