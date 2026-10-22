/*
 * Utilidades comunes de la mesh de AURA que no dependen de la placa: ingest_id, hw_id,
 * tópicos, hora en ISO 8601 y el anuncio del aula en el beacon.
 * Portadas de comun/ingest_id.h e infraestructura/nodo_raiz/raiz_logica.h (versión Arduino).
 */
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "aura_trama.h"

/* ===== Anuncio del aula en el beacon (vendor IE) ===== */
/* OUI administrado localmente + tipo 1 = "concentrador". Payload: MAC de la malla(6) + aula */
#define AURA_OUI_0              0x02
#define AURA_OUI_1              0xA5
#define AURA_OUI_2              0x52
#define AURA_IE_CONCENTRADOR    0x01

/* ===== Aula ===== */
/* Nombre corto en minúsculas: a-z, 0-9, "-" y "_", de 1 a 15 caracteres. */
#define AURA_AULA_MAX           16

static inline bool aura_aula_valida(const char *a)
{
    if (a == NULL) {
        return false;
    }
    size_t n = strlen(a);
    if (n == 0 || n >= AURA_AULA_MAX) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        char c = a[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-' || c == '_')) {
            return false;
        }
    }
    return true;
}

/* ===== ingest_id: UUID v4 que genera la hoja al tomar la muestra (contrato §5) ===== */
typedef uint32_t (*aura_azar_t)(void);

static inline void aura_ingest_id_nuevo(uint8_t id[AURA_INGEST_ID_BYTES], aura_azar_t azar)
{
    for (int i = 0; i < AURA_INGEST_ID_BYTES; i += 4) {
        uint32_t r = azar();
        id[i] = (uint8_t)(r >> 24);
        id[i + 1] = (uint8_t)(r >> 16);
        id[i + 2] = (uint8_t)(r >> 8);
        id[i + 3] = (uint8_t)r;
    }
    id[6] = (uint8_t)((id[6] & 0x0F) | 0x40);  /* versión 4 */
    id[8] = (uint8_t)((id[8] & 0x3F) | 0x80);  /* variante RFC 9562 */
}

/* salida: 37 bytes */
static inline void aura_ingest_id_texto(const uint8_t b[AURA_INGEST_ID_BYTES], char salida[37])
{
    snprintf(salida, 37,
             "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7],
             b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);
}

static inline int aura_hex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

/* Solo el formato con guiones, que es el que arma la hoja y devuelve AURA */
static inline bool aura_ingest_id_de_texto(const char *s, uint8_t id[AURA_INGEST_ID_BYTES])
{
    if (s == NULL || strlen(s) != 36) {
        return false;
    }
    int b = 0;
    for (int i = 0; i < 36;) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (s[i] != '-') {
                return false;
            }
            i++;
            continue;
        }
        int hi = aura_hex(s[i]), lo = aura_hex(s[i + 1]);
        if (hi < 0 || lo < 0) {
            return false;
        }
        id[b++] = (uint8_t)(hi << 4 | lo);
        i += 2;
    }
    return b == AURA_INGEST_ID_BYTES;
}

/* ===== hw_id y tópicos (contrato §2) ===== */
#define AURA_HW_ID_BYTES        17      /* "mac-" + 12 + terminador */
#define AURA_TOPICO_MAX         64

