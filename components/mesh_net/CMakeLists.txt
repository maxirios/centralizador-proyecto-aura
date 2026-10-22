idf_component_register(
    SRCS "mesh_net.c" "mesh_lote.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_wifi nvs_flash aura_protocol
)
