#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_CONTROL_COLA_TX_LEN       8       /**< Capacidad de cola de comandos salientes */
#define MESH_CONTROL_CMD_ID_MAX        32      /**< Longitud maxima de command_id */

/**
 * @brief Estructura que describe el resultado de un comando ejecutado por una hoja.
 */
typedef struct {
    uint8_t de_mac[6];                         /**< MAC de la hoja que reporta el resultado */
    char command_id[MESH_CONTROL_CMD_ID_MAX];  /**< Identificador del comando correlacionado */
    bool aplicado;                             /**< true si la hoja aplico exitosamente el comando */
    char motivo[48];                           /**< Motivo de rechazo o error en caso de fallo */
    const char *raw_json;                      /**< Cadena JSON completa recibida en el resultado */
} mesh_control_resultado_t;

/**
 * @brief Callback invocado al recibir un resultado de comando (AURA_TIPO_RESULTADO).
 *
 * @param resultado Puntero a la estructura con los datos del resultado procesado.
 */
typedef void (*mesh_control_resultado_cb_t)(const mesh_control_resultado_t *resultado);

/**
 * @brief Inicializa el modulo de control y despacho de comandos hacia hojas de la malla.
 *
 * Crea la cola de comandos no bloqueante y la tarea en segundo plano encargada
 * del envio P2P a traves de la malla ESP-WIFI-MESH.
 *
 * @param resultado_cb Callback opcional para notificaciones de ejecucion (puede ser NULL).
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t mesh_control_init(mesh_control_resultado_cb_t resultado_cb);

/**
 * @brief Registra o actualiza el callback de notificacion de resultados de comandos.
 *
 * @param resultado_cb Nuevo callback (puede ser NULL para desregistrar).
 */
void mesh_control_set_resultado_cb(mesh_control_resultado_cb_t resultado_cb);

/**
 * @brief Encola un comando formateado hacia una hoja especifica sin bloquear la tarea llamadora.
 *
 * Construye el payload JSON con formato:
 * {"command": comando, "command_id": id, "params": params, "origen": origen}
 * y lo encola en la tarea de despacho para envio P2P por la malla.
 *
 * @param mac_destino Direccion MAC del nodo hoja (6 bytes).
 * @param comando Nombre del comando (ej. "led", "rele", "set_config").
 * @param params_json Cadena JSON con los parametros (ej. "{\"invertir\":true}"), o NULL.
 * @param command_id Identificador unico para correlacion. Si es NULL, se genera automaticamente.
 * @param origen Etiqueta de origen (ej. "centralizador" o "local"). Si es NULL, usa "centralizador".
 * @return esp_err_t ESP_OK si se encolo con exito, ESP_ERR_NO_MEM si la cola esta llena, o ESP_ERR_INVALID_ARG.
 */
esp_err_t mesh_control_enviar_comando(const uint8_t mac_destino[6],
                                      const char *comando,
                                      const char *params_json,
                                      const char *command_id,
                                      const char *origen);

/**
 * @brief Encola una trama AURA_TIPO_COMANDO con payload JSON crudo hacia una hoja.
 *
 * @param mac_destino Direccion MAC de destino (6 bytes).
 * @param json_cmd Cadena JSON terminada en null (maximo AURA_PAYLOAD_MAX bytes).
 * @return esp_err_t ESP_OK si se encolo, ESP_ERR_NO_MEM si cola llena, o error de validacion.
 */
esp_err_t mesh_control_enviar_raw(const uint8_t mac_destino[6], const char *json_cmd);

/**
 * @brief Procesa una trama AURA_TIPO_RESULTADO recibida desde la malla.
 *
 * Parsea el JSON, extrae command_id, aplicado y motivo, e invoca el callback registrado.
 *
 * @param de_mac Direccion MAC de la hoja remitente (6 bytes).
 * @param trama Puntero a la trama AURA recibida.
 * @return true si la trama fue procesada correctamente como resultado.
 */
bool mesh_control_procesar_resultado(const uint8_t de_mac[6], const aura_trama_t *trama);

/**
 * @brief Obtiene el siguiente numero de secuencia incremental para tramas emitidas.
 *
 * @return uint16_t Numero de secuencia incremental.
 */
uint16_t mesh_control_siguiente_seq(void);

#ifdef __cplusplus
}
#endif
