#include "ui_dashboard.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "lvgl.h"
#include "ui_port.h"
#include "ui_bridge.h"
#include "cJSON.h"

// Paleta oscura del boceto
#define COL_BG      lv_color_hex(0x0F172A)
#define COL_CARD    lv_color_hex(0x1E293B)
#define COL_BORDER  lv_color_hex(0x334155)
#define COL_TEXT    lv_color_hex(0xF8FAFC)
#define COL_MUTED   lv_color_hex(0x94A3B8)
#define COL_HEADER  lv_color_hex(0x0B1E2D)
#define COL_OK      lv_color_hex(0x00B2AD)
#define COL_OFF     lv_color_hex(0xEF4444)

// La placa solo permite encender/apagar la retroiluminacion (CH422G), no regular el brillo.
// Se atenua por software con un velo negro semitransparente: 0 = sin atenuar, 100 = negro total.
#define OSCURECER_PCT 45

typedef struct { const char *clave; const char *nombre; const char *unidad; } campo_info_t;
static const campo_info_t CAMPOS[] = {
    { "temp_c",  "Temp", "C"   },
    { "hum_pct", "Hum",  "%"   },
    { "co2_ppm", "CO2",  "ppm" },
};

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
    lv_obj_t *lbl = lv_label_create(chip);
    lv_label_set_text(lbl, texto);
    lv_obj_set_style_text_color(lbl, color, 0);
}

