#include "mesh_net.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_mesh.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "cJSON.h"

#define TAG                     "MESH_NET"
#define ROUTER_FICTICIO         "aura-sin-router"
#define ESPERA_LOTE_MS          50
#define INTERVALO_REPORTE_S     60
#define PEDIR_HORA_MS           10000
#define LIMITE_ENVIO_MS         5000
#define FALLOS_PARA_RECONECTAR  3

typedef struct {
    uint8_t mac[6];
    TickType_t visto;
    char aula[AURA_AULA_MAX];
} hoja_interna_t;

typedef struct {
    uint16_t seq;
    char json[AURA_PAYLOAD_MAX + 1];
} comando_interno_t;

static uint8_t s_mi_mac[6];
static char s_aula[AURA_AULA_MAX] = "";
static volatile bool s_conectado = false;
static volatile bool s_reconecto = false;
static volatile int s_hijos = 0;
static volatile int s_fallos_envio = 0;
static uint16_t s_seq = 0;

static SemaphoreHandle_t s_lock_envio = NULL;
static SemaphoreHandle_t s_lock_lote = NULL;
static SemaphoreHandle_t s_lock_hojas = NULL;
static QueueHandle_t s_cola_comandos = NULL;

static aura_lote_t s_lote;
static TickType_t s_lote_desde = 0;

static hoja_interna_t s_hojas[MESH_NET_MAX_HOJAS];
static int s_cant_hojas = 0;

static aura_trama_t s_resultado_pendiente;
static volatile bool s_hay_resultado_pendiente = false;
static TickType_t s_resultado_enviado_en = 0;
static volatile bool s_reportar_ya = false;

static mesh_net_telemetria_cb_t s_telemetria_cb = NULL;
static mesh_net_estado_cb_t s_estado_cb = NULL;
static mesh_net_filtro_local_cb_t s_filtro_local_cb = NULL;

static uint64_t obtener_ahora_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t ms = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return aura_hora_valida((uint32_t)(ms / 1000)) ? ms : 0;
}

static void hora_ajustar(uint64_t ms)
{
    if (!aura_hora_valida((uint32_t)(ms / 1000))) {
        return;
    }
    bool primera = (obtener_ahora_ms() == 0);
    struct timeval tv = {
        .tv_sec = (time_t)(ms / 1000),
        .tv_usec = (suseconds_t)(ms % 1000) * 1000
    };
    settimeofday(&tv, NULL);
    if (primera) {
        ESP_LOGI(TAG, "Hora sincronizada con Gateway/Root");
    }
}

static void anunciar_aula(void)
{
    static uint8_t ie[sizeof(vendor_ie_data_t) + 6 + AURA_AULA_MAX];
    vendor_ie_data_t *v = (vendor_ie_data_t *)ie;

    esp_wifi_set_vendor_ie(false, WIFI_VND_IE_TYPE_BEACON, WIFI_VND_IE_ID_1, NULL);
    esp_wifi_set_vendor_ie(false, WIFI_VND_IE_TYPE_PROBE_RESP, WIFI_VND_IE_ID_1, NULL);

    if (s_aula[0] == '\0') {
        ESP_LOGW(TAG, "Sin aula asignada en NVS: no se anuncia en beacon");
        return;
    }

    v->element_id = WIFI_VENDOR_IE_ELEMENT_ID;
    v->vendor_oui[0] = AURA_OUI_0;
    v->vendor_oui[1] = AURA_OUI_1;
    v->vendor_oui[2] = AURA_OUI_2;
    v->vendor_oui_type = AURA_IE_CONCENTRADOR;
    memcpy(v->payload, s_mi_mac, 6);
    memcpy(v->payload + 6, s_aula, strlen(s_aula));
    v->length = 4 + 6 + strlen(s_aula);

    esp_err_t e1 = esp_wifi_set_vendor_ie(true, WIFI_VND_IE_TYPE_BEACON, WIFI_VND_IE_ID_1, v);
    esp_err_t e2 = esp_wifi_set_vendor_ie(true, WIFI_VND_IE_TYPE_PROBE_RESP, WIFI_VND_IE_ID_1, v);
    if (e1 == ESP_OK && e2 == ESP_OK) {
        ESP_LOGI(TAG, "Beacon IE activo anunciando aula '%s'", s_aula);
    } else {
        ESP_LOGW(TAG, "Fallo al registrar vendor IE: %s / %s", esp_err_to_name(e1), esp_err_to_name(e2));
    }
}

