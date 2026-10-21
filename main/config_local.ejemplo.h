#pragma once

/*
 * Configuración local del nodo Centralizador / Intermediario (AURA ESP-MESH).
 * Copiar como config_local.h y ajustar las credenciales si es necesario.
 * Este archivo NO debe comitearse a Git si contiene credenciales de producción.
 */

// Identificador único de la malla AURA (6 bytes)
// Debe coincidir exactamente con el Gateway y las Hojas
#define CONFIG_MESH_ID_BYTES 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc

// Clave WPA2 de la malla local
#define CONFIG_MESH_AP_PASSWORD "clave-mesh-aura"

// Aula asignada por defecto (si la NVS está limpia)
#define CONFIG_MESH_AULA_DEFECTO "aula1"
