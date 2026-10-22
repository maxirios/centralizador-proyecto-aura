#pragma once

#include "aura_trama.h"
#include "aura_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Retorna una cadena constante representativa del tipo de trama AURA.
 *
 * @param tipo Código numérico del tipo de trama (AURA_TIPO_*).
 * @return const char* Nombre legible del tipo de trama.
 */
const char *aura_tipo_a_str(uint8_t tipo);

/**
 * @brief Valida exhaustivamente una trama binaria simple de AURA.
 *
 * @param d Puntero al buffer recibido.
 * @param len Longitud del buffer recibido.
 * @return aura_validacion_t Código de resultado (AURA_TRAMA_OK si es válida).
 */
aura_validacion_t aura_validar_trama_completa(const uint8_t *d, size_t len);

#ifdef __cplusplus
}
#endif