static bool enviar_bytes(const mesh_addr_t *destino, const uint8_t *datos, size_t largo)
{
    if (!s_conectado) {
        return false;
    }
    mesh_data_t d = {
        .data = (uint8_t *)datos,
        .size = (uint16_t)largo,
        .proto = MESH_PROTO_BIN,
        .tos = MESH_TOS_P2P
    };
    esp_err_t err = esp_mesh_send(destino, &d, MESH_DATA_P2P, NULL, 0);
    if (destino != NULL) {
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "Error envio a nodo hoja: %s", esp_err_to_name(err));
        }
        return (err == ESP_OK);
    }
    if (err == ESP_OK) {
        s_fallos_envio = 0;
        return true;
    }

    ESP_LOGW(TAG, "Error envio hacia raiz: %s", esp_err_to_name(err));
    if (s_conectado && ++s_fallos_envio >= FALLOS_PARA_RECONECTAR) {
        ESP_LOGW(TAG, "%d envios fallidos seguidos: forzando reconexion", s_fallos_envio);
        s_fallos_envio = 0;
        esp_mesh_disconnect();
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_mesh_connect();
    }
    return false;
}

static bool enviar_trama(const mesh_addr_t *destino, uint8_t tipo, const void *payload, size_t largo)
{
    aura_trama_t t;
    xSemaphoreTake(s_lock_envio, portMAX_DELAY);
    aura_trama_init(&t, tipo, s_seq++, payload, largo);
    xSemaphoreGive(s_lock_envio);
    return enviar_bytes(destino, (const uint8_t *)&t, aura_trama_bytes(&t));
}

static bool enviar_json(const mesh_addr_t *destino, uint8_t tipo, const cJSON *doc)
{
    char *txt = cJSON_PrintUnformatted(doc);
    if (txt == NULL) {
        return false;
    }
    bool ok = (strlen(txt) <= AURA_PAYLOAD_MAX) && enviar_trama(destino, tipo, txt, strlen(txt));
    cJSON_free(txt);
    return ok;
}

static void lote_mandar(void)
{
    xSemaphoreTake(s_lock_lote, portMAX_DELAY);
    if (s_lote.cantidad > 0) {
        if (!enviar_bytes(NULL, s_lote.buf, s_lote.largo)) {
            ESP_LOGW(TAG, "Lote de %u tramas no enviado (las hojas reintentaran)", s_lote.cantidad);
        }
        aura_lote_vaciar(&s_lote);
    }
    xSemaphoreGive(s_lock_lote);
}

static void lote_agregar(const uint8_t mac[6], const uint8_t *trama, size_t largo)
{
    xSemaphoreTake(s_lock_lote, portMAX_DELAY);
    if (s_lote.cantidad == 0) {
        s_lote_desde = xTaskGetTickCount();
    }
    bool ok = aura_lote_agregar(&s_lote, mac, trama, largo);
    xSemaphoreGive(s_lock_lote);
    if (!ok) {
        lote_mandar();
        xSemaphoreTake(s_lock_lote, portMAX_DELAY);
        s_lote_desde = xTaskGetTickCount();
        aura_lote_agregar(&s_lote, mac, trama, largo);
        xSemaphoreGive(s_lock_lote);
    }
}

static void tarea_lote(void *arg)
{
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(10));
        if (s_lote.cantidad > 0 && (xTaskGetTickCount() - s_lote_desde) >= pdMS_TO_TICKS(ESPERA_LOTE_MS)) {
            lote_mandar();
        }
    }
}

