#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_CONTROL_COLA_TX_LEN       8   // Capacidad de cola de comandos salientes
#define MESH_CONTROL_CMD_ID_MAX        32  // Longitud maxima de command_id

// Resultado de un comando ejecutado por una hoja (AURA_TIPO_RESULTADO)
typedef struct {
    uint8_t de_mac[6];
    char command_id[MESH_CONTROL_CMD_ID_MAX];
    bool aplicado;
    char motivo[48];
    const char *raw_json;
} mesh_control_resultado_t;

typedef void (*mesh_control_resultado_cb_t)(const mesh_control_resultado_t *resultado);

// Inicializa cola de comandos y tarea en segundo plano para envio P2P
esp_err_t mesh_control_init(mesh_control_resultado_cb_t resultado_cb);

// Registra o actualiza el callback de notificacion de resultados
void mesh_control_set_resultado_cb(mesh_control_resultado_cb_t resultado_cb);

// Encola comando formateado hacia una hoja sin bloquear. command_id y origen son opcionales.
esp_err_t mesh_control_enviar_comando(const uint8_t mac_destino[6],
                                      const char *comando,
                                      const char *params_json,
                                      const char *command_id,
                                      const char *origen);

// Encola trama AURA_TIPO_COMANDO con payload JSON crudo (max 180 B)
esp_err_t mesh_control_enviar_raw(const uint8_t mac_destino[6], const char *json_cmd);

// Parsea trama AURA_TIPO_RESULTADO e invoca el callback si corresponde
bool mesh_control_procesar_resultado(const uint8_t de_mac[6], const aura_trama_t *trama);

// Retorna numero de secuencia incremental para tramas emitidas
uint16_t mesh_control_siguiente_seq(void);

#ifdef __cplusplus
}
#endif