static void crear_tarjeta_nodo(lv_obj_t *parent, const ui_nodo_t *n)
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

    lv_obj_t *cab = crear_contenedor_plano(card);
    lv_obj_set_flex_flow(cab, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cab, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_t *lbl_id = lv_label_create(cab);
    lv_label_set_text(lbl_id, n->hw_id);
    lv_obj_set_style_text_color(lbl_id, COL_TEXT, 0);
    crear_chip(cab, n->conectado ? "CONECTADO" : "AUSENTE", n->conectado ? COL_OK : COL_OFF);

    lv_obj_t *vals = crear_contenedor_plano(card);
    lv_obj_set_flex_flow(vals, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_column(vals, 16, 0);

    cJSON *root = n->tiene_telemetria ? cJSON_Parse(n->raw_values) : NULL;
    if (!root) {
        lv_obj_t *l = lv_label_create(vals);
        lv_label_set_text(l, "Esperando mediciones...");
        lv_obj_set_style_text_color(l, COL_MUTED, 0);
        return;
    }
    cJSON *campo = NULL;
    cJSON_ArrayForEach(campo, root) {
        const campo_info_t *info = buscar_campo(campo->string);
        const char *nombre = info ? info->nombre : campo->string;
        const char *unidad = info ? info->unidad : "";
        lv_obj_t *l = NULL;
        if (cJSON_IsNumber(campo)) {
            // El printf interno de LVGL no soporta %f: se formatea con snprintf de libc
            char texto[48];
            snprintf(texto, sizeof(texto), "%s: %.1f %s", nombre, campo->valuedouble, unidad);
            l = lv_label_create(vals);
            lv_label_set_text(l, texto);
        } else if (cJSON_IsBool(campo)) {
            l = lv_label_create(vals);
            lv_label_set_text_fmt(l, "%s: %s", nombre, cJSON_IsTrue(campo) ? "si" : "no");
        }
        if (l) lv_obj_set_style_text_color(l, COL_TEXT, 0);
    }
    cJSON_Delete(root);
}

static const char *TAG = "ui_dashboard";

static lv_obj_t *s_lbl_gw = NULL;
static lv_obj_t *s_cont_nodos = NULL;

// Corre en la tarea del emisor (sys_evt, mesh_hojas): solo marca el modelo como sucio.
// El redibujo se hace en la tarea de LVGL para no consumir stack ajeno.
static volatile bool s_sucio = true;

static void on_bridge_notif(ui_evento_tipo_t evento, const void *datos, void *user_data)
{
    s_sucio = true;
}

static void refresco_timer_cb(lv_timer_t *t)
{
    if (s_sucio) {
        s_sucio = false;
        ui_dashboard_actualizar();
    }
}

void ui_dashboard_actualizar(void)
{
    // Static: el snapshot ocupa ~2 KB y solo se usa desde la tarea de LVGL
    static ui_estado_aula_t snap;
    if (ui_bridge_get_snapshot(&snap) != ESP_OK) {
        return;
    }

    if (s_lbl_gw) {
        if (snap.red.gateway_conectado) {
            lv_label_set_text_fmt(s_lbl_gw, "GATEWAY OK | CH %d | %s", snap.red.canal, snap.red.aula);
            lv_obj_set_style_text_color(s_lbl_gw, lv_color_hex(0x22C55E), 0);
        } else if (snap.red.modo_isla) {
            lv_label_set_text_fmt(s_lbl_gw, "MODO ISLA | CH %d | %s", snap.red.canal, snap.red.aula);
            lv_obj_set_style_text_color(s_lbl_gw, lv_color_hex(0xF59E0B), 0);
        } else {
            lv_label_set_text_fmt(s_lbl_gw, "BUSCANDO GW... | %s", snap.red.aula);
            lv_obj_set_style_text_color(s_lbl_gw, lv_color_hex(0xEF4444), 0);
        }
    }

    if (s_cont_nodos) {
        lv_obj_clean(s_cont_nodos);

        if (snap.cant_nodos == 0) {
            lv_obj_t *lbl_vacio = lv_label_create(s_cont_nodos);
            lv_label_set_text(lbl_vacio, "Esperando hojas en el aula...\n(Las tarjetas apareceran automaticamente)");
            lv_obj_set_style_text_color(lbl_vacio, COL_MUTED, 0);
            lv_obj_set_style_text_align(lbl_vacio, LV_TEXT_ALIGN_CENTER, 0);
            lv_obj_set_style_pad_top(lbl_vacio, 30, 0);
        } else {
            for (int i = 0; i < snap.cant_nodos; i++) {
                crear_tarjeta_nodo(s_cont_nodos, &snap.nodos[i]);
            }
        }
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

    // Barra superior (Header)
    lv_obj_t *header = lv_obj_create(scr);
    lv_obj_set_size(header, 480, 75);
    lv_obj_set_pos(header, 0, 0);
    lv_obj_set_style_bg_color(header, COL_HEADER, 0);
    lv_obj_set_style_border_width(header, 0, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header, 12, 0);
    lv_obj_set_flex_flow(header, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(header, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_t *lbl_title = lv_label_create(header);
    lv_label_set_text(lbl_title, "PROYECTO AURA - CENTRALIZADOR");
    lv_obj_set_style_text_color(lbl_title, lv_color_hex(0xFFFFFF), 0);

    s_lbl_gw = lv_label_create(header);
    lv_label_set_text(s_lbl_gw, "INICIALIZANDO RED...");
    lv_obj_set_style_text_color(s_lbl_gw, lv_color_hex(0x94A3B8), 0);

    // Navegacion inferior: cuatro pestañas (las de Dashboard, Config y Acerca de son provisorias)
    lv_obj_t *tv = lv_tabview_create(scr);
    lv_obj_set_size(tv, 480, 725);
    lv_obj_set_pos(tv, 0, 75);
    lv_tabview_set_tab_bar_position(tv, LV_DIR_BOTTOM);
    lv_tabview_set_tab_bar_size(tv, 64);
    lv_obj_set_style_bg_color(tv, COL_BG, 0);

    lv_obj_t *barra = lv_tabview_get_tab_bar(tv);
    lv_obj_set_style_bg_color(barra, COL_CARD, 0);
    lv_obj_set_style_text_color(barra, COL_MUTED, LV_PART_ITEMS);
    lv_obj_set_style_text_color(barra, COL_TEXT, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(barra, COL_OK, LV_PART_ITEMS | LV_STATE_CHECKED);

    lv_obj_t *tab_dash = lv_tabview_add_tab(tv, "Dashboard");
    s_cont_nodos = lv_tabview_add_tab(tv, "Dispositivos");
    lv_obj_t *tab_cfg = lv_tabview_add_tab(tv, "Config");
    lv_obj_t *tab_info = lv_tabview_add_tab(tv, "Acerca de");

    lv_obj_t *tabs_provisorias[] = { tab_dash, tab_cfg, tab_info };
    const char *textos[] = { "Dashboard: resumen y control (en construccion)",
                             "Config: red y aula (en construccion)",
                             "Acerca de (en construccion)" };
    for (int i = 0; i < 3; i++) {
        lv_obj_t *l = lv_label_create(tabs_provisorias[i]);
        lv_label_set_text(l, textos[i]);
        lv_obj_set_style_text_color(l, COL_MUTED, 0);
        lv_obj_center(l);
    }

    lv_obj_set_style_pad_row(s_cont_nodos, 8, 0);
    lv_obj_set_flex_flow(s_cont_nodos, LV_FLEX_FLOW_COLUMN);

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