static hoja_interna_t *hoja_vista(const uint8_t mac[6])
{
    xSemaphoreTake(s_lock_hojas, portMAX_DELAY);
    int i;
    for (i = 0; i < s_cant_hojas && memcmp(s_hojas[i].mac, mac, 6) != 0; i++) {
    }
    if (i == s_cant_hojas) {
        if (s_cant_hojas == MESH_NET_MAX_HOJAS) {
            i = 0;
        } else {
            s_cant_hojas++;
        }
        memcpy(s_hojas[i].mac, mac, 6);
        s_hojas[i].aula[0] = 0;
        char hw[AURA_HW_ID_BYTES];
        aura_hw_id_de_mac(mac, hw);
        ESP_LOGI(TAG, "Nueva hoja detectada: %s", hw);
    }
    s_hojas[i].visto = xTaskGetTickCount();
    hoja_interna_t *ret = &s_hojas[i];
    xSemaphoreGive(s_lock_hojas);
    return ret;
}

static void aprender_aula(hoja_interna_t *h, const aura_trama_t *t)
{
    if (t->tipo != AURA_TIPO_REPORTE) {
        return;
    }
    char txt[AURA_PAYLOAD_MAX + 1];
    aura_payload_texto(t, txt, sizeof(txt));
    cJSON *d = cJSON_Parse(txt);
    if (d == NULL) {
        return;
    }
    const cJSON *cfg = cJSON_GetObjectItemCaseSensitive(d, "config");
    const cJSON *a = cJSON_GetObjectItemCaseSensitive(cfg, "aula");
    if (cJSON_IsString(a)) {
        xSemaphoreTake(s_lock_hojas, portMAX_DELAY);
        strlcpy(h->aula, a->valuestring, sizeof(h->aula));
        xSemaphoreGive(s_lock_hojas);
    }
    cJSON_Delete(d);
}

static void describir_config(cJSON *config)
{
    if (s_aula[0]) {
        cJSON_AddStringToObject(config, "aula", s_aula);
    } else {
        cJSON_AddNullToObject(config, "aula");
    }
    cJSON_AddNumberToObject(config, "intervalo_s", INTERVALO_REPORTE_S);
}

static void enviar_reporte_propio(void)
{
    cJSON *d = cJSON_CreateObject();
    describir_config(cJSON_AddObjectToObject(d, "config"));
    cJSON_AddStringToObject(d, "rol", "concentrador");
    cJSON_AddNumberToObject(d, "capa", esp_mesh_get_layer());
    cJSON_AddNumberToObject(d, "hijos", s_hijos);
    cJSON_AddNumberToObject(d, "hojas_aula", s_cant_hojas);
    cJSON_AddStringToObject(d, "alimentacion", "red");
    enviar_json(NULL, AURA_TIPO_REPORTE, d);
    cJSON_Delete(d);
}

