#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Crea el dashboard (header de red + pestañas Dashboard, Dispositivos, Config y Acerca de)
esp_err_t ui_dashboard_create(void);

// Redibuja resumen, control y tarjetas con el estado actual de ui_bridge (llamar con el lock de LVGL)
void ui_dashboard_actualizar(void);

#ifdef __cplusplus
}
#endif
