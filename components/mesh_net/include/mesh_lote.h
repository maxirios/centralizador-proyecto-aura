#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_LOTE_VENTANA_MS    50      // Ventana de acumulacion de tramas de telemetria (ms)

// Callback para enviar el buffer binario del lote consolidado hacia el Gateway Root
typedef bool (*mesh_lote_enviar_cb_t)(const uint8_t *data, size_t len);

// Inicializa modulo de lotes, mutex y tarea periodica de transmision
esp_err_t mesh_lote_init(mesh_lote_enviar_cb_t callback);

// Agrega una trama al lote activo. prioritario=true fuerza despacho inmediato
esp_err_t mesh_lote_agregar(const uint8_t mac[6], const uint8_t *trama, size_t largo, bool prioritario);

// Fuerza el despacho inmediato del lote acumulado actual
void mesh_lote_flush(void);

// Retorna la cantidad de tramas acumuladas en el lote en curso
uint8_t mesh_lote_cantidad_actual(void);

#ifdef __cplusplus
}
#endif
