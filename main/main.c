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

#define ROUTER_SSID CONFIG_ROUTER_SSID
#define ROUTER_PASS CONFIG_ROUTER_PASS

static const char *TAG = "mesh";
static esp_netif_t *netif_sta;

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

	float value = 20.0f;
	while (true) {
		if (esp_mesh_is_root()) {
			uint8_t buf[sizeof(float)];
			mesh_addr_t from;
			mesh_data_t data = { .data = buf, .size = sizeof(buf) };
			int flag = 0;
			if (esp_mesh_recv(&from, &data, 2000, &flag, NULL, 0) == ESP_OK) {
				float received;
				memcpy(&received, buf, sizeof(received));
				ESP_LOGI(TAG, "de " MACSTR ": %.2f", MAC2STR(from.addr), received);
			}
		} else {
			mesh_data_t data = {
				.data = (uint8_t *)&value, .size = sizeof(value),
				.proto = MESH_PROTO_BIN, .tos = MESH_TOS_P2P,
			};
			esp_err_t err = esp_mesh_send(NULL, &data, MESH_DATA_P2P, NULL, 0);
			ESP_LOGI(TAG, "envio %.2f -> %s", value, esp_err_to_name(err));
			value +=0.1f;
			vTaskDelay(pdMS_TO_TICKS(2000));
		}
	}
}

