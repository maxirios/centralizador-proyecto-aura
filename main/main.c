#include <string.h>
#include <stdio.h>
#include <math.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_mesh.h"
#include "esp_mac.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "aura_protocol.h"
#include "mesh_net.h"
#include "mesh_lote.h"
#include "mesh_hora.h"
#include "mesh_isla.h"
#include "mesh_hojas.h"
#include "mesh_control.h"
#include "bsp_display.h"
#include "bsp_touch.h"
#include "ui_bridge.h"
#include "ui_port.h"
#include "ui.h"
#include "screens.h"
#include "styles.h"
#include "relay_ctrl.h"
#include "driver/gpio.h"

#define PIN_BOTON GPIO_NUM_0

static const char *TAG = "mesh";
static esp_netif_t *netif_sta;

static bool enviar_a_raiz_cb(const uint8_t *data, size_t len)
{
    mesh_data_t m_data = {
        .data = (uint8_t *)data,
        .size = len,
        .proto = MESH_PROTO_BIN,
        .tos = MESH_TOS_P2P,
    };
    esp_err_t err = esp_mesh_send(NULL, &m_data, MESH_DATA_P2P, NULL, 0);
    ESP_LOGI(TAG, "Lote AURA enviado a raiz (%u bytes) -> %s", (unsigned)len, esp_err_to_name(err));
    return (err == ESP_OK);
}

static bool enviar_trama_mesh_cb(const uint8_t *mac, const uint8_t *data, size_t len)
{
    mesh_data_t m_data = {
        .data = (uint8_t *)data,
        .size = len,
        .proto = MESH_PROTO_BIN,
        .tos = MESH_TOS_P2P,
    };
    mesh_addr_t dest;
    mesh_addr_t *p_dest = NULL;
    if (mac != NULL) {
        memcpy(dest.addr, mac, 6);
        p_dest = &dest;
    }
    esp_err_t err = esp_mesh_send(p_dest, &m_data, MESH_DATA_P2P, NULL, 0);
    if (mac != NULL) {
        ESP_LOGI(TAG, "Trama enviada a " MACSTR " (%u B) -> %s",
                 MAC2STR(mac), (unsigned)len, esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "Trama enviada a raiz (%u B) -> %s",
                 (unsigned)len, esp_err_to_name(err));
    }
    return (err == ESP_OK);
}

static void on_control_resultado(const mesh_control_resultado_t *res)
{
    char hw[AURA_HW_ID_BYTES];
    aura_hw_id_de_mac(res->de_mac, hw);
    ESP_LOGI(TAG, "Confirmacion de ejecucion de %s: cid='%s' aplicado=%s motivo='%s'",
             hw, res->command_id, res->aplicado ? "SI" : "NO", res->motivo);
    ui_bridge_on_control_resultado(res);
}

#if CONFIG_AURA_ENABLE_DEMO_NODES
static void tarea_demo_nodos(void *arg)
{
    static const uint8_t mac_a[6] = {0xE0, 0x72, 0xA1, 0xD8, 0x48, 0xB0};
    static const uint8_t mac_b[6] = {0x40, 0x4C, 0xCA, 0x58, 0xB2, 0x14};
    while (true) {
        ui_bridge_on_mesh_telemetria(
            mac_a, 0,
            "{\"values\":{\"presencia\":1,\"luz_ventana_lx\":340.0,\"luz_aula_lx\":420.0,"
            "\"temp_c\":23.4,\"humedad_pct\":45.0,\"rele_canal1\":1},"
            "\"adaptador\":\"mac-e072a1d848b0\"}",
            false);
        ui_bridge_on_mesh_telemetria(
            mac_b, 0,
            "{\"values\":{\"presencia\":0,\"luz_ventana_lx\":180.0,\"luz_aula_lx\":290.0,"
            "\"temp_c\":24.1,\"humedad_pct\":48.0,\"rele_canal1\":0},"
            "\"adaptador\":\"mac-404cca58b214\"}",
            false);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
#endif

static volatile bool s_eez_ui_sucio = true;
static int s_ticker_idx = 0;
static int s_dev_ticker_idx[4] = {0, 0, 0, 0};

static void refresco_eez_ui_timer_cb(lv_timer_t *t);

static int clamp_int(int v, int lo, int hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

#define MAX_TICKER_ITEMS     28
#define TICKER_ITEM_LEN      32
#define TICKER_VISIBLE_CHIPS 4

static char s_ticker_items[MAX_TICKER_ITEMS][TICKER_ITEM_LEN];
static char s_dev_items[MAX_TICKER_ITEMS][TICKER_ITEM_LEN];

static int extraer_items_nodo_ticker(const ui_nodo_t *n, char items[][TICKER_ITEM_LEN], int count, int max_items)
{
    if (!n) return count;
    if (!isnan(n->temp) && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "Temp: %.1f°C", n->temp);
    }
    if (!isnan(n->hum) && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "Hum: %.0f%%", n->hum);
    }
    if (!isnan(n->luz_ventana) && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "Vent: %.0flx", n->luz_ventana);
    }
    if (!isnan(n->luz_aula) && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "Aula: %.0flx", n->luz_aula);
    }
    if (!isnan(n->co2) && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "CO2: %.0fppm", n->co2);
    }
    if (n->presencia >= 0 && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "Pres: %d", n->presencia ? 1 : 0);
    }
    if (n->tiene_actuador && count < max_items) {
        snprintf(items[count++], TICKER_ITEM_LEN, "Rele: %d", n->actuador_estado ? 1 : 0);
    }
    return count;
}

static int extraer_items_ticker(const ui_estado_aula_t *snap, char items[][TICKER_ITEM_LEN], int max_items)
{
    int count = 0;
    for (uint8_t i = 0; i < snap->cant_nodos && count < max_items; i++) {
        count = extraer_items_nodo_ticker(&snap->nodos[i], items, count, max_items);
    }
    return count;
}

