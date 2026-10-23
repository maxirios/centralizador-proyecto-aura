#pragma once

#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Inicializa tarea FreeRTOS de LVGL v9, registra panel RGB ST7262 y touch GT911 en portrait
esp_err_t ui_port_init(void);

// Adquiere o libera el mutex de LVGL para operaciones graficas
bool ui_port_lock(uint32_t timeout_ms);
void ui_port_unlock(void);

// Retorna el display principal de LVGL activo
lv_display_t *ui_port_get_display(void);

#ifdef __cplusplus
}
#endif
