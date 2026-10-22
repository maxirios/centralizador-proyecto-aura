#include "aura_protocol.h"

const char *aura_tipo_a_str(uint8_t tipo)
{
    switch (tipo) {
        case AURA_TIPO_TELEMETRIA:   return "TELEMETRIA";
        case AURA_TIPO_COMANDO:      return "COMANDO";
        case AURA_TIPO_ACK:          return "ACK";
        case AURA_TIPO_CONFIRMACION: return "CONFIRMACION";
        case AURA_TIPO_RESULTADO:    return "RESULTADO";
        case AURA_TIPO_REPORTE:      return "REPORTE/ESTADO";
        case AURA_TIPO_ALERTA:       return "ALERTA";
        case AURA_TIPO_PING:         return "PING";
        case AURA_TIPO_HORA:         return "HORA";
        case AURA_TIPO_LOTE:         return "LOTE";
        case AURA_TIPO_EVENTO_OK:    return "EVENTO_OK";
        case AURA_TIPO_REPORTAR:     return "REPORTAR";
        default:                     return "DESCONOCIDO";
    }
}

aura_validacion_t aura_validar_trama_completa(const uint8_t *d, size_t len)
{
    return aura_trama_validar(d, len);
}
