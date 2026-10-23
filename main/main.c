#include <string.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_mesh.h"
#include "esp_mac.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "aura_protocol.h"
#include "mesh_net.h"
#include "mesh_lote.h"
#include "mesh_hora.h"
#include "mesh_isla.h"
#include "mesh_hojas.h"

#define ROUTER_SSID CONFIG_ROUTER_SSID
#define ROUTER_PASS CONFIG_ROUTER_PASS

static const char *TAG = "mesh";
static esp_netif_t *netif_sta;

static bool enviar_a_raiz_cb(const uint8_t *data, size_t len)
{
	mesh_data_t m_data = {
		.data = (uint8_t *)data,
		.size = len,
		.proto = MESH_PROTO_BIN,
		.tos = MESH_TOS_P2P,
	};
	esp_err_t err = esp_mesh_send(NULL, &m_data, MESH_DATA_P2P, NULL, 0);
	ESP_LOGI(TAG, "Lote AURA enviado a raiz (%u bytes) -> %s", (unsigned)len, esp_err_to_name(err));
	return (err == ESP_OK);
}

static bool enviar_trama_mesh_cb(const uint8_t *mac, const uint8_t *data, size_t len)
{
	mesh_data_t m_data = {
		.data = (uint8_t *)data,
		.size = len,
		.proto = MESH_PROTO_BIN,
		.tos = MESH_TOS_P2P,
	};
	mesh_addr_t dest;
	mesh_addr_t *p_dest = NULL;
	if (mac != NULL) {
		memcpy(dest.addr, mac, 6);
		p_dest = &dest;
	}
	esp_err_t err = esp_mesh_send(p_dest, &m_data, MESH_DATA_P2P, NULL, 0);
	if (mac != NULL) {
		ESP_LOGI(TAG, "Trama enviada a " MACSTR " (%u B) -> %s",
		         MAC2STR(mac), (unsigned)len, esp_err_to_name(err));
	} else {
		ESP_LOGI(TAG, "Trama enviada a raiz (%u B) -> %s",
		         (unsigned)len, esp_err_to_name(err));
	}
	return (err == ESP_OK);
}

static void on_mesh_event(void *arg, esp_event_base_t base, int32_t id, void *data) {
	if (id == MESH_EVENT_STARTED) {
		if (mesh_isla_esta_activa()) {
			esp_mesh_set_self_organized(false, false);
		}
	} else if (id == MESH_EVENT_SCAN_DONE) {
		if (mesh_isla_esta_activa()) {
			mesh_event_scan_done_t *s = (mesh_event_scan_done_t *)data;
			mesh_isla_procesar_escaneo(s->number);
		}
	} else if (id == MESH_EVENT_PARENT_CONNECTED) {
		mesh_event_connected_t *c = (mesh_event_connected_t *)data;
		mesh_isla_notificar_padre_conectado(c->connected.channel);
		if (esp_mesh_is_root()) {
			esp_netif_dhcpc_start(netif_sta);
		} else {
			mesh_hora_pedir_sincronizacion();
		}
	} else if (id == MESH_EVENT_PARENT_DISCONNECTED) {
		mesh_isla_notificar_padre_desconectado();
	} else if (id == MESH_EVENT_CHILD_CONNECTED) {
		mesh_event_child_connected_t *c = (mesh_event_child_connected_t *)data;
		mesh_hojas_notificar_child_connected(c->mac);
		ESP_LOGI(TAG, "Hijo conectado a la malla: " MACSTR " (aid %d)", MAC2STR(c->mac), c->aid);
	} else if (id == MESH_EVENT_CHILD_DISCONNECTED) {
		mesh_event_child_disconnected_t *c = (mesh_event_child_disconnected_t *)data;
		mesh_hojas_notificar_child_disconnected(c->mac);
		ESP_LOGW(TAG, "Hijo desconectado de la malla: " MACSTR, MAC2STR(c->mac));
	}
}

