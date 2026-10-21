#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "esp_mesh.h"
#include "aura_trama.h"
#include "aura_util.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_NET_AULA_MAX       AURA_AULA_MAX
#define MESH_NET_HW_ID_BYTES    AURA_HW_ID_BYTES
#define MESH_NET_MAX_HOJAS      8

typedef struct {
    uint8_t mac[6];
    char hw_id[MESH_NET_HW_ID_BYTES];
    char aula[MESH_NET_AULA_MAX];
    uint32_t ultimo_visto_ms;
} mesh_net_hoja_info_t;

typedef struct {
    uint8_t mesh_id[6];
    const char *mesh_password;
    const char *aula_por_defecto;   /* Aula inicial si la NVS está vacía; NULL para esperar set_config */
    uint8_t max_capas;              /* Límite de saltos en la malla (por defecto 6) */
    uint8_t max_hijos;              /* Límite de nodos hoja conectados directamente (por defecto 6) */
} mesh_net_config_t;

/* Callback invocado cuando llega una telemetría válida de una hoja asignada al aula */
typedef void (*mesh_net_telemetria_cb_t)(const uint8_t mac[6], const char *hw_id, const char *values_json, uint64_t ts_ms);

/* Callback invocado cuando cambia la conexión con el nodo raíz (Gateway) o la cantidad de hijos */
typedef void (*mesh_net_estado_cb_t)(bool conectado_raiz, int cantidad_hijos);

/* Callback para decisiones locales / filtros offline (retorna true para reenviar al Gateway) */
typedef bool (*mesh_net_filtro_local_cb_t)(const uint8_t mac[6], const aura_trama_t *trama);

/* API de Inicialización y control */
esp_err_t mesh_net_init(const mesh_net_config_t *cfg);
esp_err_t mesh_net_start(void);

/* Registro de callbacks para la interfaz gráfica y lógica offline */
void mesh_net_set_telemetria_cb(mesh_net_telemetria_cb_t cb);
void mesh_net_set_estado_cb(mesh_net_estado_cb_t cb);
void mesh_net_set_filtro_local_cb(mesh_net_filtro_local_cb_t cb);

/* Consulta de estado */
bool mesh_net_is_conectado(void);
int  mesh_net_get_hijos(void);
const char *mesh_net_get_aula(void);
esp_err_t mesh_net_set_aula(const char *nueva_aula);

/* Envío de comandos hacia los nodos hoja del aula (desde UI táctil o reglas locales) */
esp_err_t mesh_net_enviar_comando_hoja(const uint8_t mac_hoja[6], const char *comando_json);
esp_err_t mesh_net_enviar_comando_ultima_hoja(const char *comando_json);

/* Consulta de nodos hoja detectados y activos */
size_t mesh_net_get_hojas(mesh_net_hoja_info_t *out_hojas, size_t max_hojas);

#ifdef __cplusplus
}
#endif
