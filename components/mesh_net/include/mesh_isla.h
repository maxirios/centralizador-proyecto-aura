#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_ISLA_TRAS_S         60          /**< Tiempo sin nodo raiz para activar modo isla (segundos) */
#define MESH_ISLA_REVISAR_S      30          /**< Intervalo de escaneo de gateway en canal propio (segundos) */
#define MESH_ISLA_REVISAR_TODO_S 300         /**< Intervalo de escaneo de gateway en todos los canales (segundos) */
#define MESH_ROUTER_ISLA         "aura-isla" /**< SSID de router ficticio utilizado durante modo isla */

/**
 * @brief Inicializa el modulo de modo isla y recupera el estado de RTC y NVS.
 *
 * Determina si el inicio actual corresponde a una transicion transitoria a modo isla.
 * Lanza la tarea de temporizacion y monitoreo en segundo plano.
 *
 * @param mesh_id Identificador de la malla (6 bytes).
 * @return esp_err_t ESP_OK en caso de exito.
 */
esp_err_t mesh_isla_init(const uint8_t mesh_id[6]);

/**
 * @brief Consulta si el nodo esta actualmente operando en modo isla.
 *
 * @return true si esta operando como raiz local de la isla.
 * @return false si opera en modo normal conectado o buscando a la raiz global.
 */
bool mesh_isla_esta_activa(void);

/**
 * @brief Obtiene el canal de radiofrecuencia asignado para la operacion de la isla.
 *
 * @return uint8_t Canal de 1 a 13 si esta en modo isla, o el ultimo canal conocido si esta en modo normal.
 */
uint8_t mesh_isla_get_canal(void);

/**
 * @brief Notifica al modulo que el nodo se conecto exitosamente a un padre en la malla.
 *
 * Almacena el canal de operacion en NVS y cancela el temporizador de caida.
 *
 * @param canal Canal de radiofrecuencia actual (1 a 13).
 */
void mesh_isla_notificar_padre_conectado(uint8_t canal);

/**
 * @brief Notifica al modulo que se perdio la conexion con el nodo padre.
 *
 * Inicia el temporizador de cuenta regresiva para la transicion a modo isla.
 */
void mesh_isla_notificar_padre_desconectado(void);

/**
 * @brief Procesa el resultado de un escaneo Wi-Fi para detectar el retorno del Gateway.
 *
 * Si se detecta un AP de la malla con capa 1 perteneciente a la misma red mesh,
 * limpia la bandera RTC y reinicia el dispositivo para retornar a modo normal.
 *
 * @param num_aps Cantidad de puntos de acceso encontrados en el escaneo.
 */
void mesh_isla_procesar_escaneo(int num_aps);

/**
 * @brief Fuerza la transicion a modo isla reiniciando el dispositivo como raiz local.
 */
void mesh_isla_entrar(void);

/**
 * @brief Sale del modo isla borrando la bandera RTC y reiniciando a modo normal.
 */
void mesh_isla_salir(void);

#ifdef __cplusplus
}
#endif