static void procesar_comando_centralizador(const comando_interno_t *c)
{
    static bool hay_ultimo = false;
    static uint16_t ultimo = 0;
    if (hay_ultimo && ultimo == c->seq) {
        return;
    }
    hay_ultimo = true;
    ultimo = c->seq;
    ESP_LOGI(TAG, "Comando recibido para concentrador: %s", c->json);

    cJSON *d = cJSON_Parse(c->json);
    const cJSON *cmd = cJSON_GetObjectItemCaseSensitive(d, "command");
    const cJSON *ci = cJSON_GetObjectItemCaseSensitive(d, "command_id");
    const cJSON *params = cJSON_GetObjectItemCaseSensitive(d, "params");
    bool ok = false;
    const char *motivo = "comando_desconocido";

    if (!cJSON_IsObject(d)) {
        motivo = "json_invalido";
    } else if (cJSON_IsString(cmd) && strcmp(cmd->valuestring, "set_config") == 0) {
        const cJSON *a = cJSON_GetObjectItemCaseSensitive(params, "aula");
        if (cJSON_GetArraySize(params) != 1 || a == NULL) {
            motivo = "parametro_desconocido";
        } else if (!cJSON_IsString(a) || !aura_aula_valida(a->valuestring)) {
            motivo = "aula_invalida";
        } else {
            esp_err_t err = mesh_net_set_aula(a->valuestring);
            ok = (err == ESP_OK);
            if (!ok) {
                motivo = "error_de_nvs";
            }
        }
    }

    cJSON *r = cJSON_CreateObject();
    if (cJSON_IsString(ci)) {
        cJSON_AddStringToObject(r, "command_id", ci->valuestring);
    }
    cJSON_AddBoolToObject(r, "aplicado", ok);
    if (!ok) {
        cJSON_AddStringToObject(r, "motivo", motivo);
    }
    describir_config(cJSON_AddObjectToObject(r, "config"));
    char *txt = cJSON_PrintUnformatted(r);
    if (txt && strlen(txt) <= AURA_PAYLOAD_MAX) {
        xSemaphoreTake(s_lock_envio, portMAX_DELAY);
        aura_trama_init(&s_resultado_pendiente, AURA_TIPO_RESULTADO, s_seq++, txt, strlen(txt));
        xSemaphoreGive(s_lock_envio);
        s_hay_resultado_pendiente = true;
        s_resultado_enviado_en = xTaskGetTickCount();
        enviar_bytes(NULL, (const uint8_t *)&s_resultado_pendiente, aura_trama_bytes(&s_resultado_pendiente));
    }
    cJSON_free(txt);
    cJSON_Delete(r);
    cJSON_Delete(d);

    if (ok) {
        enviar_reporte_propio();
    }
}

static void tarea_estado(void *arg)
{
    TickType_t ultimo_reporte = 0, ultimo_pedido_hora = 0;
    comando_interno_t c;
    while (true) {
        if (xQueueReceive(s_cola_comandos, &c, pdMS_TO_TICKS(200)) == pdTRUE && s_conectado) {
            procesar_comando_centralizador(&c);
        }
        if (!s_conectado) {
            continue;
        }
        TickType_t ahora = xTaskGetTickCount();
        if (s_hay_resultado_pendiente && ahora - s_resultado_enviado_en >= pdMS_TO_TICKS(3000)) {
            s_resultado_enviado_en = ahora;
            enviar_bytes(NULL, (const uint8_t *)&s_resultado_pendiente, aura_trama_bytes(&s_resultado_pendiente));
        }
        if (s_reconecto || s_reportar_ya || ahora - ultimo_reporte >= pdMS_TO_TICKS(INTERVALO_REPORTE_S * 1000)) {
            s_reconecto = false;
            s_reportar_ya = false;
            ultimo_reporte = ahora;
            enviar_reporte_propio();
        }
        if (obtener_ahora_ms() == 0 && (ultimo_pedido_hora == 0 || ahora - ultimo_pedido_hora >= pdMS_TO_TICKS(PEDIR_HORA_MS))) {
            ultimo_pedido_hora = ahora;
            enviar_trama(NULL, AURA_TIPO_HORA, NULL, 0);
        }
    }
}

