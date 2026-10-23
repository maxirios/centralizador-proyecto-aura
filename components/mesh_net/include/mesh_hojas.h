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

#define MESH_HOJAS_MAX                  8       // Capacidad maxima de hojas rastreadas por concentrador
#define MESH_HOJAS_AUSENTE_MS           20000   // Tiempo desconectada para marcar ausente (20 s)
#define MESH_HOJAS_GRACIA_ARRANQUE_MS   60000   // Gracia tras arranque antes de evaluar ausentes (60 s)
#define MESH_HOJAS_INTERVALO_DEFECTO_S  60      // Intervalo por defecto si la hoja no lo informo (s)

// Informacion y estado de presencia de una hoja registrada en el aula
typedef struct {
    uint8_t mac[6];
    char aula[AURA_AULA_MAX];
    uint32_t ts_mostrado;           // Timestamp UTC de la medicion mas reciente
    uint32_t intervalo_s;           // Intervalo de reporte configurado en la hoja (s)
    bool ausente;
    TickType_t visto;               // Tick del ultimo mensaje recibido
    TickType_t desconectada_desde;  // Tick de desconexion del concentrador (0 = conectada)
} mesh_hoja_info_t;

// Callback ante cambios de presencia de hojas (ausente / reconectada)
typedef void (*mesh_hoja_evento_cb_t)(const uint8_t mac[6], bool ausente, const char *motivo);

// Callback ante telemetria o estado valido no obsoleto
typedef void (*mesh_hoja_telemetria_cb_t)(const uint8_t mac[6], uint32_t ts, const char *values_json, bool es_estado);

// Inicializa tabla de monitoreo de hojas, recupera de NVS y lanza tarea periodica de ausencia
esp_err_t mesh_hojas_init(const char *aula, mesh_hoja_evento_cb_t evento_cb, mesh_hoja_telemetria_cb_t telemetria_cb);

// Actualiza el aula de operacion y recarga la lista de hojas correspondientes
void mesh_hojas_set_aula(const char *nueva_aula);

// Notifica asociacion o desasociacion de una estacion en la malla
void mesh_hojas_notificar_child_connected(const uint8_t mac[6]);
void mesh_hojas_notificar_child_disconnected(const uint8_t mac[6]);

// Procesa trama entrante de una hoja. out_descartar_reenvio=true si no debe enviarse a la raiz
bool mesh_hojas_procesar_trama(const uint8_t de_mac[6], const aura_trama_t *trama, bool *out_descartar_reenvio);

// Retorna true si hay al menos una hoja del aula marcada como ausente
bool mesh_hojas_hay_ausentes(void);

// Copia snapshot de la lista actual de hojas monitoreadas. Retorna cantidad copiada.
int mesh_hojas_get_lista(mesh_hoja_info_t *lista, size_t max_elementos);

// Retorna la MAC de la ultima hoja activa que envio datos, o false si no hay ninguna
bool mesh_hojas_get_ultima(uint8_t mac_salida[6]);

#ifdef __cplusplus
}
#endif