void ui_ticker_step(lv_obj_t *target_btn, int delta)
{
    static ui_estado_aula_t snap;
    if (ui_bridge_get_snapshot(&snap) != ESP_OK) {
        return;
    }

    int dev_idx = -1;
    if (target_btn == objects.dev_c1_ticker__ticker_prev_btn || target_btn == objects.dev_c1_ticker__ticker_next_btn) {
        dev_idx = 0;
    } else if (target_btn == objects.dev_c2_ticker__ticker_prev_btn || target_btn == objects.dev_c2_ticker__ticker_next_btn) {
        dev_idx = 1;
    } else if (target_btn == objects.dev_c3_ticker__ticker_prev_btn || target_btn == objects.dev_c3_ticker__ticker_next_btn) {
        dev_idx = 2;
    } else if (target_btn == objects.dev_c4_ticker__ticker_prev_btn || target_btn == objects.dev_c4_ticker__ticker_next_btn) {
        dev_idx = 3;
    }

    if (dev_idx >= 0) {
        if (dev_idx >= snap.cant_nodos) return;
        int total = extraer_items_nodo_ticker(&snap.nodos[dev_idx], s_dev_items, 0, MAX_TICKER_ITEMS);
        int max_idx = (total > TICKER_VISIBLE_CHIPS) ? (total - TICKER_VISIBLE_CHIPS) : 0;
        int next_idx = clamp_int(s_dev_ticker_idx[dev_idx] + delta, 0, max_idx);
        if (next_idx != s_dev_ticker_idx[dev_idx]) {
            s_dev_ticker_idx[dev_idx] = next_idx;
            s_eez_ui_sucio = true;
            refresco_eez_ui_timer_cb(NULL);
        }
        return;
    }

    int total = extraer_items_ticker(&snap, s_ticker_items, MAX_TICKER_ITEMS);
    int max_idx = (total > TICKER_VISIBLE_CHIPS) ? (total - TICKER_VISIBLE_CHIPS) : 0;

    int next_idx = clamp_int(s_ticker_idx + delta, 0, max_idx);
    if (next_idx != s_ticker_idx) {
        s_ticker_idx = next_idx;
        s_eez_ui_sucio = true;
        refresco_eez_ui_timer_cb(NULL);
    }
}

static void on_ui_bridge_notif(ui_evento_tipo_t evento, const void *datos, void *user_data)
{
    (void)evento;
    (void)datos;
    (void)user_data;
    s_eez_ui_sucio = true;
}

static void aplicar_badge_estado(lv_obj_t *panel, lv_obj_t *lbl, bool online, const char *txt)
{
    if (!panel || !lbl) return;
    lv_label_set_text(lbl, txt);
    if (online) {
        remove_style_panel_badge_offline(panel);
        add_style_panel_badge_online(panel);
        remove_style_label_badge_offline(lbl);
        add_style_label_badge_online(lbl);
    } else {
        remove_style_panel_badge_online(panel);
        add_style_panel_badge_offline(panel);
        remove_style_label_badge_online(lbl);
        add_style_label_badge_offline(lbl);
    }
}

static void aplicar_btn_rele_estilo(lv_obj_t *btn, bool on)
{
    if (!btn) return;
    if (on) {
        remove_style_btn_relay_squircle_off(btn);
        add_style_btn_relay_squircle_on(btn);
    } else {
        remove_style_btn_relay_squircle_on(btn);
        add_style_btn_relay_squircle_off(btn);
    }
}

static void aplicar_btn_ticker_nav(lv_obj_t *btn, lv_obj_t *lbl, bool active)
{
    if (!btn || !lbl) return;
    if (active) {
        remove_style_btn_ticker_disabled(btn);
        add_style_btn_ticker_active(btn);
        remove_style_label_ticker_disabled(lbl);
        add_style_label_ticker_active(lbl);
    } else {
        remove_style_btn_ticker_active(btn);
        add_style_btn_ticker_disabled(btn);
        remove_style_label_ticker_active(lbl);
        add_style_label_ticker_disabled(lbl);
    }
}

static void aplicar_chip_ticker_alt(lv_obj_t *chip, bool alt)
{
    if (!chip) return;
    if (alt) {
        remove_style_panel_ticker_chip_base(chip);
        add_style_panel_ticker_chip_alt(chip);
    } else {
        remove_style_panel_ticker_chip_alt(chip);
        add_style_panel_ticker_chip_base(chip);
    }
}

typedef struct {
    lv_obj_t *prev_btn;
    lv_obj_t *prev_lbl;
    lv_obj_t *chips[TICKER_VISIBLE_CHIPS];
    lv_obj_t *lbls[TICKER_VISIBLE_CHIPS];
    lv_obj_t *next_btn;
    lv_obj_t *next_lbl;
    lv_obj_t *prog_bar;
} ticker_bar_widgets_t;

