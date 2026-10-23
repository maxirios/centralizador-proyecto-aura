#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"
#include "aura_util.h"
#include "freertos/FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_HOJAS_MAX                  8       /**< Capacidad maxima de hojas rastreadas por concentrador */
#define MESH_HOJAS_AUSENTE_MS           20000   /**< Tiempo desconectada para marcar ausente (20 s) */
#define MESH_HOJAS_GRACIA_ARRANQUE_MS   60000   /**< Gracia tras arranque antes de evaluar ausentes (60 s) */
#define MESH_HOJAS_INTERVALO_DEFECTO_S  60      /**< Intervalo por defecto si la hoja no lo informo (s) */

/**
 * @brief Informacion y estado de una hoja registrada en el aula.
 */
typedef struct {
    uint8_t mac[6];                 /**< Direccion MAC de la hoja */
    char aula[AURA_AULA_MAX];       /**< Aula que informa la hoja */
    uint32_t ts_mostrado;           /**< Timestamp UTC de la medicion mas reciente mostrada */
    uint32_t intervalo_s;           /**< Intervalo de reporte telemetrico configurado en la hoja (s) */
    bool ausente;                   /**< true si la hoja esta marcada como ausente */
    TickType_t visto;               /**< Tick de recepcion del ultimo mensaje de la hoja */
    TickType_t desconectada_desde;  /**< Tick de desconexion del concentrador (0 = conectada) */
} mesh_hoja_info_t;

/**
 * @brief Callback invocado cuando una hoja pasa a estar ausente o vuelve a conectarse.
 *
 * @param mac Direccion MAC de la hoja (6 bytes).
 * @param ausente true si pasa a estar ausente, false si volvio a la red.
 * @param motivo Descripcion textual del evento (ej. "se desconecto y no volvio", "3 intervalos sin datos", "volvio").
 */
typedef void (*mesh_hoja_evento_cb_t)(const uint8_t mac[6], bool ausente, const char *motivo);

/**
 * @brief Callback invocado cuando se recibe telemetria o estado valido y no obsoleto de una hoja.
 *
 * @param mac Direccion MAC de la hoja emisora (6 bytes).
 * @param ts Timestamp UTC asociado a la medicion (0 si no cuenta con hora).
 * @param values_json Cadena JSON con los valores de los sensores/actuadores.
 * @param es_estado true si proviene de una trama AURA_TIPO_ESTADO, false si es AURA_TIPO_TELEMETRIA.
 */
typedef void (*mesh_hoja_telemetria_cb_t)(const uint8_t mac[6], uint32_t ts, const char *values_json, bool es_estado);

/**
 * @brief Inicializa la tabla de monitoreo de hojas del aula y recupera hojas previas desde NVS.
 *
 * Lanza una tarea de fondo para revision periodica de ausencia (cada 2 segundos).
 *
 * @param aula Nombre del aula actual asignada al concentrador.
 * @param evento_cb Callback de aviso ante cambios de presencia de hojas (opcional, puede ser NULL).
 * @param telemetria_cb Callback ante datos telemetricos no obsoletos (opcional, puede ser NULL).
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t mesh_hojas_init(const char *aula, mesh_hoja_evento_cb_t evento_cb, mesh_hoja_telemetria_cb_t telemetria_cb);

/**
 * @brief Actualiza el aula de operacion y recarga la lista de hojas correspondientes.
 *
 * @param nueva_aula Cadena terminada en null con el nuevo nombre de aula.
 */
void mesh_hojas_set_aula(const char *nueva_aula);

/**
 * @brief Notifica al modulo la asociacion directa de una estacion/hijo en la malla.
 *
 * @param mac Direccion MAC de la estacion conectada (6 bytes).
 */
void mesh_hojas_notificar_child_connected(const uint8_t mac[6]);

/**
 * @brief Notifica al modulo la desasociacion de una estacion/hijo en la malla.
 *
 * @param mac Direccion MAC de la estacion desconectada (6 bytes).
 */
void mesh_hojas_notificar_child_disconnected(const uint8_t mac[6]);

/**
 * @brief Procesa una trama recibida desde una hoja.
 *
 * Actualiza la presencia en la tabla, parsea reportes/estados, filtra datos atrasados
 * respecto a ts_mostrado y previene el reenvio hacia la raiz si la trama es AURA_TIPO_ESTADO.
 *
 * @param de_mac Direccion MAC del nodo emisor (6 bytes).
 * @param trama Puntero a la trama AURA recibida.
 * @param[out] out_descartar_reenvio true si la trama NO debe agregarse al lote ni reenviarse a la raiz (ej: AURA_TIPO_ESTADO o dato obsoleto).
 * @return true si la trama correspondia a una hoja del aula o fue procesada por el modulo.
 */
bool mesh_hojas_procesar_trama(const uint8_t de_mac[6], const aura_trama_t *trama, bool *out_descartar_reenvio);

/**
 * @brief Evalua si hay al menos una hoja registrada del aula que se encuentre actualmente ausente.
 *
 * @return true si existe al menos una hoja ausente.
 */
bool mesh_hojas_hay_ausentes(void);

/**
 * @brief Obtiene una copia snapshot de la lista actual de hojas monitoreadas.
 *
 * @param lista Buffer de destino.
 * @param max_elementos Capacidad maxima del buffer.
 * @return int Cantidad de elementos copiados.
 */
int mesh_hojas_get_lista(mesh_hoja_info_t *lista, size_t max_elementos);

/**
 * @brief Obtiene la direccion MAC de la ultima hoja del aula que envio datos.
 *
 * @param mac_salida Buffer de 6 bytes para almacenar la direccion MAC.
 * @return true si se conoce una hoja activa, false si aun no hay ninguna.
 */
bool mesh_hojas_get_ultima(uint8_t mac_salida[6]);

#ifdef __cplusplus
}
#endif
