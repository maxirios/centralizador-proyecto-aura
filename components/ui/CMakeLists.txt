idf_component_register(
    SRCS "ui_bridge.c"
    INCLUDE_DIRS "include"
    REQUIRES mesh_net aura_protocol json esp_timer
)
