idf_component_register(
    SRCS "bsp_display.c" "bsp_touch.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_lcd esp_driver_gpio driver esp_timer
)
