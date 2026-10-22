#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_LOTE_VENTANA_MS    50      /**< Ventana de acumulación de tramas de telemetría (ms) */

/**
 * @brief Callback para enviar el buffer binario del lote consolidado hacia el Gateway Root.
 */
typedef bool (*mesh_lote_enviar_cb_t)(const uint8_t *data, size_t len);

/**
 * @brief Inicializa el módulo de lotes, el mutex de sincronización y la tarea periódica.
 *
 * @param callback Función de envío hacia la raíz de la malla.
 * @return esp_err_t ESP_OK en caso de éxito.
 */
esp_err_t mesh_lote_init(mesh_lote_enviar_cb_t callback);

/**
 * @brief Agrega una trama al lote activo.
 * Si es prioritaria (Alertas, Resultados, Reportes) o si el buffer se llena,
 * se transmite inmediatamente hacia el Gateway.
 *
 * @param mac Dirección MAC del nodo hoja emisor (6 bytes).
 * @param trama Puntero al buffer de la trama binaria.
 * @param largo Longitud de la trama.
 * @param prioritario Si es true, fuerza el despacho inmediato del lote.
 * @return esp_err_t ESP_OK si se procesó correctamente.
 */
esp_err_t mesh_lote_agregar(const uint8_t mac[6], const uint8_t *trama, size_t largo, bool prioritario);

/**
 * @brief Fuerza el despacho inmediato del lote acumulado actual.
 */
void mesh_lote_flush(void);

/**
 * @brief Retorna la cantidad de tramas acumuladas en el lote en curso.
 */
uint8_t mesh_lote_cantidad_actual(void);

#ifdef __cplusplus
}
#endif
