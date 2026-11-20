file(GLOB_RECURSE UI_SRCS "ui/*.c")

idf_component_register(
    SRCS
        "main.c"
        "relay_ctrl.c"
        "actions.c"
        "vars.c"
        ${UI_SRCS}
    INCLUDE_DIRS
        "."
        "ui"
        "${CMAKE_CURRENT_LIST_DIR}/../managed_components/lvgl__lvgl/include"
    REQUIRES
        nvs_flash
        esp_wifi
        esp_netif
        esp_event
        aura_protocol
        mesh_net
        esp_driver_gpio
        bsp_display
        ui
        lvgl
        esp_lvgl_port
)
