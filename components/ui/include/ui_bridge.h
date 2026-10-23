#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "mesh_hojas.h"
#include "mesh_control.h"
#include "aura_util.h"

#ifdef __cplusplus
extern "C" {
#endif

// Representacion de un nodo del aula en el modelo de UI
typedef struct {
    uint8_t mac[6];
    char hw_id[AURA_HW_ID_BYTES];
    bool conectado;
    bool tiene_telemetria;
    uint32_t ts_ultimo;
    float temp;
    float hum;
    float co2;
    bool tiene_actuador;
    bool actuador_estado;
    char raw_values[AURA_VALUES_MAX + 1];
} ui_nodo_t;

// Estado general de conectividad del concentrador y red
typedef struct {
    bool gateway_conectado;
    bool modo_isla;
    uint8_t canal;
    char aula[AURA_AULA_MAX];
} ui_red_estado_t;

// Snapshot completo del estado del aula
typedef struct {
    ui_red_estado_t red;
    uint8_t cant_nodos;
    ui_nodo_t nodos[MESH_HOJAS_MAX];
} ui_estado_aula_t;

// Tipo de evento notificado a observadores de UI
typedef enum {
    UI_EVENTO_RED_CAMBIO = 0,
    UI_EVENTO_NODO_CONECTADO,
    UI_EVENTO_NODO_DESCONECTADO,
    UI_EVENTO_NODO_TELEMETRIA,
    UI_EVENTO_CONTROL_RESULTADO,
} ui_evento_tipo_t;

// Callback para notificar cambios del modelo a la vista activa
typedef void (*ui_notif_cb_t)(ui_evento_tipo_t evento, const void *datos, void *user_data);

// Inicializa el modelo de estado y el mutex de sincronizacion
esp_err_t ui_bridge_init(void);

// Registra callback de observador para la capa de presentacion
void ui_bridge_registrar_observador(ui_notif_cb_t cb, void *user_data);

// Adquiere o libera el mutex de proteccion del modelo
bool ui_bridge_lock(TickType_t timeout_ticks);
void ui_bridge_unlock(void);

// Copia snapshot consistente del estado actual del aula
esp_err_t ui_bridge_get_snapshot(ui_estado_aula_t *out_estado);

// Obtiene puntero de lectura al estado bajo lock externo
const ui_estado_aula_t *ui_bridge_get_estado_ref(void);

// Actualiza indicador de gateway y modo isla
void ui_bridge_actualizar_red(bool gateway_conectado, bool modo_isla, uint8_t canal, const char *aula);

// Handlers para conectar con callbacks de mesh_net
void ui_bridge_on_mesh_evento_hoja(const uint8_t mac[6], bool ausente, const char *motivo);
void ui_bridge_on_mesh_telemetria(const uint8_t mac[6], uint32_t ts, const char *values_json, bool es_estado);
void ui_bridge_on_control_resultado(const mesh_control_resultado_t *res);

// Despacha comando a un actuador de nodo hoja
esp_err_t ui_bridge_enviar_comando(const uint8_t dest_mac[6], const char *actuador, const char *payload_json);

// Conmuta actuador estandar (led o rele) del nodo especificado
esp_err_t ui_bridge_conmutar_actuador(const uint8_t dest_mac[6], const char *actuador);

#ifdef __cplusplus
}
#endif
