#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_TOUCH_I2C_NUM          I2C_NUM_0
#define BSP_TOUCH_I2C_SDA_PIN      8
#define BSP_TOUCH_I2C_SCL_PIN      9
#define BSP_TOUCH_I2C_FREQ_HZ      400000

#define BSP_TOUCH_GT911_ADDR_PRIM  0x5D
#define BSP_TOUCH_GT911_ADDR_SEC   0x14

/**
 * @brief Estructura de datos para coordenadas tactiles leidas del GT911.
 */
typedef struct {
    uint16_t x;             /**< Coordenada X mapeada a portrait (0..479) */
    uint16_t y;             /**< Coordenada Y mapeada a portrait (0..799) */
    uint8_t puntos;         /**< Cantidad de puntos detectados (0 si no hay toque) */
    bool presionado;        /**< true si la pantalla esta siendo presionada */
} bsp_touch_data_t;

/**
 * @brief Inicializa el bus I2C y el controlador tactil Goodix GT911.
 *
 * Configura los pines I2C y detecta la direccion activa del GT911.
 *
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t bsp_touch_init(void);

/**
 * @brief Lee el estado del panel tactil y devuelve coordenadas mapeadas a orientacion vertical.
 *
 * @param[out] data Puntero a la estructura donde almacenar las coordenadas leidas.
 * @return esp_err_t ESP_OK si la lectura fue correcta, ESP_FAIL si hubo error en bus I2C.
 */
esp_err_t bsp_touch_read(bsp_touch_data_t *data);

#ifdef __cplusplus
}
#endif
