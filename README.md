# Centralizador Proyecto Aura

Firmware para el nodo centralizador con pantalla táctil del Proyecto AURA. Desarrollado en **ESP-IDF v6.1** nativo para microcontroladores **ESP32-S3** (referencia de hardware: Waveshare ESP32-S3-Touch-LCD-7).

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
