#pragma once

#include "aura_trama.h"
#include "aura_util.h"

#ifdef __cplusplus
extern "C" {
#endif

// Retorna nombre legible del tipo de trama AURA (ej. "TELEMETRIA", "COMANDO")
const char *aura_tipo_a_str(uint8_t tipo);

// Valida exhaustivamente longitud y campos de una trama binaria simple de AURA
aura_validacion_t aura_validar_trama_completa(const uint8_t *d, size_t len);

#ifdef __cplusplus
}
#endif
