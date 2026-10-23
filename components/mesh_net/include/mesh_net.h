#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "aura_util.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_AURA_AULA_DEFAULT
#define CONFIG_AURA_AULA_DEFAULT "aula-1"
#endif

// Inicializa gestor de red del centralizador y carga el aula desde NVS
esp_err_t mesh_net_init(void);

// Retorna el nombre del aula actualmente configurada
const char *mesh_net_get_aula(void);

// Configura y persiste una nueva aula en NVS y actualiza balizas Wi-Fi Vendor IE
esp_err_t mesh_net_set_aula(const char *nueva_aula);

// Inyecta Vendor IE (OUI 0x02,0xA5,0x52, rol concentrador, MAC, aula) en beacons Wi-Fi
esp_err_t mesh_net_anunciar_aula(void);

// Parsea comandos remotos JSON de configuracion (ej. set_config {"aula": "..."})
esp_err_t mesh_net_procesar_comando_config(const char *json_str, char *respuesta, size_t max_len);

#ifdef __cplusplus
}
#endif
