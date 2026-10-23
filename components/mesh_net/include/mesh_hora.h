#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_trama.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_HORA_REINTENTO_MS   5000    // Intervalo de solicitud de hora a la raiz sin sincronizar (ms)
#define MESH_HORA_RESYNC_MS      3600000 // Intervalo de resincronizacion periodica con la raiz (1 hora)

// Callback para enviar tramas binarias de hora por la red mesh
typedef bool (*mesh_hora_enviar_cb_t)(const uint8_t *mac, const uint8_t *data, size_t len);

// Inicializa sincronizacion horaria y tarea periodica de consulta hacia la raiz
esp_err_t mesh_hora_init(mesh_hora_enviar_cb_t callback);

// Retorna timestamp UTC actual en milisegundos, o 0 si no esta sincronizado
uint64_t mesh_hora_ahora_ms(void);

// Retorna true si el reloj del sistema cuenta con una hora UTC valida
bool mesh_hora_es_valida(void);

// Ajusta el reloj del sistema con el timestamp UTC provisto por la raiz
void mesh_hora_ajustar(uint64_t ms_utc);

// Solicita sincronizacion inmediata con la raiz (ej: al conectar con el padre)
void mesh_hora_pedir_sincronizacion(void);

// Procesa trama AURA_TIPO_HORA (responde a hojas si tiene hora valida, o ajusta hora local)
bool mesh_hora_procesar_trama(const uint8_t de_mac[6], const aura_trama_t *trama);

#ifdef __cplusplus
}
#endif
