# Directrices del Proyecto - Centralizador Aura (ESP32-S3 + LVGL + ESP-MESH)

Este repositorio contiene el firmware del **Centralizador** del Proyecto Aura: un nodo con pantalla táctil vertical que visualiza telemetría en tiempo real y transfiere datos en formato JSON a través de una red ESP-MESH hacia el Gateway Root.

## Ficha Técnica de Hardware y Entorno
- **SoC:** ESP32-S3 (`CONFIG_IDF_TARGET="esp32s3"`).
- **Memoria:** Flash 8 MB (QIO 80 MHz), PSRAM Octal 8 MB (`CONFIG_SPIRAM_MODE_OCT=y`).
- **Pantalla:** Waveshare ESP32-S3-Touch-LCD-7 (RGB 800×480 nativo, operando en **modo vertical / portrait a 480×800** mediante rotación de LVGL).
- **Táctil:** Goodix GT911 (I2C) con inversión/rotación de ejes mapeada a portrait.
- **Frameworks:** ESP-IDF v5.x + LVGL v9.x (`esp_lvgl_port`).
- **Rol de Red:** Nodo Concentrador / Intermediario ESP-WIFI-MESH (capa 2 del aula). Se conecta hacia arriba al Gateway Root (único nodo con salida a Internet vía Wi-Fi) y hacia abajo coordina a los Nodos Hoja (sensores ambientales y actuadores/relés). No se asocia a routers Wi-Fi directamente.

## Comandos Estándar de Trabajo
| Tarea | Comando |
| :--- | :--- |
| Configurar target (solo primera vez) | `idf.py set-target esp32s3` |
| Compilar proyecto | `idf.py build` |
| Reconfigurar CMake/Kconfig | `idf.py reconfigure` |
| Flashear y abrir monitor serie | `idf.py -p /dev/ttyACM0 flash monitor` |
| Limpieza estándar | `idf.py clean` |

## Reglas Críticas de Arquitectura y Seguridad
1. **Configuración inmutable a mano:** Nunca edites `sdkconfig` directamente. Todo cambio persistente va en `sdkconfig.defaults`.
2. **Secretos fuera de Git:** Parámetros sensibles de red Wi-Fi van en `sdkconfig.defaults.local` (en `.gitignore`).
3. **Memoria de renderizado:** Alojar los framebuffers y buffers de renderizado de LVGL v9 en **PSRAM** (`MALLOC_CAP_SPIRAM`) para no agotar la RAM interna.
4. **Concurrencia FreeRTOS + LVGL:** La rutina `lv_timer_handler()` corre en una tarea FreeRTOS dedicada; toda llamada que interactúe con la UI debe usar los bloqueos de `esp_lvgl_port_lock()` / `esp_lvgl_port_unlock()`.
5. **Modularidad en `components/`:** El código de drivers, lógica de red y pantallas debe desacoplarse en componentes locales (`components/bsp_display`, `components/mesh_net`, `components/ui`).
6. **Pull Requests y Evidencia:** Toda PR con cambios en microcontroladores debe seguir la estructura y formato de pruebas de terminal definido en `docs/evidencia-pruebas.md`.

## Enrutador de Skills Especializadas (Context Pointers)
Antes de implementar código o resolver problemas, consulta el archivo correspondiente:

| Tarea / Contexto | Skill a Consultar | Ruta del Manual |
| :--- | :--- | :--- |
| Configuración de target, build, flash, logs o panics | **ESP-IDF Core** | `.agents/skills/esp-idf/SKILL.md` |
| Creación de nuevos módulos y dependencias en `components/` | **ESP-IDF Components** | `.agents/skills/esp-idf-components/SKILL.md` |
| Patrones FreeRTOS, buffers PSRAM y plantillas LVGL v9 | **ESP32 Firmware Engineer** | `.agents/skills/esp32-firmware-engineer/SKILL.md` |
| Gestión de ramas, Conventional Commits y Pull Requests | **GitHub Workflow** | `.agents/skills/github-workflow/SKILL.md` |
| Plantilla y evidencia de pruebas en Pull Requests | **Plantilla PR** | `.github/PULL_REQUEST_TEMPLATE.md` |
| Mantenimiento y optimización de este archivo | **Agents.md Maintainer** | `~/.agents/skills/agents-md/SKILL.md` |
