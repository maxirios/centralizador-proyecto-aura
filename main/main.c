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

static void on_mesh_event(void *arg, esp_event_base_t base, int32_t id, void *data) {
	if (id == MESH_EVENT_PARENT_CONNECTED && esp_mesh_is_root()) {
		esp_netif_dhcpc_start(netif_sta);
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

	ESP_ERROR_CHECK(esp_mesh_init());
	ESP_ERROR_CHECK(esp_event_handler_register(MESH_EVENT, ESP_EVENT_ANY_ID,
						   &on_mesh_event, NULL));

	mesh_cfg_t cfg = MESH_INIT_CONFIG_DEFAULT();
	memcpy(cfg.mesh_id.addr, "MESH01", 6);
	cfg.router.ssid_len = strlen(ROUTER_SSID);
	memcpy(cfg.router.ssid, ROUTER_SSID, cfg.router.ssid_len);
	memcpy(cfg.router.password, ROUTER_PASS, strlen(ROUTER_PASS));
	cfg.mesh_ap.max_connection = 4;
	ESP_ERROR_CHECK(esp_mesh_set_config(&cfg));
	ESP_ERROR_CHECK(esp_mesh_start());

	ESP_ERROR_CHECK(mesh_net_init());
	ESP_ERROR_CHECK(mesh_net_anunciar_aula());
	ESP_ERROR_CHECK(mesh_lote_init(enviar_a_raiz_cb));

	uint8_t rx_buf[AURA_TRAMA_MAX];
	while (true) {
		mesh_addr_t from;
		mesh_data_t data = { .data = rx_buf, .size = sizeof(rx_buf) };
		int flag = 0;
		if (esp_mesh_recv(&from, &data, 1000, &flag, NULL, 0) == ESP_OK) {
			aura_validacion_t v = aura_trama_validar(rx_buf, data.size);
			if (v == AURA_TRAMA_OK) {
				const aura_trama_t *t = (const aura_trama_t *)rx_buf;
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