static void tarea_recepcion(void *arg)
{
    static uint8_t buf[MESH_MPS];
    while (true) {
        mesh_addr_t de;
        mesh_data_t d = {.data = buf, .size = sizeof(buf)};
        int flag = 0;
        if (esp_mesh_recv(&de, &d, portMAX_DELAY, &flag, NULL, 0) != ESP_OK) {
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }
        if (aura_trama_validar(buf, d.size) != AURA_TRAMA_OK) {
            ESP_LOGW(TAG, "Trama invalida recibida de " MACSTR " (%u bytes)", MAC2STR(de.addr), d.size);
            continue;
        }
        aura_trama_t t;
        memcpy(&t, buf, d.size);

        if (t.tipo == AURA_TIPO_COMANDO) {
            comando_interno_t c = {.seq = t.seq};
            aura_payload_texto(&t, c.json, sizeof(c.json));
            xQueueSend(s_cola_comandos, &c, 0);
            continue;
        }
        if (t.tipo == AURA_TIPO_HORA && t.largo == 8) {
            hora_ajustar(aura_u64_leer(t.payload));
            continue;
        }
        if (t.tipo == AURA_TIPO_EVENTO_OK) {
            if (t.largo == 2 && s_hay_resultado_pendiente &&
                s_resultado_pendiente.seq == (uint16_t)(t.payload[0] | t.payload[1] << 8)) {
                s_hay_resultado_pendiente = false;
            }
            continue;
        }
        if (t.tipo == AURA_TIPO_REPORTAR) {
            s_reportar_ya = true;
            continue;
        }

        hoja_interna_t *h = hoja_vista(de.addr);
        aprender_aula(h, &t);

        if (t.tipo == AURA_TIPO_HORA) {
            uint64_t ms = obtener_ahora_ms();
            if (ms) {
                aura_trama_t r;
                xSemaphoreTake(s_lock_envio, portMAX_DELAY);
                aura_hora_armar(&r, s_seq++, ms);
                xSemaphoreGive(s_lock_envio);
                enviar_bytes(&de, (const uint8_t *)&r, aura_trama_bytes(&r));
                continue;
            }
        }

        char hw[AURA_HW_ID_BYTES];
        aura_hw_id_de_mac(de.addr, hw);

        if (t.tipo == AURA_TIPO_TELEMETRIA && t.largo >= AURA_TELEMETRIA_CABECERA) {
            char values[AURA_VALUES_MAX + 1];
            size_t n = t.largo - AURA_TELEMETRIA_CABECERA;
            memcpy(values, t.payload + AURA_TELEMETRIA_CABECERA, n);
            values[n] = '\0';

            uint32_t ts_s = aura_u32_leer(t.payload);
            uint64_t ts_ms = (uint64_t)ts_s * 1000;

            if (s_telemetria_cb != NULL) {
                s_telemetria_cb(de.addr, hw, values, ts_ms);
            }
        }

        bool permitir_reenvio = true;
        if (s_filtro_local_cb != NULL) {
            permitir_reenvio = s_filtro_local_cb(de.addr, &t);
        }

        if (permitir_reenvio) {
            lote_agregar(de.addr, buf, d.size);
            if (t.tipo != AURA_TIPO_TELEMETRIA) {
                lote_mandar();
            }
        }
    }
}

static void manejador_mesh(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    switch (id) {
    case MESH_EVENT_STARTED:
        anunciar_aula();
        break;
    case MESH_EVENT_PARENT_CONNECTED: {
        mesh_event_connected_t *c = (mesh_event_connected_t *)data;
        s_conectado = true;
        s_reconecto = true;
        s_fallos_envio = 0;
        ESP_LOGI(TAG, "Conectado al padre " MACSTR " (capa %d, canal %d)",
                 MAC2STR(c->connected.bssid), esp_mesh_get_layer(), c->connected.channel);
        anunciar_aula();
        if (s_estado_cb) {
            s_estado_cb(true, s_hijos);
        }
        break;
    }
    case MESH_EVENT_PARENT_DISCONNECTED:
        s_conectado = false;
        ESP_LOGW(TAG, "Desconectado del padre, buscando nuevo padre...");
        if (s_estado_cb) {
            s_estado_cb(false, s_hijos);
        }
        break;
    case MESH_EVENT_NO_PARENT_FOUND:
        ESP_LOGW(TAG, "No se encontro padre (verificar gateway activo y MESH_ID)");
        break;
    case MESH_EVENT_CHILD_CONNECTED: {
        mesh_event_child_connected_t *c = (mesh_event_child_connected_t *)data;
        s_hijos++;
        ESP_LOGI(TAG, "Hijo conectado: " MACSTR " (aid %d, total %d)", MAC2STR(c->mac), c->aid, s_hijos);
        if (s_estado_cb) {
            s_estado_cb(s_conectado, s_hijos);
        }
        break;
    }
    case MESH_EVENT_CHILD_DISCONNECTED: {
        mesh_event_child_disconnected_t *c = (mesh_event_child_disconnected_t *)data;
        if (s_hijos > 0) {
            s_hijos--;
        }
        ESP_LOGW(TAG, "Hijo desconectado: " MACSTR " (total %d)", MAC2STR(c->mac), s_hijos);
        if (s_estado_cb) {
            s_estado_cb(s_conectado, s_hijos);
        }
        break;
    }
    default:
        break;
    }
}