static inline void aura_hw_id_de_mac(const uint8_t mac[6], char salida[AURA_HW_ID_BYTES])
{
    snprintf(salida, AURA_HW_ID_BYTES, "mac-%02x%02x%02x%02x%02x%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static inline bool aura_topico(char *salida, size_t cap, const uint8_t mac[6], const char *sufijo)
{
    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(mac, hw);
    int n = snprintf(salida, cap, "hw/%s/%s", hw, sufijo);
    return n > 0 && (size_t)n < cap;
}

/*
 * Lo único que consume la raíz: hw/mac-<12 hex minúsculas>/ack y .../command.
 * Cualquier otra cosa es de otro adaptador o está mal armada. tipo: "ack" o "command".
 */
static inline bool aura_parsear_topico(const char *t, size_t len, uint8_t mac[6], char tipo[8])
{
    if (len < 7 + 12 + 1 || strncmp(t, "hw/mac-", 7) != 0) {
        return false;
    }
    const char *p = t + 7;
    for (int i = 0; i < 12; i++) {
        char c = p[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    if (p[12] != '/') {
        return false;
    }
    size_t resto = len - (7 + 13);
    const char *r = p + 13;
    if (resto == 3 && strncmp(r, "ack", 3) == 0) {
        strcpy(tipo, "ack");
    } else if (resto == 7 && strncmp(r, "command", 7) == 0) {
        strcpy(tipo, "command");
    } else {
        return false;
    }
    for (int i = 0; i < 6; i++) {
        mac[i] = (uint8_t)(aura_hex(p[2 * i]) << 4 | aura_hex(p[2 * i + 1]));
    }
    return true;
}

/* Los cinco resultados del ack confirman; cualquier otro no (ante la duda, la hoja reintenta) */
static inline bool aura_ack_confirma(const char *r)
{
    return r != NULL && (strcmp(r, "persistido") == 0 || strcmp(r, "duplicado") == 0 ||
                         strcmp(r, "cuarentena") == 0 || strcmp(r, "descartado") == 0 ||
                         strcmp(r, "rechazado") == 0);
}

/* El backend solo reconoce hw/<hw_id>/alerts/[a-z_]{1,24} */
static inline bool aura_alerta_tipo_valido(const char *t)
{
    if (t == NULL) {
        return false;
    }
    size_t n = strlen(t);
    if (n == 0 || n > 24) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        if (!((t[i] >= 'a' && t[i] <= 'z') || t[i] == '_')) {
            return false;
        }
    }
    return true;
}

/* ===== Offline inferido (contrato §3.2): 3 x intervalo sin tramas ===== */
static inline bool aura_debe_marcar_offline(uint32_t ahora_ms, uint32_t ultimo_ms,
                                            uint32_t intervalo_s, bool ya_offline)
{
    if (ya_offline || intervalo_s == 0) {
        return false;
    }
    return (uint64_t)(uint32_t)(ahora_ms - ultimo_ms) > 3ull * intervalo_s * 1000ull;
}

/* ===== Época -> "2026-10-05T14:03:00Z" (21 bytes). false si la hora no es válida ===== */
#define AURA_ISO_BYTES 21

static inline bool aura_epoca_a_iso(uint32_t epoca, char salida[AURA_ISO_BYTES])
{
    if (!aura_hora_valida(epoca)) {
        return false;
    }
    uint32_t dias = epoca / 86400u, seg = epoca % 86400u;
    int64_t z = (int64_t)dias + 719468;                /* algoritmo de Howard Hinnant */
    int64_t era = z / 146097;
    uint32_t doe = (uint32_t)(z - era * 146097);
    uint32_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    uint32_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    uint32_t mp = (5 * doy + 2) / 153;
    uint32_t d = doy - (153 * mp + 2) / 5 + 1;
    uint32_t m = mp < 10 ? mp + 3 : mp - 9;
    int64_t y = (int64_t)yoe + era * 400 + (m <= 2 ? 1 : 0);
    char tmp[48];
    snprintf(tmp, sizeof(tmp), "%04d-%02u-%02uT%02u:%02u:%02uZ", (int)y, (unsigned)m, (unsigned)d,
             (unsigned)(seg / 3600), (unsigned)(seg / 60 % 60), (unsigned)(seg % 60));
    memcpy(salida, tmp, AURA_ISO_BYTES - 1);
    salida[AURA_ISO_BYTES - 1] = '\0';
    return true;
}

/* ===== Reintento de una muestra sin confirmar: 15 s, 30 s, 1 min... hasta 5 min ===== */
static inline uint32_t aura_espera_confirmacion_ms(uint32_t intentos)
{
    if (intentos >= 5) {
        return 300000u;
    }
    uint32_t ms = 15000u << intentos;
    return ms > 300000u ? 300000u : ms;
}

/* Le agrega azar a una espera (entre 50 % y 150 %): después de un corte, cada nodo reintenta
   en un momento distinto y no se amontonan todos sobre el concentrador y la raíz. */
static inline uint32_t aura_con_azar(uint32_t ms, uint32_t azar)
{
    return ms / 2 + (uint32_t)(((uint64_t)ms * (azar % 1001)) / 1000);
}
