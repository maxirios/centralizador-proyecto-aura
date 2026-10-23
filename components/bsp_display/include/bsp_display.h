#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_LCD_H_RES              800
#define BSP_LCD_V_RES              480
#define BSP_LCD_PORTRAIT_WIDTH     480
#define BSP_LCD_PORTRAIT_HEIGHT    800

// Bus I2C maestro compartido (SDA=8, SCL=9 a 400kHz) para CH422G y GT911
esp_err_t bsp_i2c_init(void);

// Configura expansor CH422G en 0x24/0x38 y enciende retroiluminacion
esp_err_t bsp_display_backlight_init(void);

// Controla backlight via CH422G manteniendo LCD_RST y TP_RST en alto
esp_err_t bsp_display_set_backlight(bool on);

// Inicializa panel RGB ST7262 con FB en PSRAM octal y bounce buffer de 10 lineas en DRAM
esp_err_t bsp_display_init(esp_lcd_panel_handle_t *out_panel_handle);

// Retorna el handle del panel LCD activo o NULL si no fue inicializado
esp_lcd_panel_handle_t bsp_display_get_panel_handle(void);

#ifdef __cplusplus
}
#endif
