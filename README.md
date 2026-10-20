# Centralizador Proyecto Aura

Firmware para nodo de red ESP-MESH y visualización. Este repositorio está preparado para compilarse y flashearse sobre microcontroladores de la familia ESP32 (utilizando **ESP32-S3** como referencia estándar de este proyecto).

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

> *(o alternativamente: `source $HOME/.espressif/v6.1/esp-idf/export.sh`)*

---

### 2. Seleccionar el Microcontrolador Destino (Target)

Configura el microcontrolador objetivo del proyecto (por ejemplo, **ESP32-S3**):

```bash
idf.py set-target esp32s3
```

---

### 3. Configuración de Wi-Fi y Malla (`menuconfig`)

Las credenciales de red y los parámetros de la malla se configuran de forma interactiva directamente desde la interfaz gráfica de terminal:

```bash
idf.py menuconfig
```

1. Navega hasta el menú **`Mesh Wi-Fi Configuration --->`** (o **`Wi-Fi Configuration --->`**).
2. Ingresa el **Router SSID** y el **Router Password**.
3. Presiona `S` para guardar los cambios y luego `Q` para salir.

Los datos se guardarán de forma local y segura en tu archivo `sdkconfig` sin exponer contraseñas al repositorio de Git.

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

> **Tip para el puerto serie**: Puedes exportar la variable de entorno ejecutando `export ESPPORT="/dev/ttyACM0"` en tu terminal activa para no tener que escribir `-p /dev/ttyACM0` en cada comando de `flash` o `monitor` (`idf.py flash monitor` lo tomará automáticamente). Si tienes un solo microcontrolador conectado, puedes omitir el puerto por completo ya que ESP-IDF lo detectará solo.

#### Abrir el monitor serie:

```bash
idf.py -p /dev/ttyACM0 monitor
```

#### Flashear y monitorear en un solo paso:

```bash
idf.py -p /dev/ttyACM0 flash monitor
```

> **Tip**: Para salir del monitor serie, puedes presionar las combinaciónes de teclas `Ctrl + ]` , `Ctrl + 5` o `Ctrl + t` y seguido `Ctrl + x`.
