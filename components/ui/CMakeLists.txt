idf_component_register(
    SRCS "ui_bridge.c"
    INCLUDE_DIRS "include"
    REQUIRES mesh_net aura_protocol esp_timer esp_lvgl_port lvgl bsp_display
)
