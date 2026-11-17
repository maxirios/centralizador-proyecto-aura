#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AURA_MAX_LOCAL_RELAYS 8

// Inicializa los GPIOs de los reles locales configurados en menuconfig
esp_err_t relay_ctrl_init(void);

// Cantidad de reles locales configurados (1 a AURA_MAX_LOCAL_RELAYS)
int relay_ctrl_get_count(void);

// Obtiene el estado actual (true = ON, false = OFF) del rele idx (0..count-1)
bool relay_ctrl_get_state(int idx);

// Fija el estado del rele idx y actualiza su GPIO fisico si corresponde
void relay_ctrl_set_state(int idx, bool on);

// Conmuta el estado del rele idx y retorna el nuevo estado
bool relay_ctrl_toggle(int idx);

// Retorna la etiqueta configurada en menuconfig (cadena vacia "" si no tiene)
const char *relay_ctrl_get_label(int idx);

// Retorna el GPIO configurado para el rele idx (-1 si esta deshabilitado)
int relay_ctrl_get_gpio(int idx);

#ifdef __cplusplus
}
#endif