static void actualizar_ticker_instancia(const ticker_bar_widgets_t *tw,
                                        char items[][TICKER_ITEM_LEN], int total, int idx, int max_idx)
{
    if (!tw) return;

    if (total == 0) {
        for (int k = 0; k < TICKER_VISIBLE_CHIPS; k++) {
            if (tw->chips[k]) lv_obj_add_flag(tw->chips[k], LV_OBJ_FLAG_HIDDEN);
        }
        aplicar_btn_ticker_nav(tw->prev_btn, tw->prev_lbl, false);
        aplicar_btn_ticker_nav(tw->next_btn, tw->next_lbl, false);
        if (tw->prog_bar) lv_obj_add_flag(tw->prog_bar, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    for (int k = 0; k < TICKER_VISIBLE_CHIPS; k++) {
        int item_idx = idx + k;
        if (item_idx < total) {
            if (tw->chips[k]) {
                lv_obj_clear_flag(tw->chips[k], LV_OBJ_FLAG_HIDDEN);
                aplicar_chip_ticker_alt(tw->chips[k], (item_idx % 2) == 0);
            }
            if (tw->lbls[k]) {
                lv_label_set_text(tw->lbls[k], items[item_idx]);
            }
        } else {
            if (tw->chips[k]) lv_obj_add_flag(tw->chips[k], LV_OBJ_FLAG_HIDDEN);
        }
    }

    // Tope no circular en ambos extremos
    aplicar_btn_ticker_nav(tw->prev_btn, tw->prev_lbl, idx > 0);
    aplicar_btn_ticker_nav(tw->next_btn, tw->next_lbl, idx < max_idx);

    if (tw->prog_bar) {
        lv_obj_clear_flag(tw->prog_bar, LV_OBJ_FLAG_HIDDEN);
        const int thumb_len = 35;
        int start_val = (max_idx > 0) ? ((idx * (100 - thumb_len)) / max_idx) : 0;
        start_val = clamp_int(start_val, 0, 100 - thumb_len);
        int end_val = start_val + thumb_len;
        lv_bar_set_start_value(tw->prog_bar, 0, LV_ANIM_OFF);
        lv_bar_set_value(tw->prog_bar, end_val, LV_ANIM_OFF);
        lv_bar_set_start_value(tw->prog_bar, start_val, LV_ANIM_OFF);
    }
}

static void init_local_relays_ui(void)
{
    uint8_t count = relay_ctrl_get_count();
    if (objects.dash_relays_sub) {
        char sub[32];
        snprintf(sub, sizeof(sub), "%u CANALES", (unsigned)count);
        lv_label_set_text(objects.dash_relays_sub, sub);
    }

    lv_obj_t *tiles[5] = {
        objects.dash_relay_tile_1, objects.dash_relay_tile_2,
        objects.dash_relay_tile_3, objects.dash_relay_tile_4,
        objects.dash_relay_tile_5
    };
    lv_obj_t *btns[5] = {
        objects.dash_relay_btn_1, objects.dash_relay_btn_2,
        objects.dash_relay_btn_3, objects.dash_relay_btn_4,
        objects.dash_relay_btn_5
    };
    lv_obj_t *lbls[5] = {
        objects.dash_relay_lbl_1, objects.dash_relay_lbl_2,
        objects.dash_relay_lbl_3, objects.dash_relay_lbl_4,
        objects.dash_relay_lbl_5
    };

    for (uint8_t i = 0; i < 5; i++) {
        if (!tiles[i]) continue;
        if (i < count) {
            lv_obj_clear_flag(tiles[i], LV_OBJ_FLAG_HIDDEN);
            if (lbls[i]) {
                lv_label_set_text(lbls[i], relay_ctrl_get_label(i));
            }
            aplicar_btn_rele_estilo(btns[i], relay_ctrl_get_state(i));
        } else {
            lv_obj_add_flag(tiles[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

typedef struct {
    lv_obj_t *card;
    lv_obj_t *node_lbl;
    lv_obj_t *badge;
    lv_obj_t *badge_lbl;
    lv_obj_t *act_title;
    lv_obj_t *act_sub;
    lv_obj_t *act_btn;
} dash_act_widgets_t;

static void poblar_dash_act_card(const dash_act_widgets_t *w, const ui_nodo_t *n)
{
    if (!w || !w->card || !n) return;
    lv_obj_clear_flag(w->card, LV_OBJ_FLAG_HIDDEN);

    const char *id_str = (n->adaptador[0] != '\0') ? n->adaptador : n->hw_id;
    if (w->node_lbl) lv_label_set_text(w->node_lbl, id_str);

    aplicar_badge_estado(w->badge, w->badge_lbl, n->conectado, n->conectado ? "EN LINEA" : "SIN CONEXION");

    if (w->act_title) {
        lv_label_set_text(w->act_title, "ACTUADOR HOJA");
    }
    if (w->act_sub) {
        if (n->tiene_actuador) {
            lv_label_set_text(w->act_sub, n->actuador_estado ? "Estado: ENCENDIDO" : "Estado: APAGADO");
        } else {
            lv_label_set_text(w->act_sub, "Toque para conmutar");
        }
    }
    aplicar_btn_rele_estilo(w->act_btn, n->actuador_estado);
}

typedef struct {
    lv_obj_t *box;
    lv_obj_t *title;
    lv_obj_t *badge;
    lv_obj_t *badge_lbl;
    lv_obj_t *s1_val;
    lv_obj_t *s1_bar;
    lv_obj_t *s2_val;
    lv_obj_t *s2_bar;
    lv_obj_t *s3_val;
    lv_obj_t *s3_bar;
    lv_obj_t *s4_lbl;
    lv_obj_t *s4_val;
    lv_obj_t *s4_bar;
    lv_obj_t *pres_badge;
    lv_obj_t *pres_lbl;
} dash_node_widgets_t;

static void poblar_dash_node_box(const dash_node_widgets_t *w, const ui_nodo_t *n)
{
    if (!w || !w->box || !n) return;
    lv_obj_clear_flag(w->box, LV_OBJ_FLAG_HIDDEN);

    const char *id_str = (n->adaptador[0] != '\0') ? n->adaptador : n->hw_id;
    if (w->title) lv_label_set_text(w->title, id_str);

    aplicar_badge_estado(w->badge, w->badge_lbl, n->conectado, n->conectado ? "EN LINEA" : "SIN CONEXION");

    char buf[64];
    if (!isnan(n->temp)) {
        snprintf(buf, sizeof(buf), "%.1f °C", n->temp);
        if (w->s1_val) lv_label_set_text(w->s1_val, buf);
        if (w->s1_bar) lv_bar_set_value(w->s1_bar, clamp_int((int)n->temp, 0, 50), LV_ANIM_OFF);
    } else {
        if (w->s1_val) lv_label_set_text(w->s1_val, "--.- °C");
        if (w->s1_bar) lv_bar_set_value(w->s1_bar, 0, LV_ANIM_OFF);
    }

    if (!isnan(n->hum)) {
        snprintf(buf, sizeof(buf), "%.0f %%", n->hum);
        if (w->s2_val) lv_label_set_text(w->s2_val, buf);
        if (w->s2_bar) lv_bar_set_value(w->s2_bar, clamp_int((int)n->hum, 0, 100), LV_ANIM_OFF);
    } else {
        if (w->s2_val) lv_label_set_text(w->s2_val, "-- %");
        if (w->s2_bar) lv_bar_set_value(w->s2_bar, 0, LV_ANIM_OFF);
    }

    if (!isnan(n->luz_ventana)) {
        snprintf(buf, sizeof(buf), "%.0f lx", n->luz_ventana);
        if (w->s3_val) lv_label_set_text(w->s3_val, buf);
        if (w->s3_bar) lv_bar_set_value(w->s3_bar, clamp_int((int)n->luz_ventana, 0, 1000), LV_ANIM_OFF);
    } else {
        if (w->s3_val) lv_label_set_text(w->s3_val, "-- lx");
        if (w->s3_bar) lv_bar_set_value(w->s3_bar, 0, LV_ANIM_OFF);
    }

    if (!isnan(n->luz_aula)) {
        if (w->s4_lbl) lv_label_set_text(w->s4_lbl, "LUZ AULA");
        snprintf(buf, sizeof(buf), "%.0f lx", n->luz_aula);
        if (w->s4_val) lv_label_set_text(w->s4_val, buf);
        if (w->s4_bar) lv_bar_set_value(w->s4_bar, clamp_int((int)n->luz_aula, 0, 1000), LV_ANIM_OFF);
    } else if (!isnan(n->co2)) {
        if (w->s4_lbl) lv_label_set_text(w->s4_lbl, "CO2 AMB.");
        snprintf(buf, sizeof(buf), "%.0f ppm", n->co2);
        if (w->s4_val) lv_label_set_text(w->s4_val, buf);
        int scaled = clamp_int((int)((n->co2 * 1000.0f) / 2000.0f), 0, 1000);
        if (w->s4_bar) lv_bar_set_value(w->s4_bar, scaled, LV_ANIM_OFF);
    } else {
        if (w->s4_lbl) lv_label_set_text(w->s4_lbl, "LUZ AULA");
        if (w->s4_val) lv_label_set_text(w->s4_val, "-- lx");
        if (w->s4_bar) lv_bar_set_value(w->s4_bar, 0, LV_ANIM_OFF);
    }

    if (n->presencia == 1) {
        aplicar_badge_estado(w->pres_badge, w->pres_lbl, true, "DETECTADO");
    } else if (n->presencia == 0) {
        aplicar_badge_estado(w->pres_badge, w->pres_lbl, false, "LIBRE");
    } else {
        aplicar_badge_estado(w->pres_badge, w->pres_lbl, false, "SIN DATO");
    }
}

static void refresco_eez_ui_timer_cb(lv_timer_t *t)
{
    (void)t;
    if (!s_eez_ui_sucio) return;
    s_eez_ui_sucio = false;

    static ui_estado_aula_t snap;
    if (ui_bridge_get_snapshot(&snap) != ESP_OK) return;

    uint8_t online_cnt = 0;
    for (uint8_t i = 0; i < snap.cant_nodos; i++) {
        if (snap.nodos[i].conectado) online_cnt++;
    }

    // Subtitulo de Aula en las 5 cabeceras ("Aula: Sin asignar" por defecto)
    char aula_hdr[48];
    if (snap.red.aula[0] != '\0') {
        snprintf(aula_hdr, sizeof(aula_hdr), "Aula: %s", snap.red.aula);
    } else {
        snprintf(aula_hdr, sizeof(aula_hdr), "Aula: Sin asignar");
    }
    if (objects.dashboard_act_header__header_subtitle)  lv_label_set_text(objects.dashboard_act_header__header_subtitle, aula_hdr);
    if (objects.dashboard_sens_header__header_subtitle) lv_label_set_text(objects.dashboard_sens_header__header_subtitle, aula_hdr);
    if (objects.devices_header__header_subtitle)        lv_label_set_text(objects.devices_header__header_subtitle, aula_hdr);
    if (objects.config_header__header_subtitle)         lv_label_set_text(objects.config_header__header_subtitle, aula_hdr);
    if (objects.about_header__header_subtitle)          lv_label_set_text(objects.about_header__header_subtitle, aula_hdr);

    char mesh_txt[32];
    if (snap.red.modo_isla) {
        snprintf(mesh_txt, sizeof(mesh_txt), "Isla (%u)", (unsigned)online_cnt);
    } else {
        snprintf(mesh_txt, sizeof(mesh_txt), "Mesh (%u)", (unsigned)online_cnt);
    }
    if (objects.dashboard_act_header__header_mesh_lbl)  lv_label_set_text(objects.dashboard_act_header__header_mesh_lbl, mesh_txt);
    if (objects.dashboard_sens_header__header_mesh_lbl) lv_label_set_text(objects.dashboard_sens_header__header_mesh_lbl, mesh_txt);
    if (objects.devices_header__header_mesh_lbl)        lv_label_set_text(objects.devices_header__header_mesh_lbl, mesh_txt);
    if (objects.config_header__header_mesh_lbl)         lv_label_set_text(objects.config_header__header_mesh_lbl, mesh_txt);
    if (objects.about_header__header_mesh_lbl)          lv_label_set_text(objects.about_header__header_mesh_lbl, mesh_txt);

    // Actualizar Ticker en ambas páginas del Tablero (4 chips intercalados + barra de desplazamiento + topes)
    int total_items = extraer_items_ticker(&snap, s_ticker_items, MAX_TICKER_ITEMS);
    int max_idx = (total_items > TICKER_VISIBLE_CHIPS) ? (total_items - TICKER_VISIBLE_CHIPS) : 0;
    s_ticker_idx = clamp_int(s_ticker_idx, 0, max_idx);

    const ticker_bar_widgets_t tw_act = {
        .prev_btn = objects.dashboard_act_ticker__ticker_prev_btn,
        .prev_lbl = objects.dashboard_act_ticker__ticker_prev_lbl,
        .chips = {
            objects.dashboard_act_ticker__ticker_chip_1,
            objects.dashboard_act_ticker__ticker_chip_2,
            objects.dashboard_act_ticker__ticker_chip_3,
            objects.dashboard_act_ticker__ticker_chip_4,
        },
        .lbls = {
            objects.dashboard_act_ticker__ticker_chip_lbl_1,
            objects.dashboard_act_ticker__ticker_chip_lbl_2,
            objects.dashboard_act_ticker__ticker_chip_lbl_3,
            objects.dashboard_act_ticker__ticker_chip_lbl_4,
        },
        .next_btn = objects.dashboard_act_ticker__ticker_next_btn,
        .next_lbl = objects.dashboard_act_ticker__ticker_next_lbl,
        .prog_bar = objects.dashboard_act_ticker__ticker_prog_bar,
    };
    const ticker_bar_widgets_t tw_sens = {
        .prev_btn = objects.dashboard_sens_ticker__ticker_prev_btn,
        .prev_lbl = objects.dashboard_sens_ticker__ticker_prev_lbl,
        .chips = {
            objects.dashboard_sens_ticker__ticker_chip_1,
            objects.dashboard_sens_ticker__ticker_chip_2,
            objects.dashboard_sens_ticker__ticker_chip_3,
            objects.dashboard_sens_ticker__ticker_chip_4,
        },
        .lbls = {
            objects.dashboard_sens_ticker__ticker_chip_lbl_1,
            objects.dashboard_sens_ticker__ticker_chip_lbl_2,
            objects.dashboard_sens_ticker__ticker_chip_lbl_3,
            objects.dashboard_sens_ticker__ticker_chip_lbl_4,
        },
        .next_btn = objects.dashboard_sens_ticker__ticker_next_btn,
        .next_lbl = objects.dashboard_sens_ticker__ticker_next_lbl,
        .prog_bar = objects.dashboard_sens_ticker__ticker_prog_bar,
    };
    actualizar_ticker_instancia(&tw_act, s_ticker_items, total_items, s_ticker_idx, max_idx);
    actualizar_ticker_instancia(&tw_sens, s_ticker_items, total_items, s_ticker_idx, max_idx);

    if (objects.dash_nodes_sec_tag) {
        char tag_txt[32];
        snprintf(tag_txt, sizeof(tag_txt), "%u EN LINEA", (unsigned)online_cnt);
        lv_label_set_text(objects.dash_nodes_sec_tag, tag_txt);
    }

    dash_act_widgets_t a1 = {
        .card = objects.dash_n1_act_card,
        .node_lbl = objects.dash_n1_act_node,
        .badge = objects.dash_n1_act_badge,
        .badge_lbl = objects.dash_n1_act_badge_lbl,
        .act_title = objects.dash_n1_act_title,
        .act_sub = objects.dash_n1_act_sub,
        .act_btn = objects.dash_n1_act_btn,
    };
    dash_act_widgets_t a2 = {
        .card = objects.dash_n2_act_card,
        .node_lbl = objects.dash_n2_act_node,
        .badge = objects.dash_n2_act_badge,
        .badge_lbl = objects.dash_n2_act_badge_lbl,
        .act_title = objects.dash_n2_act_title,
        .act_sub = objects.dash_n2_act_sub,
        .act_btn = objects.dash_n2_act_btn,
    };

    dash_node_widgets_t w1 = {
        .box = objects.dash_node1_box,
        .title = objects.dash_n1_title,
        .badge = objects.dash_n1_badge,
        .badge_lbl = objects.dash_n1_badge_lbl,
        .s1_val = objects.dash_n1_s1_val, .s1_bar = objects.dash_n1_s1_bar,
        .s2_val = objects.dash_n1_s2_val, .s2_bar = objects.dash_n1_s2_bar,
        .s3_val = objects.dash_n1_s3_val, .s3_bar = objects.dash_n1_s3_bar,
        .s4_lbl = objects.dash_n1_s4_lbl, .s4_val = objects.dash_n1_s4_val, .s4_bar = objects.dash_n1_s4_bar,
        .pres_badge = objects.dash_n1_pres_badge, .pres_lbl = objects.dash_n1_pres_lbl,
    };
    dash_node_widgets_t w2 = {
        .box = objects.dash_node2_box,
        .title = objects.dash_n2_title,
        .badge = objects.dash_n2_badge,
        .badge_lbl = objects.dash_n2_badge_lbl,
        .s1_val = objects.dash_n2_s1_val, .s1_bar = objects.dash_n2_s1_bar,
        .s2_val = objects.dash_n2_s2_val, .s2_bar = objects.dash_n2_s2_bar,
        .s3_val = objects.dash_n2_s3_val, .s3_bar = objects.dash_n2_s3_bar,
        .s4_lbl = objects.dash_n2_s4_lbl, .s4_val = objects.dash_n2_s4_val, .s4_bar = objects.dash_n2_s4_bar,
        .pres_badge = objects.dash_n2_pres_badge, .pres_lbl = objects.dash_n2_pres_lbl,
    };

    if (snap.cant_nodos == 0) {
        if (objects.dash_act_empty_card) lv_obj_clear_flag(objects.dash_act_empty_card, LV_OBJ_FLAG_HIDDEN);
        if (objects.dash_n1_act_card)    lv_obj_add_flag(objects.dash_n1_act_card, LV_OBJ_FLAG_HIDDEN);
        if (objects.dash_n2_act_card)    lv_obj_add_flag(objects.dash_n2_act_card, LV_OBJ_FLAG_HIDDEN);

        if (objects.dash_empty_card) lv_obj_clear_flag(objects.dash_empty_card, LV_OBJ_FLAG_HIDDEN);
        if (objects.dash_node1_box)  lv_obj_add_flag(objects.dash_node1_box, LV_OBJ_FLAG_HIDDEN);
        if (objects.dash_node2_box)  lv_obj_add_flag(objects.dash_node2_box, LV_OBJ_FLAG_HIDDEN);
    } else {
        if (objects.dash_act_empty_card) lv_obj_add_flag(objects.dash_act_empty_card, LV_OBJ_FLAG_HIDDEN);
        if (objects.dash_empty_card)     lv_obj_add_flag(objects.dash_empty_card, LV_OBJ_FLAG_HIDDEN);

        poblar_dash_act_card(&a1, &snap.nodos[0]);
        poblar_dash_node_box(&w1, &snap.nodos[0]);

        if (snap.cant_nodos >= 2) {
            poblar_dash_act_card(&a2, &snap.nodos[1]);
            poblar_dash_node_box(&w2, &snap.nodos[1]);
        } else {
            if (objects.dash_n2_act_card) lv_obj_add_flag(objects.dash_n2_act_card, LV_OBJ_FLAG_HIDDEN);
            if (objects.dash_node2_box)   lv_obj_add_flag(objects.dash_node2_box, LV_OBJ_FLAG_HIDDEN);
        }
    }

    char strip_buf[32];
    // Pantalla Dispositivos
    if (objects.dev_sec_total) {
        snprintf(strip_buf, sizeof(strip_buf), "%u Nodos Registrados", (unsigned)snap.cant_nodos);
        lv_label_set_text(objects.dev_sec_total, strip_buf);
    }

    lv_obj_t *dev_cards[4] = { objects.dev_card_1, objects.dev_card_2, objects.dev_card_3, objects.dev_card_4 };
    lv_obj_t *dev_ids[4]   = { objects.dev_c1_id, objects.dev_c2_id, objects.dev_c3_id, objects.dev_c4_id };
    lv_obj_t *dev_bdgs[4]  = { objects.dev_c1_badge, objects.dev_c2_badge, objects.dev_c3_badge, objects.dev_c4_badge };
    lv_obj_t *dev_blbls[4] = { objects.dev_c1_badge_lbl, objects.dev_c2_badge_lbl, objects.dev_c3_badge_lbl, objects.dev_c4_badge_lbl };

    ticker_bar_widgets_t tw_devs[4] = {
        {
            .prev_btn = objects.dev_c1_ticker__ticker_prev_btn,
            .prev_lbl = objects.dev_c1_ticker__ticker_prev_lbl,
            .chips = {
                objects.dev_c1_ticker__ticker_chip_1,
                objects.dev_c1_ticker__ticker_chip_2,
                objects.dev_c1_ticker__ticker_chip_3,
                objects.dev_c1_ticker__ticker_chip_4,
            },
            .lbls = {
                objects.dev_c1_ticker__ticker_chip_lbl_1,
                objects.dev_c1_ticker__ticker_chip_lbl_2,
                objects.dev_c1_ticker__ticker_chip_lbl_3,
                objects.dev_c1_ticker__ticker_chip_lbl_4,
            },
            .next_btn = objects.dev_c1_ticker__ticker_next_btn,
            .next_lbl = objects.dev_c1_ticker__ticker_next_lbl,
            .prog_bar = objects.dev_c1_ticker__ticker_prog_bar,
        },
        {
            .prev_btn = objects.dev_c2_ticker__ticker_prev_btn,
            .prev_lbl = objects.dev_c2_ticker__ticker_prev_lbl,
            .chips = {
                objects.dev_c2_ticker__ticker_chip_1,
                objects.dev_c2_ticker__ticker_chip_2,
                objects.dev_c2_ticker__ticker_chip_3,
                objects.dev_c2_ticker__ticker_chip_4,
            },
            .lbls = {
                objects.dev_c2_ticker__ticker_chip_lbl_1,
                objects.dev_c2_ticker__ticker_chip_lbl_2,
                objects.dev_c2_ticker__ticker_chip_lbl_3,
                objects.dev_c2_ticker__ticker_chip_lbl_4,
            },
            .next_btn = objects.dev_c2_ticker__ticker_next_btn,
            .next_lbl = objects.dev_c2_ticker__ticker_next_lbl,
            .prog_bar = objects.dev_c2_ticker__ticker_prog_bar,
        },
        {
            .prev_btn = objects.dev_c3_ticker__ticker_prev_btn,
            .prev_lbl = objects.dev_c3_ticker__ticker_prev_lbl,
            .chips = {
                objects.dev_c3_ticker__ticker_chip_1,
                objects.dev_c3_ticker__ticker_chip_2,
                objects.dev_c3_ticker__ticker_chip_3,
                objects.dev_c3_ticker__ticker_chip_4,
            },
            .lbls = {
                objects.dev_c3_ticker__ticker_chip_lbl_1,
                objects.dev_c3_ticker__ticker_chip_lbl_2,
                objects.dev_c3_ticker__ticker_chip_lbl_3,
                objects.dev_c3_ticker__ticker_chip_lbl_4,
            },
            .next_btn = objects.dev_c3_ticker__ticker_next_btn,
            .next_lbl = objects.dev_c3_ticker__ticker_next_lbl,
            .prog_bar = objects.dev_c3_ticker__ticker_prog_bar,
        },
        {
            .prev_btn = objects.dev_c4_ticker__ticker_prev_btn,
            .prev_lbl = objects.dev_c4_ticker__ticker_prev_lbl,
            .chips = {
                objects.dev_c4_ticker__ticker_chip_1,
                objects.dev_c4_ticker__ticker_chip_2,
                objects.dev_c4_ticker__ticker_chip_3,
                objects.dev_c4_ticker__ticker_chip_4,
            },
            .lbls = {
                objects.dev_c4_ticker__ticker_chip_lbl_1,
                objects.dev_c4_ticker__ticker_chip_lbl_2,
                objects.dev_c4_ticker__ticker_chip_lbl_3,
                objects.dev_c4_ticker__ticker_chip_lbl_4,
            },
            .next_btn = objects.dev_c4_ticker__ticker_next_btn,
            .next_lbl = objects.dev_c4_ticker__ticker_next_lbl,
            .prog_bar = objects.dev_c4_ticker__ticker_prog_bar,
        },
    };

    if (snap.cant_nodos == 0) {
        if (objects.dev_empty_card) lv_obj_clear_flag(objects.dev_empty_card, LV_OBJ_FLAG_HIDDEN);
        for (int i = 0; i < 4; i++) {
            if (dev_cards[i]) lv_obj_add_flag(dev_cards[i], LV_OBJ_FLAG_HIDDEN);
        }
    } else {
        if (objects.dev_empty_card) lv_obj_add_flag(objects.dev_empty_card, LV_OBJ_FLAG_HIDDEN);
        for (int i = 0; i < 4; i++) {
            if (!dev_cards[i]) continue;
            if (i < snap.cant_nodos) {
                const ui_nodo_t *n = &snap.nodos[i];
                lv_obj_clear_flag(dev_cards[i], LV_OBJ_FLAG_HIDDEN);
                const char *id_str = (n->adaptador[0] != '\0') ? n->adaptador : n->hw_id;
                if (dev_ids[i]) lv_label_set_text(dev_ids[i], id_str);
                aplicar_badge_estado(dev_bdgs[i], dev_blbls[i], n->conectado, n->conectado ? "EN LINEA" : "SIN CONEXION");

                int dev_total = extraer_items_nodo_ticker(n, s_dev_items, 0, MAX_TICKER_ITEMS);
                int dev_max_idx = (dev_total > TICKER_VISIBLE_CHIPS) ? (dev_total - TICKER_VISIBLE_CHIPS) : 0;
                s_dev_ticker_idx[i] = clamp_int(s_dev_ticker_idx[i], 0, dev_max_idx);
                actualizar_ticker_instancia(&tw_devs[i], s_dev_items, dev_total, s_dev_ticker_idx[i], dev_max_idx);
            } else {
                lv_obj_add_flag(dev_cards[i], LV_OBJ_FLAG_HIDDEN);
            }
        }
    }

    // Pantalla Configuracion
    if (objects.cfg_val_aula) {
        lv_label_set_text(objects.cfg_val_aula, snap.red.aula[0] != '\0' ? snap.red.aula : "Sin asignar");
    }
    if (objects.cfg_val_chan) {
        char ch_buf[48];
        snprintf(ch_buf, sizeof(ch_buf), "Canal %u - Mesh ID MESH01", (unsigned)snap.red.canal);
        lv_label_set_text(objects.cfg_val_chan, ch_buf);
    }
    if (objects.cfg_gw_badge && objects.cfg_gw_badge_lbl) {
        bool gw_ok = snap.red.gateway_conectado && !snap.red.modo_isla;
        const char *gw_txt = snap.red.modo_isla ? "MODO ISLA" : (gw_ok ? "CONECTADO" : "BUSCANDO");
        aplicar_badge_estado(objects.cfg_gw_badge, objects.cfg_gw_badge_lbl, gw_ok, gw_txt);
    }
}

static void tarea_boton_local(void *arg)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PIN_BOTON),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    int anterior = 1;
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(50));
        int nivel = gpio_get_level(PIN_BOTON);
        if (anterior == 1 && nivel == 0) {
            vTaskDelay(pdMS_TO_TICKS(30));
            if (gpio_get_level(PIN_BOTON) == 0) {
                uint8_t mac_hoja[6];
                if (mesh_hojas_get_ultima(mac_hoja)) {
                    char hw[AURA_HW_ID_BYTES];
                    aura_hw_id_de_mac(mac_hoja, hw);
                    ESP_LOGI(TAG, "Boton pulsado: orden conmutar LED enviada a %s", hw);
                    ui_bridge_conmutar_actuador(mac_hoja, "led");
                } else {
                    ESP_LOGW(TAG, "Boton pulsado: sin hojas activas en el aula");
                }
            }
        }
        anterior = nivel;
    }
}

static void on_mesh_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (id == MESH_EVENT_STARTED) {
        if (mesh_isla_esta_activa()) {
            esp_mesh_set_self_organized(false, false);
        }
        mesh_net_anunciar_aula();
        ui_bridge_actualizar_red(!mesh_isla_esta_activa(), mesh_isla_esta_activa(), mesh_isla_get_canal(), mesh_net_get_aula());
    } else if (id == MESH_EVENT_SCAN_DONE) {
        if (mesh_isla_esta_activa()) {
            mesh_event_scan_done_t *s = (mesh_event_scan_done_t *)data;
            mesh_isla_procesar_escaneo(s->number);
        }
    } else if (id == MESH_EVENT_PARENT_CONNECTED) {
        mesh_event_connected_t *c = (mesh_event_connected_t *)data;
        mesh_isla_notificar_padre_conectado(c->connected.channel);
        mesh_net_anunciar_aula();
        ui_bridge_actualizar_red(true, false, c->connected.channel, mesh_net_get_aula());
        if (esp_mesh_is_root()) {
            esp_netif_dhcpc_start(netif_sta);
        } else {
            mesh_hora_pedir_sincronizacion();
        }
    } else if (id == MESH_EVENT_PARENT_DISCONNECTED) {
        mesh_isla_notificar_padre_desconectado();
        ui_bridge_actualizar_red(false, mesh_isla_esta_activa(), 0, mesh_net_get_aula());
    } else if (id == MESH_EVENT_CHILD_CONNECTED) {
        mesh_event_child_connected_t *c = (mesh_event_child_connected_t *)data;
        mesh_hojas_notificar_child_connected(c->mac);
        ESP_LOGI(TAG, "Hijo conectado a la malla: " MACSTR " (aid %d)", MAC2STR(c->mac), c->aid);
    } else if (id == MESH_EVENT_CHILD_DISCONNECTED) {
        mesh_event_child_disconnected_t *c = (mesh_event_child_disconnected_t *)data;
        mesh_hojas_notificar_child_disconnected(c->mac);
        ESP_LOGW(TAG, "Hijo desconectado de la malla: " MACSTR, MAC2STR(c->mac));
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_LOGI(TAG, "Protocolo AURA v%d cargado (cabecera %d B, payload max %d B)",
             AURA_PROTO_VERSION, AURA_CABECERA_BYTES, AURA_PAYLOAD_MAX);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_netif_create_default_wifi_mesh_netifs(&netif_sta, NULL));

    wifi_init_config_t wifi_cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(mesh_isla_init((const uint8_t *)"MESH01"));

    ESP_ERROR_CHECK(esp_mesh_init());
    ESP_ERROR_CHECK(esp_event_handler_register(MESH_EVENT, ESP_EVENT_ANY_ID,
                           &on_mesh_event, NULL));
    ESP_ERROR_CHECK(esp_mesh_fix_root(true));
    ESP_ERROR_CHECK(esp_mesh_set_max_layer(6));
    ESP_ERROR_CHECK(esp_mesh_disable_ps());
    ESP_ERROR_CHECK(esp_mesh_set_ap_authmode(WIFI_AUTH_OPEN));

    mesh_cfg_t cfg = MESH_INIT_CONFIG_DEFAULT();
    memcpy(cfg.mesh_id.addr, "MESH01", 6);
    const char *router = mesh_isla_esta_activa() ? MESH_ROUTER_ISLA : "NO_EXISTE_ESTE_ROUTER";
    cfg.router.ssid_len = strlen(router);
    memcpy(cfg.router.ssid, router, cfg.router.ssid_len);
    cfg.channel = mesh_isla_esta_activa() ? mesh_isla_get_canal() : 0;
    cfg.allow_channel_switch = !mesh_isla_esta_activa();
    cfg.mesh_ap.max_connection = 4;
    cfg.mesh_ap.nonmesh_max_connection = 0;
    cfg.mesh_ap.password[0] = '\0';

    if (mesh_isla_esta_activa()) {
        ESP_ERROR_CHECK(esp_mesh_set_type(MESH_ROOT));
    }
    ESP_ERROR_CHECK(esp_mesh_set_config(&cfg));
    ESP_ERROR_CHECK(esp_mesh_start());

    ESP_ERROR_CHECK(mesh_net_init());
    ESP_ERROR_CHECK(mesh_net_anunciar_aula());
    ESP_ERROR_CHECK(relay_ctrl_init());
    ESP_ERROR_CHECK(ui_bridge_init());

#if CONFIG_AURA_ENABLE_DEMO_NODES
    xTaskCreate(tarea_demo_nodos, "demo_nodos", 4096, NULL, 3, NULL);
#endif

    ui_bridge_actualizar_red(!mesh_isla_esta_activa(), mesh_isla_esta_activa(), mesh_isla_get_canal(), mesh_net_get_aula());

    ESP_ERROR_CHECK(mesh_hojas_init(mesh_net_get_aula(), ui_bridge_on_mesh_evento_hoja, ui_bridge_on_mesh_telemetria));
    ESP_ERROR_CHECK(mesh_control_init(on_control_resultado));
    ESP_ERROR_CHECK(mesh_lote_init(enviar_a_raiz_cb));
    ESP_ERROR_CHECK(mesh_hora_init(enviar_trama_mesh_cb));

    esp_err_t err_touch = bsp_touch_init();
    if (err_touch == ESP_OK) {
        ESP_LOGI(TAG, "BSP Touch Goodix GT911 inicializado con exito");
    } else {
        ESP_LOGW(TAG, "BSP Touch no detectado (err=%s)", esp_err_to_name(err_touch));
    }

    esp_err_t err_disp = bsp_display_init(NULL);
    if (err_disp == ESP_OK) {
        ESP_LOGI(TAG, "BSP Display RGB inicializado con exito");
        esp_err_t err_ui = ui_port_init();
        if (err_ui == ESP_OK) {
            if (ui_port_lock(100)) {
                ui_init();
                init_local_relays_ui();
                s_eez_ui_sucio = true;
                refresco_eez_ui_timer_cb(NULL);
                ui_bridge_registrar_observador(on_ui_bridge_notif, NULL);
                lv_timer_create(refresco_eez_ui_timer_cb, 250, NULL);
                ui_port_unlock();
                ESP_LOGI(TAG, "Interfaz EEZ Studio inicializada con exito");
            }
        } else {
            ESP_LOGE(TAG, "Fallo al inicializar ui_port (%s)", esp_err_to_name(err_ui));
        }
    } else {
        ESP_LOGW(TAG, "BSP Display no inicializado (err=%s)", esp_err_to_name(err_disp));
    }

    if (err_disp != ESP_OK) {
        xTaskCreate(tarea_boton_local, "btn_local", 2048, NULL, 3, NULL);
    }

    static uint8_t rx_buf[AURA_TRAMA_MAX];
    while (true) {
        mesh_addr_t from;
        mesh_data_t data = { .data = rx_buf, .size = sizeof(rx_buf) };
        int flag = 0;
        if (esp_mesh_recv(&from, &data, 1000, &flag, NULL, 0) == ESP_OK) {
            aura_validacion_t v = aura_trama_validar(rx_buf, data.size);
            if (v == AURA_TRAMA_OK) {
                const aura_trama_t *t = (const aura_trama_t *)rx_buf;

                if (t->tipo == AURA_TIPO_HORA && mesh_hora_procesar_trama(from.addr, t)) {
                    continue;
                }

                if (t->tipo == AURA_TIPO_RESULTADO) {
                    mesh_control_procesar_resultado(from.addr, t);
                }

                bool descartar_reenvio = false;
                mesh_hojas_procesar_trama(from.addr, t, &descartar_reenvio);
                if (descartar_reenvio || mesh_isla_esta_activa()) {
                    continue;
                }

                bool prioritario = (t->tipo == AURA_TIPO_ALERTA ||
                                    t->tipo == AURA_TIPO_RESULTADO ||
                                    t->tipo == AURA_TIPO_REPORTE);
                ESP_LOGI(TAG, "Trama valida de " MACSTR " [%s], seq=%u, prioritario=%d",
                         MAC2STR(from.addr), aura_tipo_a_str(t->tipo), t->seq, prioritario);
                mesh_lote_agregar(from.addr, rx_buf, data.size, prioritario);
            } else {
                ESP_LOGD(TAG, "Dato recibido de " MACSTR " no es trama simple AURA (%d bytes)",
                         MAC2STR(from.addr), data.size);
            }
        }
    }
}
