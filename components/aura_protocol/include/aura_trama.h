/*
 * Trama de la mesh de AURA (versión 3 de la trama, contrato MQTT v4.0).
 *
 * Es interna de la mesh: AURA no la ve. La raíz la traduce a los tópicos hw/<hw_id>/...
 * Mismo formato que comun/protocolo_aura.h de la versión Arduino, más dos tipos nuevos
 * (HORA y LOTE), que solo existen dentro de la mesh.
 *
 *   trama:  versión(1) tipo(1) seq(2, LE) largo(1) payload(largo <= 180)
 *   LOTE:   versión(1) tipo=LOTE(1) cantidad(1) y, por cada ítem: MAC(6) largo(1) trama(largo)
 *
 * LOTE lo arma el concentrador: junta las tramas de las hojas de su aula y las manda una
 * sola vez a la raíz, con la MAC de cada hoja. Así la raíz publica cada dato con el hw_id
 * de la hoja que lo midió y no con el del concentrador que se lo entregó.
 */
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define AURA_PROTO_VERSION      3
#define AURA_PAYLOAD_MAX        180
#define AURA_CABECERA_BYTES     5
#define AURA_TRAMA_MAX          (AURA_CABECERA_BYTES + AURA_PAYLOAD_MAX)

/* Tipos. Se transmiten como uint8_t: no cambiar los valores, solo agregar. */
enum {
    AURA_TIPO_TELEMETRIA   = 1,   /* hoja -> raíz: una muestra de la cola */
    AURA_TIPO_COMANDO      = 2,   /* raíz o concentrador -> nodo: el JSON del comando */
    AURA_TIPO_ACK          = 3,   /* reservado (ESP-NOW): sin uso */
    AURA_TIPO_CONFIRMACION = 4,   /* raíz -> hoja: AURA guardó esa muestra (ack) */
    AURA_TIPO_RESULTADO    = 5,   /* nodo -> raíz: qué pasó con un comando */
    AURA_TIPO_REPORTE      = 6,   /* nodo -> raíz: config vigente y estado */
    AURA_TIPO_ALERTA       = 7,   /* nodo -> raíz: hw/<hw_id>/alerts/<tipo> */
    AURA_TIPO_PING         = 8,   /* reservado (ESP-NOW): sin uso */
    AURA_TIPO_HORA         = 9,   /* nodo -> raíz/concentrador: pedido (sin payload);
                                     respuesta: ms UTC (uint64 LE) */
    AURA_TIPO_LOTE         = 10,  /* concentrador -> raíz: tramas de varias hojas */
    AURA_TIPO_EVENTO_OK    = 11,  /* raíz -> nodo: el evento (resultado, reporte o alerta) con esa
                                     seq ya se publicó; payload: seq (uint16 LE). Sin esto el nodo
                                     lo reintenta: los eventos no se pierden en un corte. */
    AURA_TIPO_REPORTAR     = 12,  /* raíz -> nodo: volvió el broker; mandá tu reporte y lo
                                     pendiente ya (sin payload) */
    AURA_TIPO_ESTADO       = AURA_TIPO_REPORTE, /* alias: reporte de estado y configuración */
};

typedef struct __attribute__((packed)) {
    uint8_t  version;
    uint8_t  tipo;
    uint16_t seq;                 /* por nodo de origen: descarta repetidos */
    uint8_t  largo;               /* bytes útiles de payload */
    uint8_t  payload[AURA_PAYLOAD_MAX];
} aura_trama_t;

static inline void aura_trama_init(aura_trama_t *t, uint8_t tipo, uint16_t seq,
                                   const void *payload, size_t largo)
{
    memset(t, 0, sizeof(*t));
    t->version = AURA_PROTO_VERSION;
    t->tipo = tipo;
    t->seq = seq;
    t->largo = (uint8_t)(largo > AURA_PAYLOAD_MAX ? AURA_PAYLOAD_MAX : largo);
    if (payload != NULL && t->largo) {
        memcpy(t->payload, payload, t->largo);
    }
}

static inline uint16_t aura_trama_bytes(const aura_trama_t *t)
{
    return (uint16_t)(AURA_CABECERA_BYTES + t->largo);
}

typedef enum {
    AURA_TRAMA_OK = 0,
    AURA_TRAMA_CORTA,
    AURA_TRAMA_VERSION,           /* firmware de otra generación: se cuenta aparte */
    AURA_TRAMA_LARGO,
} aura_validacion_t;

/* Valida una trama simple (no LOTE) antes de interpretarla. */
static inline aura_validacion_t aura_trama_validar(const uint8_t *d, size_t len)
{
    if (d == NULL || len < AURA_CABECERA_BYTES) {
        return AURA_TRAMA_CORTA;
    }
    if (d[0] != AURA_PROTO_VERSION) {
        return AURA_TRAMA_VERSION;
    }
    if (d[4] > AURA_PAYLOAD_MAX || len != (size_t)AURA_CABECERA_BYTES + d[4]) {
        return AURA_TRAMA_LARGO;
    }
    return AURA_TRAMA_OK;
}

/* Copia el payload a un texto terminado en cero (el payload no trae terminador). */
static inline void aura_payload_texto(const aura_trama_t *t, char *salida, size_t cap)
{
    if (cap == 0) {
        return;
    }
    size_t n = t->largo < cap - 1 ? t->largo : cap - 1;
    memcpy(salida, t->payload, n);
    salida[n] = '\0';
}

/* ===== Enteros little-endian (no dependen de la alineación) ===== */
static inline void aura_u32_escribir(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}