esp_err_t mesh_net_init(const mesh_net_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    s_lock_envio = xSemaphoreCreateMutex();
    s_lock_lote = xSemaphoreCreateMutex();
    s_lock_hojas = xSemaphoreCreateMutex();
    s_cola_comandos = xQueueCreate(8, sizeof(comando_interno_t));
    aura_lote_vaciar(&s_lote);

    nvs_handle_t h;
    if (nvs_open("concentrador", NVS_READONLY, &h) == ESP_OK) {
        size_t n = sizeof(s_aula);
        if (nvs_get_str(h, "aula", s_aula, &n) != ESP_OK || !aura_aula_valida(s_aula)) {
            s_aula[0] = '\0';
        }
        nvs_close(h);
    }
    if (s_aula[0] == '\0' && cfg->aula_por_defecto != NULL && aura_aula_valida(cfg->aula_por_defecto)) {
        strlcpy(s_aula, cfg->aula_por_defecto, sizeof(s_aula));
    }

    esp_read_mac(s_mi_mac, ESP_MAC_WIFI_STA);
    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(s_mi_mac, hw);
    ESP_LOGI(TAG, "Inicializando Concentrador %s | Aula configurada: %s",
             hw, s_aula[0] ? s_aula : "(sin asignar)");

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *netif_sta = NULL, *netif_ap = NULL;
    ESP_ERROR_CHECK(esp_netif_create_default_wifi_mesh_netifs(&netif_sta, &netif_ap));

    wifi_init_config_t wcfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wcfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_country_code("AR", false));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_mesh_init());
    ESP_ERROR_CHECK(esp_event_handler_register(MESH_EVENT, ESP_EVENT_ANY_ID, &manejador_mesh, NULL));
    ESP_ERROR_CHECK(esp_mesh_fix_root(true));
    ESP_ERROR_CHECK(esp_mesh_set_max_layer(cfg->max_capas ? cfg->max_capas : 6));
    ESP_ERROR_CHECK(esp_mesh_disable_ps());
    ESP_ERROR_CHECK(esp_mesh_set_ap_authmode(WIFI_AUTH_WPA2_PSK));

    mesh_cfg_t mcfg = MESH_INIT_CONFIG_DEFAULT();
    memcpy((uint8_t *)&mcfg.mesh_id, cfg->mesh_id, 6);
    mcfg.channel = 0;
    mcfg.allow_channel_switch = true;
    mcfg.router.ssid_len = strlen(ROUTER_FICTICIO);
    memcpy(mcfg.router.ssid, ROUTER_FICTICIO, mcfg.router.ssid_len);
    mcfg.mesh_ap.max_connection = cfg->max_hijos ? cfg->max_hijos : 6;
    mcfg.mesh_ap.nonmesh_max_connection = 0;
    if (cfg->mesh_password != NULL) {
        memcpy(mcfg.mesh_ap.password, cfg->mesh_password, strlen(cfg->mesh_password));
    }
    ESP_ERROR_CHECK(esp_mesh_set_config(&mcfg));
    ESP_ERROR_CHECK(esp_mesh_send_block_time(LIMITE_ENVIO_MS));

    return ESP_OK;
}

esp_err_t mesh_net_start(void)
{
    ESP_ERROR_CHECK(esp_mesh_start());

    xTaskCreate(tarea_recepcion, "mesh_rx", 6144, NULL, 5, NULL);
    xTaskCreate(tarea_lote, "lote_tx", 3072, NULL, 5, NULL);
    xTaskCreate(tarea_estado, "mesh_status", 4096, NULL, 4, NULL);

    return ESP_OK;
}

void mesh_net_set_telemetria_cb(mesh_net_telemetria_cb_t cb)
{
    s_telemetria_cb = cb;
}

void mesh_net_set_estado_cb(mesh_net_estado_cb_t cb)
{
    s_estado_cb = cb;
}

