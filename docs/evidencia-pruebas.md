# Guía y Plantilla de Evidencia de Pruebas en Terminal

Esta guía aplica para toda Pull Request que introduzca o modifique código de microcontroladores (firmware, drivers de hardware, protocolos de red o visualización).

---

## 1. Reglas Generales

1. **Evitar volcados masivos:** No pegar salidas continuas de cientos de líneas de consola.
2. **Dividir por microcontrolador o etapa:** Si se monitorean varias placas (ej. Centralizador ESP32-S3 vs Hoja ESP32-C3) o etapas distintas (ej. Conexión Wi-Fi/Malla vs Despacho de Comandos), separarlas en bloques independientes.
3. **Contexto acotado:** Mostrar la línea clave acompañada de 2 a 3 líneas anteriores y posteriores para dar contexto sin saturar.
4. **Evidencia visual física:** Si el cambio altera el comportamiento visual (parpadeo de LEDs, estados de pantalla o LVGL), el agente debe proponer incluir la sección de evidencia visual en la PR con un marcador de posición para arrastrar la foto o video directamente desde la interfaz web de GitHub.

---

## 2. Formato: Comprobación Exitosa (Comportamiento Esperado)

Copiar y completar un bloque por cada dispositivo o etapa funcional testeada:

### [Dispositivo / Etapa, ej: ESP32-S3 Centralizador - Conexión a la Malla]
En la salida del terminal del ESP32-S3 el hito comprobado fue: `I (4510) MESH_NET: Conectado al padre 7c:2c:67:7c:8d:6c (capa 2, canal 1)`

Salida de la terminal:
```bash
# Líneas anteriores de contexto
I (1040) MESH_NET: Escaneando canales de malla...
I (1045) MESH_NET: Beacon IE activo anunciando aula 'aula1'
# Línea clave de interés
I (4510) MESH_NET: Conectado al padre 7c:2c:67:7c:8d:6c (capa 2, canal 1)
# Líneas posteriores de contexto
I (4520) MESH_NET: Sincronizando hora con Gateway...
I (4530) CENTRALIZADOR_APP: Operando normalmente en aula 'aula1'
```

---

## 3. Formato: Diagnóstico de Error / Bugfix (Fallo Resuelto)

Utilizar cuando la PR solucione un error o para documentar un fallo previo a la corrección:

### [Dispositivo / Etapa con Error, ej: ESP32-S3 Centralizador - Timeout de Envío]
En la salida del terminal del ESP32-S3 el error detectado fue: `E (12340) MESH_NET: Error envio hacia raiz: ESP_ERR_TIMEOUT`

Salida de la terminal:
```bash
# Líneas anteriores de contexto
I (12300) MESH_NET: Intentando enviar lote de 3 tramas...
W (12320) MESH_NET: Control de flujo ocupado
# Línea de error detectada
E (12340) MESH_NET: Error envio hacia raiz: ESP_ERR_TIMEOUT
# Líneas posteriores de recuperación
W (12350) MESH_NET: Reintentando en 1000 ms...
I (13350) MESH_NET: Lote entregado exitosamente
```

---

## 4. Formato: Evidencia Visual Física (LEDs, Pantalla / LVGL)

Utilizar cuando la PR modifique el comportamiento visual del hardware (ej. secuencias de LEDs o interfaces en pantalla). El agente debe consultar al usuario si desea incluir este bloque para adjuntar una foto o GIF desde GitHub:

### Evidencia Visual
<!-- Arrastrar o pegar aquí la foto o video desde la interfaz web de GitHub -->
