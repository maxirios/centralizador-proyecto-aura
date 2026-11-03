#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Crea la vista de validacion de telemetria y control tactil en la pantalla activa
esp_err_t ui_view_test_create(void);

// Actualiza contenido de widgets con el estado actual de ui_bridge
void ui_view_test_actualizar(void);

#ifdef __cplusplus
}
#endif