void mesh_net_set_filtro_local_cb(mesh_net_filtro_local_cb_t cb)
{
    s_filtro_local_cb = cb;
}

bool mesh_net_is_conectado(void)
{
    return s_conectado;
}

int mesh_net_get_hijos(void)
{
    return s_hijos;
}

const char *mesh_net_get_aula(void)
{
    return s_aula;
}

esp_err_t mesh_net_set_aula(const char *nueva_aula)
{
    if (nueva_aula == NULL || !aura_aula_valida(nueva_aula)) {
        return ESP_ERR_INVALID_ARG;
    }

    nvs_handle_t h;
    esp_err_t err = nvs_open("concentrador", NVS_READWRITE, &h);
    if (err != ESP_OK) {
        return err;
    }
    err = nvs_set_str(h, "aula", nueva_aula);
    if (err == ESP_OK) {
        err = nvs_commit(h);
    }
    nvs_close(h);

    if (err == ESP_OK) {
        bool cambio = (strcmp(s_aula, nueva_aula) != 0);
        strlcpy(s_aula, nueva_aula, sizeof(s_aula));
        anunciar_aula();

        if (cambio) {
            ESP_LOGW(TAG, "Cambio de aula: liberando %d hojas conectadas", s_hijos);
            esp_wifi_deauth_sta(0);
            xSemaphoreTake(s_lock_hojas, portMAX_DELAY);
            s_cant_hojas = 0;
            xSemaphoreGive(s_lock_hojas);
        }
    }
    return err;
}

esp_err_t mesh_net_enviar_comando_hoja(const uint8_t mac_hoja[6], const char *comando_json)
{
    if (mac_hoja == NULL || comando_json == NULL || !s_conectado) {
        return ESP_ERR_INVALID_STATE;
    }
    mesh_addr_t dest;
    memcpy(dest.addr, mac_hoja, 6);
    bool ok = enviar_trama(&dest, AURA_TIPO_COMANDO, comando_json, strlen(comando_json));
    return ok ? ESP_OK : ESP_FAIL;
}

esp_err_t mesh_net_enviar_comando_ultima_hoja(const char *comando_json)
{
    xSemaphoreTake(s_lock_hojas, portMAX_DELAY);
    int mejor = -1;
    for (int i = 0; i < s_cant_hojas; i++) {
        if (s_hojas[i].aula[0] && strcmp(s_hojas[i].aula, s_aula) != 0) {
            continue;
        }
        if (mejor < 0 || (int32_t)(s_hojas[i].visto - s_hojas[mejor].visto) > 0) {
            mejor = i;
        }
    }
    uint8_t mac[6];
    bool encontrada = false;
    if (mejor >= 0) {
        memcpy(mac, s_hojas[mejor].mac, 6);
        encontrada = true;
    }
    xSemaphoreGive(s_lock_hojas);

    if (!encontrada) {
        return ESP_ERR_NOT_FOUND;
    }
    return mesh_net_enviar_comando_hoja(mac, comando_json);
}

size_t mesh_net_get_hojas(mesh_net_hoja_info_t *out_hojas, size_t max_hojas)
{
    if (out_hojas == NULL || max_hojas == 0) {
        return 0;
    }
    xSemaphoreTake(s_lock_hojas, portMAX_DELAY);
    size_t n = (size_t)s_cant_hojas < max_hojas ? (size_t)s_cant_hojas : max_hojas;
    TickType_t ahora = xTaskGetTickCount();
    for (size_t i = 0; i < n; i++) {
        memcpy(out_hojas[i].mac, s_hojas[i].mac, 6);
        aura_hw_id_de_mac(s_hojas[i].mac, out_hojas[i].hw_id);
        strlcpy(out_hojas[i].aula, s_hojas[i].aula, sizeof(out_hojas[i].aula));
        out_hojas[i].ultimo_visto_ms = (uint32_t)pdTICKS_TO_MS(ahora - s_hojas[i].visto);
    }
    xSemaphoreGive(s_lock_hojas);
    return n;
}
