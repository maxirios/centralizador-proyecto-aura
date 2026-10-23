#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_LCD_H_RES              800     /**< Resolucion horizontal nativa del panel ST7262 */
#define BSP_LCD_V_RES              480     /**< Resolucion vertical nativa del panel ST7262 */
#define BSP_LCD_PORTRAIT_WIDTH     480     /**< Ancho util en orientacion portrait */
#define BSP_LCD_PORTRAIT_HEIGHT    800     /**< Alto util en orientacion portrait */

/**
 * @brief Inicializa el bus I2C maestro compartido para periféricos (retroiluminación CH422G y táctil GT911).
 *
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t bsp_i2c_init(void);

/**
 * @brief Inicializa el bus I2C y el expansor de E/S CH422G para el control de retroiluminacion.
 *
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t bsp_display_backlight_init(void);

/**
 * @brief Controla el estado de encendido de la retroiluminacion (backlight) del panel.
 *
 * @param on true para encender, false para apagar.
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t bsp_display_set_backlight(bool on);

/**
 * @brief Inicializa el panel LCD RGB (ST7262) con framebuffers alojados en PSRAM octal.
 *
 * @param[out] out_panel_handle Puntero para recibir el handle del panel LCD creado (opcional, puede ser NULL).
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t bsp_display_init(esp_lcd_panel_handle_t *out_panel_handle);

/**
 * @brief Obtiene el handle del panel LCD RGB activo.
 *
 * @return esp_lcd_panel_handle_t Handle del panel o NULL si no fue inicializado.
 */
esp_lcd_panel_handle_t bsp_display_get_panel_handle(void);

#ifdef __cplusplus
}
#endif
