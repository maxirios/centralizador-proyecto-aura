#include "ui_dashboard.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_idf_version.h"
#include "lvgl.h"
#include "ui_port.h"
#include "ui_bridge.h"
#include "aura_trama.h"
#include "aura_util.h"
#include "cJSON.h"

static const char *TAG = "ui_dashboard";

// Paleta oscura del boceto
#define COL_BG      lv_color_hex(0x0F172A)
#define COL_CARD    lv_color_hex(0x1E293B)
#define COL_BORDER  lv_color_hex(0x334155)
#define COL_TEXT    lv_color_hex(0xF8FAFC)
#define COL_MUTED   lv_color_hex(0x94A3B8)
#define COL_HEADER  lv_color_hex(0x0B1E2D)
#define COL_OK      lv_color_hex(0x00B2AD)
#define COL_WARN    lv_color_hex(0xF59E0B)
#define COL_OFF     lv_color_hex(0xEF4444)

// La placa solo permite encender/apagar la retroiluminacion (CH422G), no regular el brillo.
// Se atenua por software con un velo negro semitransparente: 0 = sin atenuar, 100 = negro total.
#define OSCURECER_PCT 45

#define ANCHO_PANTALLA  480
#define ALTO_PANTALLA   800
#define ALTO_HEADER     75
#define ALTO_TABS       64

// Fuentes grandes opcionales: si no estan habilitadas en menuconfig se usa la fuente por defecto
#if LV_FONT_MONTSERRAT_24
#define FUENTE_GRANDE (&lv_font_montserrat_24)
#else
#define FUENTE_GRANDE LV_FONT_DEFAULT
#endif
#if LV_FONT_MONTSERRAT_18
#define FUENTE_MEDIA (&lv_font_montserrat_18)
#else
#define FUENTE_MEDIA LV_FONT_DEFAULT
#endif

typedef struct { const char *clave; const char *nombre; const char *unidad; } campo_info_t;
static const campo_info_t CAMPOS[] = {
    { "temp_c",    "Temperatura", "\xC2\xB0" "C" },  // "°C" en UTF-8 (glifo incluido en Montserrat)
    { "hum_pct",   "Humedad",     "%"   },
    { "co2_ppm",   "CO2",         "ppm" },
    { "presencia", "Presencia",   ""    },
    { "led",       "LED",         ""    },
};

typedef enum { CFG_AULA = 0, CFG_CANAL, CFG_MODO, CFG_GATEWAY, CFG_NODOS, CFG_CANT } cfg_fila_t;

// Widgets que se actualizan en cada refresco
static lv_obj_t *s_lbl_gw = NULL;
static lv_obj_t *s_lbl_conectados = NULL;
static lv_obj_t *s_lbl_ausentes = NULL;
static lv_obj_t *s_lbl_aula = NULL;
static lv_obj_t *s_lbl_red = NULL;
static lv_obj_t *s_cont_control = NULL;
static lv_obj_t *s_tab_disp = NULL;
static lv_obj_t *s_lbl_cfg[CFG_CANT];

// MAC de cada fila de control; el boton guarda un puntero a su entrada
static uint8_t s_macs_control[MESH_HOJAS_MAX][6];

// Corre en la tarea del emisor (sys_evt, mesh_hojas): solo marca el modelo como sucio.
// El redibujo se hace en la tarea de LVGL para no consumir stack ajeno.
static volatile bool s_sucio = true;

static const campo_info_t *buscar_campo(const char *clave)
{
    for (size_t i = 0; i < sizeof(CAMPOS) / sizeof(CAMPOS[0]); i++) {
        if (strcmp(CAMPOS[i].clave, clave) == 0) return &CAMPOS[i];
    }
    return NULL;
}

