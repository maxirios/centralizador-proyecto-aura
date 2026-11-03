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

// Coordenadas tactiles nativas del panel (800x480). LVGL v9 aplica la rotacion al display.
typedef struct {
    uint16_t x;             // 0..799 (nativo horizontal)
    uint16_t y;             // 0..479 (nativo vertical)
    uint8_t puntos;         // Puntos detectados (0 si no hay toque)
    bool presionado;
} bsp_touch_data_t;

// Secuencia de reset (GPIO 4 + CH422G) y verificacion de GT911 en 0x5D
esp_err_t bsp_touch_init(void);

// Lee coordenadas crudas del GT911 (0..799, 0..479). No thread-safe.
esp_err_t bsp_touch_read(bsp_touch_data_t *data);

#ifdef __cplusplus
}
#endif
