idf_component_register(
    SRCS "mesh_net.c" "mesh_lote.c" "mesh_hora.c" "mesh_isla.c" "mesh_hojas.c" "mesh_control.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_wifi nvs_flash aura_protocol esp_timer esp_system
)
