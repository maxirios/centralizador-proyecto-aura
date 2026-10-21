idf_component_register(
    SRCS "mesh_net.c"
    INCLUDE_DIRS "include"
    REQUIRES aura_mesh esp_wifi esp_netif esp_event nvs_flash
    PRIV_REQUIRES espressif__cjson
)
