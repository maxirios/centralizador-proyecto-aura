# Centralizador Proyecto Aura

## Build
1. Editar ROUTER_SSID y ROUTER_PASS en main/main.c (hotspot de 2.4 GHz).
2. Cargar ESP-IDF y, desde la raíz del repo:
   - S3 (root):  idf.py -B build_s3 -D SDKCONFIG=sdkconfig_s3 -D IDF_TARGET=esp32s3 build
   - ESP32:      idf.py -B build_esp -D SDKCONFIG=sdkconfig_esp -D IDF_TARGET=esp32 build
3. Encender primero la S3 y después el otro nodo.
