# GUI — Proyecto EEZ Studio (AURA Centralizador)

Este directorio contiene la definición visual de la interfaz gráfica del **Centralizador AURA** diseñada para **EEZ Studio** sobre **LVGL v9** en orientación vertical (**480 × 800 px**, RGB565).

- **Archivo fuente de verdad:** `GUI/aura.eez-project`
- **Directorio de exportación C/H:** `../main/ui/` (configurado en `settings.build.destinationFolder` como `..\main\ui`).

> **Importante:** Nunca edites manualmente los archivos generados en `main/ui/` (`screens.c`, `screens.h`, `styles.c`, `images.c`, `ui.c`, `vars.h`, `actions.h`), ya que EEZ Studio los sobrescribe en cada exportación.

---

## Arquitectura del Proyecto

### 1. Paleta y Temas (`Default` Claro / `Dark` Oscuro)
El proyecto define 21 tokens semánticos de color con soporte completo para dos temas conmutables:
- **`Default` (Modo Claro — predeterminado):** Fondo `#F4F6F9`, tarjetas `#FFFFFF`, bordes `#E2E8F0`, texto `#1E293B`.
- **`Dark` (Modo Oscuro):** Fondo `#0F172A`, tarjetas `#1E293B`, bordes `#334155`, texto `#F8FAFC`.
- **Colores Institucionales AURA:**
  - `AuraBlue`: `#004069`
  - `AuraOrange`: `#FE9304`
  - `AuraTeal`: `#00B2AD`
  - `AuraGray`: `#494949`

### 2. UserWidgets Reutilizables (`userWidgets`)
- **`HeaderBar` (480 × 62 px):** Logo oficial con fondo transparente (`logo_header_48`), título `AURA CENTRALIZADOR`, subtítulo de aula, botón de alternancia de tema (`ToggleTheme`) y badge de estado de red (`Mesh OK`).
- **`BottomNav` (480 × 60 px):** Barra de navegación inferior fija con 4 pestañas táctiles (`NavDashboard`, `NavDevices`, `NavConfig`, `NavAbout`).

### 3. Pantallas (`userPages`)
1. **`dashboard` (Dashboard Híbrido):**
   - Tarjetas KPI con mediciones reales del nodo activo sin promediar (`TEMPERATURA (E1-AZ)`, `HUMEDAD (E1-AZ)`, `CALIDAD DE AIRE CO2 (E1-AZ)` con barra de progreso y chip `NORMAL`).
   - Filas de control rápido de actuadores (`Ventilacion de Aula`, `Luces Principales`, `LED Indicador de Alerta`).
   - Tarjeta resumen de estado de nodos en el aula y enlace con Gateway Root.
2. **`devices` (Dispositivos Conectados):**
   - Chips de filtrado (`Todos`, `Sensores`, `Actuadores`) y tarjetas por nodo con estado (`CONECTADO` / `AUSENTE`), lecturas crudas, estado de actuador y dirección MAC.
3. **`config` (Ajustes del Centralizador):**
   - Selector de tema Claro/Oscuro, slider de brillo por software (velo de atenuación), aula asignada, canal ESP-WIFI-MESH, estado del Gateway Root, switch de Modo Isla Autónomo y botón de guardado.
4. **`about` (Acerca de):**
   - Tarjeta institucional con logo AURA (`logo_about_240`), versión de firmware, ficha técnica del sistema (ESP-WIFI-MESH Trama v3, Waveshare 7" Touch LCD ST7262 + GT911, Portrait 480×800) y créditos del equipo.

---

## Flujo de Trabajo

1. **Abrir en EEZ Studio:**
   ```bash
   ~/.local/bin/EEZ-Studio-0.29.0.AppImage GUI/aura.eez-project
   ```
2. **Validar en el Canvas y alternar temas:**
   - Revisa las 4 páginas (`dashboard`, `devices`, `config`, `about`) y los 2 UserWidgets (`HeaderBar`, `BottomNav`).
   - En el panel **Themes**, alterna entre `Default` y `Dark` para inspeccionar el contraste en ambos modos.
3. **Exportar código C (`Build` / `F7` o `Ctrl+B`):**
   - Presiona `F7` o el botón **Build** en la barra superior de EEZ Studio.
   - Los archivos C/H se generarán automáticamente en `../main/ui/`.
4. **Verificación automática (Compuertas del Skill `eezstudio`):**
   Desde la raíz del repositorio:
   ```bash
   python3 .agents/skills/eezstudio/verify_project.py GUI/aura.eez-project
   python3 .agents/skills/eezstudio/render_pages.py GUI/aura.eez-project
   python3 .agents/skills/eezstudio/verify_no_canvas_divergence.py .
   ```
