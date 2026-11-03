#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_HORA_REINTENTO_MS   5000    /**< Intervalo de solicitud de hora a la raiz sin sincronizar (ms) */
#define MESH_HORA_RESYNC_MS      3600000 /**< Intervalo de resincronizacion periodica con la raiz (1 hora) */

/**
 * @brief Callback para enviar tramas binarias de hora por la red mesh.
 * @param mac Direccion MAC de destino (6 bytes) o NULL para enviar a la raiz (Gateway Root).
 * @param data Puntero a los bytes de la trama binaria.
 * @param len Longitud en bytes de la trama.
 * @return true si se transmitio exitosamente.
 */
typedef bool (*mesh_hora_enviar_cb_t)(const uint8_t *mac, const uint8_t *data, size_t len);

/**
 * @brief Inicializa el modulo de sincronizacion y respuesta horaria.
 *
 * Crea el mutex de sincronizacion y lanza la tarea periodica de consulta hacia la raiz.
 *
 * @param callback Callback para transmitir tramas de red mesh.
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t mesh_hora_init(mesh_hora_enviar_cb_t callback);

/**
 * @brief Obtiene el timestamp UTC actual en milisegundos.
 *
 * @return uint64_t Milisegundos UTC si el reloj es valido (>= AURA_EPOCA_MINIMA), o 0 si no esta sincronizado.
 */
uint64_t mesh_hora_ahora_ms(void);

/**
 * @brief Verifica si el reloj del sistema cuenta con una hora UTC valida.
 *
 * @return true si el reloj esta sincronizado.
 */
bool mesh_hora_es_valida(void);

/**
 * @brief Ajusta el reloj del sistema con el timestamp UTC provisto por la raiz.
 *
 * @param ms_utc Milisegundos UTC.
 */
void mesh_hora_ajustar(uint64_t ms_utc);

/**
 * @brief Notifica o solicita sincronizacion inmediata con la raiz (ej: al conectar con el padre).
 */
void mesh_hora_pedir_sincronizacion(void);

/**
 * @brief Procesa una trama de tipo AURA_TIPO_HORA.
 *
 * Si es una respuesta de la raiz (8 bytes): ajusta el reloj local y retorna true.
 * Si es un pedido de una hoja (0 bytes) y el reloj local es valido: responde inmediatamente
 * con la hora UTC local a la MAC de la hoja y retorna true.
 * Si es un pedido de una hoja pero la hora local aun no es valida: retorna false (permitiendo
 * que sea derivada y acumulada hacia la raiz).
 *
 * @param de_mac MAC del nodo emisor de la trama.
 * @param trama Puntero a la trama recibida.
 * @return true si la trama fue atendida y consumida localmente.
 *         false si la trama no pudo resolverse localmente.
 */
bool mesh_hora_procesar_trama(const uint8_t de_mac[6], const aura_trama_t *trama);

#ifdef __cplusplus
}
#endif