static lv_obj_t *crear_contenedor_plano(lv_obj_t *parent)
{
    lv_obj_t *o = lv_obj_create(parent);
    lv_obj_set_width(o, lv_pct(100));
    lv_obj_set_height(o, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(o, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(o, 0, 0);
    lv_obj_set_style_pad_all(o, 0, 0);
    lv_obj_remove_flag(o, LV_OBJ_FLAG_SCROLLABLE);
    return o;
}

static lv_obj_t *crear_tarjeta(lv_obj_t *parent)
{
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_width(card, lv_pct(100));
    lv_obj_set_height(card, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(card, COL_CARD, 0);
    lv_obj_set_style_border_color(card, COL_BORDER, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_radius(card, 10, 0);
    lv_obj_set_style_pad_all(card, 12, 0);
    lv_obj_set_style_pad_row(card, 8, 0);
    lv_obj_remove_flag(card, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(card, LV_FLEX_FLOW_COLUMN);
    return card;
}

static lv_obj_t *crear_label(lv_obj_t *parent, const char *texto, lv_color_t color)
{
    lv_obj_t *l = lv_label_create(parent);
    lv_label_set_text(l, texto);
    lv_obj_set_style_text_color(l, color, 0);
    return l;
}

static void crear_titulo_tarjeta(lv_obj_t *card, const char *texto)
{
    lv_obj_t *l = crear_label(card, texto, COL_MUTED);
    lv_obj_set_style_text_letter_space(l, 1, 0);
}

static void preparar_tab(lv_obj_t *tab)
{
    lv_obj_set_style_bg_color(tab, COL_BG, 0);
    lv_obj_set_style_bg_opa(tab, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(tab, 12, 0);
    lv_obj_set_style_pad_row(tab, 12, 0);
    lv_obj_set_flex_flow(tab, LV_FLEX_FLOW_COLUMN);
}

static void crear_chip(lv_obj_t *parent, const char *texto, lv_color_t color)
{
    lv_obj_t *chip = lv_obj_create(parent);
    lv_obj_set_size(chip, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(chip, color, 0);
    lv_obj_set_style_bg_opa(chip, LV_OPA_20, 0);
    lv_obj_set_style_border_width(chip, 0, 0);
    lv_obj_set_style_radius(chip, 6, 0);
    lv_obj_set_style_pad_hor(chip, 8, 0);
    lv_obj_set_style_pad_ver(chip, 2, 0);
    lv_obj_remove_flag(chip, LV_OBJ_FLAG_SCROLLABLE);
    crear_label(chip, texto, color);
}

// Fila "clave ........ valor"; devuelve el label del valor
static lv_obj_t *crear_fila_clave_valor(lv_obj_t *parent, const char *clave, const char *valor)
{
    lv_obj_t *fila = crear_contenedor_plano(parent);
    lv_obj_set_flex_flow(fila, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(fila, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    crear_label(fila, clave, COL_MUTED);
    return crear_label(fila, valor, COL_TEXT);
}

// Recuadro de estadistica del resumen: numero grande y leyenda; devuelve el label del numero
static lv_obj_t *crear_estadistica(lv_obj_t *parent, const char *leyenda, lv_color_t color)
{
    lv_obj_t *box = lv_obj_create(parent);
    lv_obj_set_height(box, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(box, 1);
    lv_obj_set_style_bg_color(box, COL_BG, 0);
    lv_obj_set_style_border_width(box, 0, 0);
    lv_obj_set_style_radius(box, 8, 0);
    lv_obj_set_style_pad_all(box, 10, 0);
    lv_obj_set_style_pad_row(box, 4, 0);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(box, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(box, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *num = crear_label(box, "-", color);
    lv_obj_set_style_text_font(num, FUENTE_GRANDE, 0);
    crear_label(box, leyenda, COL_MUTED);
    return num;
}

static void on_click_actuador(lv_event_t *e)
{
    const uint8_t *mac = (const uint8_t *)lv_event_get_user_data(e);
    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(mac, hw);
    esp_err_t err = ui_bridge_conmutar_actuador(mac, "led");
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Orden de conmutar LED enviada a %s", hw);
    } else {
        ESP_LOGW(TAG, "No se pudo enviar la orden a %s (%s)", hw, esp_err_to_name(err));
    }
    lv_obj_t *btn = lv_event_get_target_obj(e);
    lv_obj_t *lbl = lv_obj_get_child(btn, 0);
    if (lbl) {
        lv_label_set_text(lbl, err == ESP_OK ? "..." : "ERROR");
    }
}

static void crear_fila_control(lv_obj_t *parent, const ui_nodo_t *n, uint8_t *mac_slot)
{
    lv_obj_t *fila = crear_contenedor_plano(parent);
    lv_obj_set_flex_flow(fila, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(fila, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *info = crear_contenedor_plano(fila);
    lv_obj_set_width(info, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(info, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(info, 2, 0);
    crear_label(info, n->hw_id, COL_TEXT);
    if (n->conectado) {
        crear_label(info, n->actuador_estado ? "LED encendido" : "LED apagado", COL_MUTED);
    } else {
        crear_label(info, "Nodo ausente", COL_OFF);
    }

    memcpy(mac_slot, n->mac, 6);
    lv_obj_t *btn = lv_button_create(fila);
    lv_obj_set_size(btn, 110, 48);
    lv_obj_set_style_radius(btn, 8, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_set_style_bg_color(btn, n->actuador_estado ? COL_OK : COL_BORDER, 0);
    lv_obj_add_event_cb(btn, on_click_actuador, LV_EVENT_CLICKED, mac_slot);
    if (!n->conectado) {
        lv_obj_add_state(btn, LV_STATE_DISABLED);
    }
    lv_obj_t *lbl = crear_label(btn, n->actuador_estado ? "ON" : "OFF", COL_TEXT);
    lv_obj_set_style_text_font(lbl, FUENTE_MEDIA, 0);
    lv_obj_center(lbl);
}

static void crear_tarjeta_nodo(lv_obj_t *parent, const ui_nodo_t *n)
{
    lv_obj_t *card = crear_tarjeta(parent);

    lv_obj_t *cab = crear_contenedor_plano(card);
    lv_obj_set_flex_flow(cab, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cab, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_t *lbl_id = crear_label(cab, n->hw_id, COL_TEXT);
    lv_obj_set_style_text_font(lbl_id, FUENTE_MEDIA, 0);
    crear_chip(cab, n->conectado ? "CONECTADO" : "AUSENTE", n->conectado ? COL_OK : COL_OFF);

    // Los datos se muestran como llegan: un campo ausente en el JSON no se dibuja
    cJSON *root = n->tiene_telemetria ? cJSON_Parse(n->raw_values) : NULL;
    if (!root) {
        crear_label(card, "Esperando mediciones...", COL_MUTED);
        return;
    }
    cJSON *campo = NULL;
    cJSON_ArrayForEach(campo, root) {
        if (!campo->string) continue;
        const campo_info_t *info = buscar_campo(campo->string);
        const char *nombre = info ? info->nombre : campo->string;
        const char *unidad = info ? info->unidad : "";
        // El printf interno de LVGL no soporta %f: se formatea con snprintf de libc
        char valor[40];
        if (cJSON_IsNumber(campo)) {
            if (strcmp(campo->string, "led") == 0) {
                snprintf(valor, sizeof(valor), "%s", campo->valueint ? "encendido" : "apagado");
            } else if (campo->valuedouble == (double)(long)campo->valuedouble) {
                snprintf(valor, sizeof(valor), "%ld %s", (long)campo->valuedouble, unidad);
            } else {
                snprintf(valor, sizeof(valor), "%.1f %s", campo->valuedouble, unidad);
            }
        } else if (cJSON_IsBool(campo)) {
            if (strcmp(campo->string, "led") == 0) {
                snprintf(valor, sizeof(valor), "%s", cJSON_IsTrue(campo) ? "encendido" : "apagado");
            } else {
                snprintf(valor, sizeof(valor), "%s", cJSON_IsTrue(campo) ? "si" : "no");
            }
        } else if (cJSON_IsString(campo) && campo->valuestring) {
            snprintf(valor, sizeof(valor), "%s", campo->valuestring);
        } else {
            continue;
        }
        crear_fila_clave_valor(card, nombre, valor);
    }
    cJSON_Delete(root);
}

static bool hay_toque_en_curso(void)
{
    for (lv_indev_t *i = lv_indev_get_next(NULL); i != NULL; i = lv_indev_get_next(i)) {
        if (lv_indev_get_state(i) == LV_INDEV_STATE_PRESSED) return true;
    }
    return false;
}

static void on_bridge_notif(ui_evento_tipo_t evento, const void *datos, void *user_data)
{
    s_sucio = true;
}

static void refresco_timer_cb(lv_timer_t *t)
{
    // No se reconstruyen listas mientras el dedo esta apoyado: se perderia el click o el scroll
    if (s_sucio && !hay_toque_en_curso()) {
        s_sucio = false;
        ui_dashboard_actualizar();
    }
}

static void actualizar_estado_red(const ui_estado_aula_t *snap)
{
    const char *modo;
    lv_color_t color;
    if (snap->red.gateway_conectado) {
        modo = "GATEWAY OK";
        color = lv_color_hex(0x22C55E);
    } else if (snap->red.modo_isla) {
        modo = "MODO ISLA";
        color = COL_WARN;
    } else {
        modo = "BUSCANDO GW...";
        color = COL_OFF;
    }

    if (s_lbl_gw) {
        if (snap->red.canal) {
            lv_label_set_text_fmt(s_lbl_gw, "%s | CH %d | %s", modo, snap->red.canal, snap->red.aula);
        } else {
            lv_label_set_text_fmt(s_lbl_gw, "%s | %s", modo, snap->red.aula);
        }
        lv_obj_set_style_text_color(s_lbl_gw, color, 0);
    }
    if (s_lbl_red) {
        lv_label_set_text(s_lbl_red, modo);
        lv_obj_set_style_text_color(s_lbl_red, color, 0);
    }

    if (s_lbl_cfg[CFG_AULA]) {
        lv_label_set_text(s_lbl_cfg[CFG_AULA], snap->red.aula[0] ? snap->red.aula : "-");
    }
    if (s_lbl_cfg[CFG_CANAL]) {
        if (snap->red.canal) {
            lv_label_set_text_fmt(s_lbl_cfg[CFG_CANAL], "%d", snap->red.canal);
        } else {
            lv_label_set_text(s_lbl_cfg[CFG_CANAL], "-");
        }
    }
    if (s_lbl_cfg[CFG_MODO]) {
        lv_label_set_text(s_lbl_cfg[CFG_MODO], snap->red.modo_isla ? "Isla (raiz propia)" : "Intermedio (hijo del gateway)");
    }
    if (s_lbl_cfg[CFG_GATEWAY]) {
        lv_label_set_text(s_lbl_cfg[CFG_GATEWAY], snap->red.gateway_conectado ? "Conectado" : "Sin conexion");
        lv_obj_set_style_text_color(s_lbl_cfg[CFG_GATEWAY], snap->red.gateway_conectado ? COL_OK : COL_OFF, 0);
    }
    if (s_lbl_cfg[CFG_NODOS]) {
        lv_label_set_text_fmt(s_lbl_cfg[CFG_NODOS], "%d / %d", snap->cant_nodos, MESH_HOJAS_MAX);
    }
}

static void actualizar_dashboard(const ui_estado_aula_t *snap)
{
    int conectados = 0;
    for (int i = 0; i < snap->cant_nodos; i++) {
        if (snap->nodos[i].conectado) conectados++;
    }
    if (s_lbl_conectados) lv_label_set_text_fmt(s_lbl_conectados, "%d", conectados);
    if (s_lbl_ausentes) lv_label_set_text_fmt(s_lbl_ausentes, "%d", snap->cant_nodos - conectados);
    if (s_lbl_aula) lv_label_set_text(s_lbl_aula, snap->red.aula[0] ? snap->red.aula : "-");

    if (!s_cont_control) return;
    lv_obj_clean(s_cont_control);
    crear_titulo_tarjeta(s_cont_control, "CONTROL DE ACTUADORES");
    int filas = 0;
    for (int i = 0; i < snap->cant_nodos; i++) {
        if (!snap->nodos[i].tiene_actuador) continue;
        crear_fila_control(s_cont_control, &snap->nodos[i], s_macs_control[filas]);
        filas++;
    }
    if (filas == 0) {
        crear_label(s_cont_control, "Ningun nodo con actuador en el aula", COL_MUTED);
    }
}

static void actualizar_dispositivos(const ui_estado_aula_t *snap)
{
    if (!s_tab_disp) return;
    // lv_obj_clean vuelve el scroll a cero: se guarda y se restaura despues de reconstruir
    int32_t scroll_y = lv_obj_get_scroll_y(s_tab_disp);
    lv_obj_clean(s_tab_disp);

    if (snap->cant_nodos == 0) {
        lv_obj_t *l = crear_label(s_tab_disp, "Esperando hojas en el aula...\n(Las tarjetas apareceran automaticamente)", COL_MUTED);
        lv_obj_set_width(l, lv_pct(100));
        lv_obj_set_style_text_align(l, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_top(l, 30, 0);
        return;
    }
    for (int i = 0; i < snap->cant_nodos; i++) {
        crear_tarjeta_nodo(s_tab_disp, &snap->nodos[i]);
    }
    if (scroll_y > 0) {
        lv_obj_update_layout(s_tab_disp);
        lv_obj_scroll_to_y(s_tab_disp, scroll_y, LV_ANIM_OFF);
    }
}

void ui_dashboard_actualizar(void)
{
    // Static: el snapshot ocupa varios KB y solo se usa desde la tarea de LVGL
    static ui_estado_aula_t snap;
    if (ui_bridge_get_snapshot(&snap) != ESP_OK) {
        s_sucio = true;
        return;
    }
    actualizar_estado_red(&snap);
    actualizar_dashboard(&snap);
    actualizar_dispositivos(&snap);
}

static void crear_tab_dashboard(lv_obj_t *tab)
{
    preparar_tab(tab);

    lv_obj_t *resumen = crear_tarjeta(tab);
    crear_titulo_tarjeta(resumen, "RESUMEN DEL AULA");
    lv_obj_t *stats = crear_contenedor_plano(resumen);
    lv_obj_set_flex_flow(stats, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(stats, 8, 0);
    s_lbl_conectados = crear_estadistica(stats, "Conectados", COL_OK);
    s_lbl_ausentes = crear_estadistica(stats, "Ausentes", COL_OFF);
    s_lbl_aula = crear_estadistica(stats, "Aula", COL_TEXT);
    // El nombre del aula puede tener hasta 15 caracteres: fuente media y recorte con puntos
    lv_obj_set_style_text_font(s_lbl_aula, FUENTE_MEDIA, 0);
    lv_obj_set_width(s_lbl_aula, lv_pct(100));
    lv_label_set_long_mode(s_lbl_aula, LV_LABEL_LONG_DOT);
    lv_obj_set_style_text_align(s_lbl_aula, LV_TEXT_ALIGN_CENTER, 0);
    s_lbl_red = crear_fila_clave_valor(resumen, "Estado de red", "-");

    s_cont_control = crear_tarjeta(tab);
}

static void crear_tab_config(lv_obj_t *tab)
{
    preparar_tab(tab);

    lv_obj_t *card = crear_tarjeta(tab);
    crear_titulo_tarjeta(card, "RED Y AULA (SOLO LECTURA)");
    s_lbl_cfg[CFG_AULA] = crear_fila_clave_valor(card, "Aula", "-");
    s_lbl_cfg[CFG_CANAL] = crear_fila_clave_valor(card, "Canal Wi-Fi", "-");
    s_lbl_cfg[CFG_MODO] = crear_fila_clave_valor(card, "Modo", "-");
    s_lbl_cfg[CFG_GATEWAY] = crear_fila_clave_valor(card, "Gateway", "-");
    s_lbl_cfg[CFG_NODOS] = crear_fila_clave_valor(card, "Nodos registrados", "-");
}

static void crear_tab_acerca(lv_obj_t *tab)
{
    preparar_tab(tab);

    lv_obj_t *card = crear_tarjeta(tab);
    lv_obj_t *titulo = crear_label(card, "AURA", COL_OK);
    lv_obj_set_style_text_font(titulo, FUENTE_GRANDE, 0);
    crear_label(card, "Centralizador de aula (nodo intermedio ESP-WIFI-MESH)", COL_MUTED);

    uint8_t mac[6] = {0};
    char hw[AURA_HW_ID_BYTES] = "-";
    if (esp_read_mac(mac, ESP_MAC_WIFI_STA) == ESP_OK) {
        aura_hw_id_de_mac(mac, hw);
    }
    char proto[8];
    snprintf(proto, sizeof(proto), "v%d", AURA_PROTO_VERSION);
    char lvgl_ver[16];
    snprintf(lvgl_ver, sizeof(lvgl_ver), "%d.%d.%d", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);

    lv_obj_t *info = crear_tarjeta(tab);
    crear_titulo_tarjeta(info, "DISPOSITIVO");
    crear_fila_clave_valor(info, "ID de placa", hw);
    crear_fila_clave_valor(info, "Protocolo AURA", proto);
    crear_fila_clave_valor(info, "Placa", "Waveshare ESP32-S3-Touch-LCD-7");
    crear_fila_clave_valor(info, "ESP-IDF", esp_get_idf_version());
    crear_fila_clave_valor(info, "LVGL", lvgl_ver);
}

static void estilizar_barra_tabs(lv_obj_t *tv)
{
    // En LVGL 9 la barra de pestañas es un contenedor con un lv_button por pestaña
    lv_obj_t *barra = lv_tabview_get_tab_bar(tv);
    lv_obj_set_style_bg_color(barra, COL_CARD, 0);
    lv_obj_set_style_bg_opa(barra, LV_OPA_COVER, 0);
    lv_obj_set_style_border_side(barra, LV_BORDER_SIDE_TOP, 0);
    lv_obj_set_style_border_color(barra, COL_BORDER, 0);
    lv_obj_set_style_border_width(barra, 1, 0);

    uint32_t cant = lv_obj_get_child_count(barra);
    for (uint32_t i = 0; i < cant; i++) {
        lv_obj_t *btn = lv_obj_get_child(barra, i);
        lv_obj_set_style_bg_opa(btn, LV_OPA_TRANSP, 0);
        lv_obj_set_style_text_color(btn, COL_MUTED, 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(btn, COL_BG, LV_STATE_CHECKED);
        lv_obj_set_style_text_color(btn, COL_TEXT, LV_STATE_CHECKED);
        lv_obj_set_style_border_side(btn, LV_BORDER_SIDE_TOP, LV_STATE_CHECKED);
        lv_obj_set_style_border_color(btn, COL_OK, LV_STATE_CHECKED);
        lv_obj_set_style_border_width(btn, 3, LV_STATE_CHECKED);
    }
}

esp_err_t ui_dashboard_create(void)
{
    if (!ui_port_lock(100)) {
        return ESP_ERR_TIMEOUT;
    }

    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, COL_BG, 0);
    lv_obj_set_style_text_color(scr, COL_TEXT, 0);

    // Barra superior (Header)
    lv_obj_t *header = lv_obj_create(scr);
    lv_obj_set_size(header, ANCHO_PANTALLA, ALTO_HEADER);
    lv_obj_set_pos(header, 0, 0);
    lv_obj_set_style_bg_color(header, COL_HEADER, 0);
    lv_obj_set_style_border_width(header, 0, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header, 12, 0);
    lv_obj_remove_flag(header, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(header, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(header, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_t *lbl_title = crear_label(header, "PROYECTO AURA - CENTRALIZADOR", lv_color_hex(0xFFFFFF));
    lv_obj_set_style_text_font(lbl_title, FUENTE_MEDIA, 0);
    s_lbl_gw = crear_label(header, "INICIALIZANDO RED...", COL_MUTED);

    // Navegacion inferior con cuatro pestañas
    lv_obj_t *tv = lv_tabview_create(scr);
    lv_obj_set_size(tv, ANCHO_PANTALLA, ALTO_PANTALLA - ALTO_HEADER);
    lv_obj_set_pos(tv, 0, ALTO_HEADER);
    lv_tabview_set_tab_bar_position(tv, LV_DIR_BOTTOM);
    lv_tabview_set_tab_bar_size(tv, ALTO_TABS);
    lv_obj_set_style_bg_color(tv, COL_BG, 0);
    lv_obj_set_style_bg_opa(tv, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(tv, 0, 0);
    lv_obj_set_style_border_width(tv, 0, 0);

    lv_obj_t *tab_dash = lv_tabview_add_tab(tv, "Dashboard");
    s_tab_disp = lv_tabview_add_tab(tv, "Dispositivos");
    lv_obj_t *tab_cfg = lv_tabview_add_tab(tv, "Config");
    lv_obj_t *tab_info = lv_tabview_add_tab(tv, "Acerca de");
    estilizar_barra_tabs(tv);

    // Sin deslizamiento horizontal entre pestañas: evita cambios de pestaña al hacer scroll
    lv_obj_remove_flag(lv_tabview_get_content(tv), LV_OBJ_FLAG_SCROLLABLE);

    crear_tab_dashboard(tab_dash);
    preparar_tab(s_tab_disp);
    crear_tab_config(tab_cfg);
    crear_tab_acerca(tab_info);

    // Velo de atenuacion por encima de todo; no captura toques
    lv_obj_t *velo = lv_obj_create(lv_layer_top());
    lv_obj_set_size(velo, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(velo, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(velo, (lv_opa_t)(OSCURECER_PCT * 255 / 100), 0);
    lv_obj_set_style_border_width(velo, 0, 0);
    lv_obj_set_style_radius(velo, 0, 0);
    lv_obj_remove_flag(velo, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_flag(velo, LV_OBJ_FLAG_SCROLLABLE);

    ui_bridge_registrar_observador(on_bridge_notif, NULL);
    lv_timer_create(refresco_timer_cb, 250, NULL);

    ui_dashboard_actualizar();

    ui_port_unlock();

    ESP_LOGI(TAG, "Dashboard creado exitosamente");
    return ESP_OK;
}
