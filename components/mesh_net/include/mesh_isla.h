#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESH_ISLA_TRAS_S         60          // Tiempo sin nodo raiz para activar modo isla (segundos)
#define MESH_ISLA_REVISAR_S      30          // Intervalo de escaneo de gateway en canal propio (segundos)
#define MESH_ISLA_REVISAR_TODO_S 300         // Intervalo de escaneo de gateway en todos los canales (segundos)
#define MESH_ROUTER_ISLA         "aura-isla" // SSID ficticio utilizado durante modo isla

// Inicializa modo isla, recupera estado RTC/NVS y lanza tarea de monitoreo en segundo plano
esp_err_t mesh_isla_init(const uint8_t mesh_id[6]);

// Retorna true si el nodo opera actualmente como raiz local de la isla
bool mesh_isla_esta_activa(void);

// Retorna el canal de RF actual (1 a 13)
uint8_t mesh_isla_get_canal(void);

// Notifica conexion con nodo padre, guarda canal en NVS y cancela temporizador de caida
void mesh_isla_notificar_padre_conectado(uint8_t canal);

// Notifica desconexion con el padre e inicia cuenta regresiva para modo isla
void mesh_isla_notificar_padre_desconectado(void);

// Evalua si el escaneo Wi-Fi detecto el retorno del Gateway para volver a modo normal
void mesh_isla_procesar_escaneo(int num_aps);

// Fuerza transicion a modo isla reiniciando como raiz local
void mesh_isla_entrar(void);

// Sale de modo isla limpiando bandera RTC y reiniciando
void mesh_isla_salir(void);

#ifdef __cplusplus
}
#endif
