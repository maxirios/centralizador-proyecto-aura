# Centralizador Proyecto Aura

Firmware para el nodo centralizador con pantalla táctil del Proyecto AURA. Desarrollado en **ESP-IDF v6.1** nativo para microcontroladores **ESP32-S3** (referencia de hardware: Waveshare ESP32-S3-Touch-LCD-7).

---

## Arquitectura y Topología de Red

El sistema de comunicaciones de AURA opera como una red en malla jerárquica (ESP-WIFI-MESH) estructurada en tres niveles físicos más el backend central:

```
                  [ Broker MQTT / Servidor AURA ]
                                 ▲
                                 │ Wi-Fi 2.4 GHz (TCP/IP)
                                 │ Único nodo conectado al Router
                       ┌─────────┴──────────┐
                       │  Mesh3_Gateway     │  Raíz (Root) · ESP32-S3
                       └─────────┬──────────┘
                                 │
                                 │ Malla ESP-WIFI-MESH (Trama binaria AURA v3)
                                 │
                       ┌─────────┴──────────┐
                       │   CENTRALIZADOR    │  Concentrador de Aula (Este repositorio)
                       │ (ESP32-S3 + Touch) │  Pantalla táctil vertical · Waveshare 7"
                       └─────────┬──────────┘
                                 │
                                 │ Malla ESP-WIFI-MESH (Filtrado por Aula en Vendor IE)
                                 │
                       ┌─────────┴──────────┐
                       │    Nodos Hoja      │  Sensores ambientales (Temp/Hum/CO2)
                       │ (ESP32 / ESP32-C3) │  y Actuadores (Relés de iluminación/clima)
                       └────────────────────┘
```

### Rol del Centralizador en la Malla
- **Nodo Intermediario (Capa 2):** Se asocia hacia arriba con el Gateway (raíz) y hacia abajo acepta conexiones de los nodos hoja asignados a su aula.
- **Sin conexión directa a Internet:** El Centralizador **no** se conecta al router Wi-Fi; todo el tráfico hacia la nube se deriva a través del Gateway.
- **Filtrado por Aula:** Anuncia el identificador de su aula en beacons Wi-Fi (Vendor IE) para que las hojas del aula se enlacen automáticamente sin configurar MACs manuales.
- **Agregación en Lote:** Acumula la telemetría recibida de las hojas y la reenvía consolidada (`AURA_TIPO_LOTE`) hacia el Gateway para minimizar colisiones en el aire.
- **Control Táctil Directo:** Despacha comandos descendentes (`AURA_TIPO_COMANDO`) a las hojas cuando el usuario opera la pantalla táctil, actualizando la interfaz tras la confirmación de estado del actuador.
- **Operación Offline (Modo Isla):** Si se pierde el enlace con el Gateway, el centralizador asume temporalmente la coordinación del aula para que la pantalla y los actuadores continúen respondiendo localmente.

---

### Prerrequisitos

Tener instalado el framework oficial de Espressif **ESP-IDF v6.1**. Si aún no lo tienes instalado, consulta la documentación oficial:
* [Guía oficial de instalación de ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/v6.1/esp32/get-started/linux-macos-setup.html)

---

### 1. Inicializar el Entorno de ESP-IDF

En cada nueva terminal de trabajo, antes de ejecutar cualquier comando de `idf.py`, carga las variables de entorno de ESP-IDF:

```bash
. $HOME/.espressif/v6.1/esp-idf/export.sh
```

> *(o alternativamente: `source $HOME/esp/esp-idf/export.sh` según tu ruta de instalación)*

---

### 2. Seleccionar el Microcontrolador Destino (Target)

Configura el microcontrolador objetivo del proyecto (**ESP32-S3**):

```bash
idf.py set-target esp32s3
```

---

### 3. Configuración de Parámetros de Malla

El centralizador se conecta a la malla mediante credenciales compartidas con el Gateway y las Hojas:

- **ID de la Malla (MESH_ID):** 6 bytes hexadecimales que identifican la red local.
- **Contraseña del AP Mesh (MESH_AP_PASS):** Clave WPA2 utilizada para la comunicación inter-nodo.
- **Aula asignada:** Identificador de aula para filtrar hojas (ej. `aula1`).

Estos parámetros se configuran de forma segura mediante `main/config_local.h` o interactivamente:

```bash
idf.py menuconfig
```

Navega hasta **`AURA Mesh Intermediary Configuration --->`** para ajustar la clave de malla y el aula por defecto.

---

### 4. Compilación

Compila el firmware del proyecto:

```bash
idf.py build
```

---

### 5. Flasheo y Monitoreo Serie

Conecta el microcontrolador a tu computadora:

#### Flashear el firmware:

```bash
idf.py -p /dev/ttyACM0 flash
```

#### Abrir el monitor serie:

```bash
idf.py -p /dev/ttyACM0 monitor
```

#### Flashear y monitorear en un solo paso:

```bash
idf.py -p /dev/ttyACM0 flash monitor
```

> **Tip**: Para salir del monitor serie, presiona `Ctrl + ]`.