void app_main(void) {
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_LOGI(TAG, "Protocolo AURA v%d cargado (cabecera %d B, payload max %d B)",
	         AURA_PROTO_VERSION, AURA_CABECERA_BYTES, AURA_PAYLOAD_MAX);
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());
	ESP_ERROR_CHECK(esp_netif_create_default_wifi_mesh_netifs(&netif_sta, NULL));

	wifi_init_config_t wifi_cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&wifi_cfg));
	ESP_ERROR_CHECK(esp_wifi_start());

	ESP_ERROR_CHECK(mesh_isla_init((const uint8_t *)"MESH01"));

	ESP_ERROR_CHECK(esp_mesh_init());
	ESP_ERROR_CHECK(esp_event_handler_register(MESH_EVENT, ESP_EVENT_ANY_ID,
						   &on_mesh_event, NULL));

	mesh_cfg_t cfg = MESH_INIT_CONFIG_DEFAULT();
	memcpy(cfg.mesh_id.addr, "MESH01", 6);
	const char *router = mesh_isla_esta_activa() ? MESH_ROUTER_ISLA : ROUTER_SSID;
	cfg.router.ssid_len = strlen(router);
	memcpy(cfg.router.ssid, router, cfg.router.ssid_len);
	memcpy(cfg.router.password, ROUTER_PASS, strlen(ROUTER_PASS));
	cfg.channel = mesh_isla_esta_activa() ? mesh_isla_get_canal() : 0;
	cfg.allow_channel_switch = !mesh_isla_esta_activa();
	cfg.mesh_ap.max_connection = 4;

	if (mesh_isla_esta_activa()) {
		ESP_ERROR_CHECK(esp_mesh_set_type(MESH_ROOT));
	}
	ESP_ERROR_CHECK(esp_mesh_fix_root(true));
	ESP_ERROR_CHECK(esp_mesh_set_config(&cfg));
	ESP_ERROR_CHECK(esp_mesh_start());

	ESP_ERROR_CHECK(mesh_net_init());
	ESP_ERROR_CHECK(mesh_net_anunciar_aula());
	ESP_ERROR_CHECK(mesh_hojas_init(mesh_net_get_aula(), NULL, NULL));
	ESP_ERROR_CHECK(mesh_lote_init(enviar_a_raiz_cb));
	ESP_ERROR_CHECK(mesh_hora_init(enviar_trama_mesh_cb));

	uint8_t rx_buf[AURA_TRAMA_MAX];
	while (true) {
		mesh_addr_t from;
		mesh_data_t data = { .data = rx_buf, .size = sizeof(rx_buf) };
		int flag = 0;
		if (esp_mesh_recv(&from, &data, 1000, &flag, NULL, 0) == ESP_OK) {
			aura_validacion_t v = aura_trama_validar(rx_buf, data.size);
			if (v == AURA_TRAMA_OK) {
				const aura_trama_t *t = (const aura_trama_t *)rx_buf;

				if (t->tipo == AURA_TIPO_HORA && mesh_hora_procesar_trama(from.addr, t)) {
					continue;
				}

				bool descartar_reenvio = false;
				mesh_hojas_procesar_trama(from.addr, t, &descartar_reenvio);
				if (descartar_reenvio || mesh_isla_esta_activa()) {
					continue;
				}

				bool prioritario = (t->tipo == AURA_TIPO_ALERTA ||
				                    t->tipo == AURA_TIPO_RESULTADO ||
				                    t->tipo == AURA_TIPO_REPORTE);
				ESP_LOGI(TAG, "Trama valida de " MACSTR " [%s], seq=%u, prioritario=%d",
				         MAC2STR(from.addr), aura_tipo_a_str(t->tipo), t->seq, prioritario);
				mesh_lote_agregar(from.addr, rx_buf, data.size, prioritario);
			} else {
				ESP_LOGD(TAG, "Dato recibido de " MACSTR " no es trama simple AURA (%d bytes)",
				         MAC2STR(from.addr), data.size);
			}
		}
	}
}
