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

/**
 * @brief Inicializa el gestor de red del centralizador y carga el aula desde NVS.
 * Si no existe una entrada previa en NVS, inicializa con el valor por defecto.
 *
 * @return esp_err_t ESP_OK en caso de éxito.
 */
esp_err_t mesh_net_init(void);

/**
 * @brief Retorna el nombre del aula actualmente configurada.
 *
 * @return const char* Cadena terminada en null con el nombre del aula.
 */
const char *mesh_net_get_aula(void);

/**
 * @brief Configura y persiste una nueva aula en memoria NVS.
 * Si el aula difiere de la actual, deautentica las estaciones asociadas
 * y actualiza inmediatamente las balizas Vendor IE.
 *
 * @param nueva_aula Cadena de 1 a 15 caracteres (a-z, 0-9, '-', '_').
 * @return esp_err_t ESP_OK si fue válida y persistida, ESP_ERR_INVALID_ARG si es inválida.
 */
esp_err_t mesh_net_set_aula(const char *nueva_aula);

/**
 * @brief Inyecta los Vendor IE en los frames BEACON y PROBE_RESP del SoftAP Wi-Fi.
 * Contiene el OUI local (0x02, 0xA5, 0x52), tipo concentrador (0x01), MAC y nombre de aula.
 *
 * @return esp_err_t ESP_OK si ambas llamadas a esp_wifi_set_vendor_ie fueron exitosas.
 */
esp_err_t mesh_net_anunciar_aula(void);

/**
 * @brief Procesa comandos remotos JSON de configuración (ej. set_config {"aula": "..."}).
 *
 * @param json_str JSON entrante con el comando.
 * @param respuesta Buffer de salida para el JSON de reporte/resultado.
 * @param max_len Tamaño máximo del buffer de respuesta.
 * @return esp_err_t ESP_OK si se parseó y generó respuesta.
 */
esp_err_t mesh_net_procesar_comando_config(const char *json_str, char *respuesta, size_t max_len);

#ifdef __cplusplus
}
#endif