static inline uint32_t aura_u32_leer(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static inline void aura_u64_escribir(uint8_t *p, uint64_t v)
{
    aura_u32_escribir(p, (uint32_t)v);
    aura_u32_escribir(p + 4, (uint32_t)(v >> 32));
}

static inline uint64_t aura_u64_leer(const uint8_t *p)
{
    return (uint64_t)aura_u32_leer(p) | ((uint64_t)aura_u32_leer(p + 4) << 32);
}

/* ===== Hora ===== */
/* 2026-01-01T00:00:00Z: una hora anterior es un reloj que nunca se ajustó. */
#define AURA_EPOCA_MINIMA 1767225600u

static inline bool aura_hora_valida(uint32_t epoca)
{
    return epoca >= AURA_EPOCA_MINIMA;
}

/* ===== Telemetría ===== */
/* Payload: ingest_id(16) | ts (uint32 LE, 0 = sin hora) | JSON de values */
#define AURA_INGEST_ID_BYTES     16
#define AURA_TELEMETRIA_CABECERA (AURA_INGEST_ID_BYTES + 4)
#define AURA_VALUES_MAX          (AURA_PAYLOAD_MAX - AURA_TELEMETRIA_CABECERA)

static inline void aura_telemetria_armar(aura_trama_t *t, uint16_t seq, const uint8_t id[16],
                                         uint32_t ts, const char *values, size_t largo)
{
    uint8_t p[AURA_PAYLOAD_MAX];
    if (largo > AURA_VALUES_MAX) {
        largo = AURA_VALUES_MAX;
    }
    memcpy(p, id, AURA_INGEST_ID_BYTES);
    aura_u32_escribir(p + AURA_INGEST_ID_BYTES, ts);
    memcpy(p + AURA_TELEMETRIA_CABECERA, values, largo);
    aura_trama_init(t, AURA_TIPO_TELEMETRIA, seq, p, AURA_TELEMETRIA_CABECERA + largo);
}

/* ===== Confirmación ===== */
/* Payload: ingest_id(16) | hora de la raíz (uint32 LE, 0 = sin hora) */
#define AURA_CONFIRMACION_BYTES (AURA_INGEST_ID_BYTES + 4)

static inline void aura_confirmacion_armar(aura_trama_t *t, uint16_t seq, const uint8_t id[16],
                                           uint32_t hora)
{
    uint8_t p[AURA_CONFIRMACION_BYTES];
    memcpy(p, id, AURA_INGEST_ID_BYTES);
    aura_u32_escribir(p + AURA_INGEST_ID_BYTES, hora);
    aura_trama_init(t, AURA_TIPO_CONFIRMACION, seq, p, sizeof(p));
}

/* ===== Hora ===== */
static inline void aura_hora_armar(aura_trama_t *t, uint16_t seq, uint64_t ms_utc)
{
    uint8_t p[8];
    aura_u64_escribir(p, ms_utc);
    aura_trama_init(t, AURA_TIPO_HORA, seq, p, ms_utc ? sizeof(p) : 0);
}

/* ===== LOTE ===== */
#define AURA_LOTE_CABECERA      3
#define AURA_LOTE_ITEM_CABECERA 7       /* MAC(6) + largo(1) */
#define AURA_LOTE_MAX           1400    /* debajo de MESH_MPS (1472) */

typedef struct {
    uint8_t buf[AURA_LOTE_MAX];
    size_t  largo;
    uint8_t cantidad;
} aura_lote_t;

static inline void aura_lote_vaciar(aura_lote_t *l)
{
    l->buf[0] = AURA_PROTO_VERSION;
    l->buf[1] = AURA_TIPO_LOTE;
    l->buf[2] = 0;
    l->largo = AURA_LOTE_CABECERA;
    l->cantidad = 0;
}

/* false si no entra (hay que mandar el lote y empezar otro) */
static inline bool aura_lote_agregar(aura_lote_t *l, const uint8_t mac[6], const uint8_t *trama, size_t largo)
{
    if (largo > AURA_TRAMA_MAX || l->cantidad == 255 ||
        l->largo + AURA_LOTE_ITEM_CABECERA + largo > AURA_LOTE_MAX) {
        return false;
    }
    memcpy(l->buf + l->largo, mac, 6);
    l->buf[l->largo + 6] = (uint8_t)largo;
    memcpy(l->buf + l->largo + AURA_LOTE_ITEM_CABECERA, trama, largo);
    l->largo += AURA_LOTE_ITEM_CABECERA + largo;
    l->buf[2] = ++l->cantidad;
    return true;
}

static inline bool aura_es_lote(const uint8_t *d, size_t len)
{
    return len >= AURA_LOTE_CABECERA && d[0] == AURA_PROTO_VERSION && d[1] == AURA_TIPO_LOTE;
}

/*
 * Recorre un LOTE: en cada llamada devuelve el siguiente ítem (MAC y trama) y avanza *pos.
 * Empezar con *pos = 0. false = no hay más o el lote está mal armado (se corta ahí).
 */
static inline bool aura_lote_siguiente(const uint8_t *d, size_t len, size_t *pos,
                                       const uint8_t **mac, const uint8_t **trama, size_t *largo)
{
    if (*pos == 0) {
        *pos = AURA_LOTE_CABECERA;
    }
    if (*pos + AURA_LOTE_ITEM_CABECERA > len) {
        return false;
    }
    size_t n = d[*pos + 6];
    if (*pos + AURA_LOTE_ITEM_CABECERA + n > len) {
        return false;
    }
    *mac = d + *pos;
    *trama = d + *pos + AURA_LOTE_ITEM_CABECERA;
    *largo = n;
    *pos += AURA_LOTE_ITEM_CABECERA + n;
    return true;
}
