#include "ui_view_test.h"
#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "ui_port.h"
#include "ui_bridge.h"

static const char *TAG = "ui_view_test";

static lv_obj_t *s_lbl_gw = NULL;
static lv_obj_t *s_cont_nodos = NULL;
static lv_obj_t *s_lbl_cmd_result = NULL;

static void on_btn_click(lv_event_t *e)
{
    uint8_t mac[6];
    if (mesh_hojas_get_ultima(mac)) {
        esp_err_t err = ui_bridge_conmutar_actuador(mac, "led");
        if (err == ESP_OK) {
            lv_label_set_text(s_lbl_cmd_result, "Orden conmutar LED enviada!");
        } else {
            lv_label_set_text_fmt(s_lbl_cmd_result, "Fallo al enviar orden (%d)", (int)err);
        }
    } else {
        lv_label_set_text(s_lbl_cmd_result, "Sin hojas registradas en el aula");
    }
}

static void on_bridge_notif(ui_evento_tipo_t evento, const void *datos, void *user_data)
{
    if (ui_port_lock(100)) {
        ui_view_test_actualizar();
        ui_port_unlock();
    }
}

void ui_view_test_actualizar(void)
{
    ui_estado_aula_t snap;
    if (ui_bridge_get_snapshot(&snap) != ESP_OK) {
        return;
    }

    if (s_lbl_gw) {
        if (snap.red.gateway_conectado) {
            lv_label_set_text_fmt(s_lbl_gw, "GATEWAY OK | CH %d | %s", snap.red.canal, snap.red.aula);
            lv_obj_set_style_text_color(s_lbl_gw, lv_color_hex(0x22C55E), 0);
        } else {
            lv_label_set_text_fmt(s_lbl_gw, "MODO ISLA | CH %d | %s", snap.red.canal, snap.red.aula);
            lv_obj_set_style_text_color(s_lbl_gw, lv_color_hex(0xF59E0B), 0);
        }
    }

    if (s_cont_nodos) {
        lv_obj_clean(s_cont_nodos);

        if (snap.cant_nodos == 0) {
            lv_obj_t *lbl_vacio = lv_label_create(s_cont_nodos);
            lv_label_set_text(lbl_vacio, "Esperando hojas en el aula...\n(Las tarjetas apareceran automaticamente)");
            lv_obj_set_style_text_color(lbl_vacio, lv_color_hex(0x94A3B8), 0);
            lv_obj_set_style_text_align(lbl_vacio, LV_TEXT_ALIGN_CENTER, 0);
            lv_obj_set_style_pad_top(lbl_vacio, 30, 0);
        } else {
            for (int i = 0; i < snap.cant_nodos; i++) {
                ui_nodo_t *n = &snap.nodos[i];

                lv_obj_t *card = lv_obj_create(s_cont_nodos);
                lv_obj_set_width(card, lv_pct(100));
                lv_obj_set_height(card, LV_SIZE_CONTENT);
                lv_obj_set_style_bg_color(card, lv_color_hex(0x272B34), 0);
                lv_obj_set_style_border_color(card, n->conectado ? lv_color_hex(0x3B82F6) : lv_color_hex(0x64748B), 0);
                lv_obj_set_style_border_width(card, 1, 0);
                lv_obj_set_style_radius(card, 8, 0);
                lv_obj_set_style_pad_all(card, 10, 0);
                lv_obj_set_flex_flow(card, LV_FLEX_FLOW_COLUMN);

                lv_obj_t *row_header = lv_obj_create(card);
                lv_obj_set_width(row_header, lv_pct(100));
                lv_obj_set_height(row_header, LV_SIZE_CONTENT);
                lv_obj_set_style_bg_opa(row_header, LV_OPA_TRANSP, 0);
                lv_obj_set_style_border_width(row_header, 0, 0);
                lv_obj_set_style_pad_all(row_header, 0, 0);
                lv_obj_set_flex_flow(row_header, LV_FLEX_FLOW_ROW);
                lv_obj_set_flex_align(row_header, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

                lv_obj_t *lbl_hw = lv_label_create(row_header);
                lv_label_set_text(lbl_hw, n->hw_id);
                lv_obj_set_style_text_color(lbl_hw, lv_color_hex(0xFFFFFF), 0);

                lv_obj_t *lbl_st = lv_label_create(row_header);
                lv_label_set_text(lbl_st, n->conectado ? "CONECTADO" : "AUSENTE");
                lv_obj_set_style_text_color(lbl_st, n->conectado ? lv_color_hex(0x22C55E) : lv_color_hex(0xEF4444), 0);

                lv_obj_t *lbl_tele = lv_label_create(card);
                if (n->tiene_telemetria) {
                    lv_label_set_text_fmt(lbl_tele, "Temp: %.1f C   Hum: %.1f %%\nCO2: %.0f ppm",
                                          n->temp, n->hum, n->co2);
                } else {
                    lv_label_set_text(lbl_tele, "Registrada (esperando mediciones)");
                }
                lv_obj_set_style_text_color(lbl_tele, lv_color_hex(0xCBD5E1), 0);
            }
        }
    }
}

esp_err_t ui_view_test_create(void)
{
    if (!ui_port_lock(100)) {
        return ESP_ERR_TIMEOUT;
    }

    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x121418), 0);

    // Barra superior (Header)
    lv_obj_t *header = lv_obj_create(scr);
    lv_obj_set_size(header, 480, 75);
    lv_obj_set_pos(header, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0x1E222A), 0);
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

    // Area central con tarjetas de telemetria
    s_cont_nodos = lv_obj_create(scr);
    lv_obj_set_size(s_cont_nodos, 460, 560);
    lv_obj_set_pos(s_cont_nodos, 10, 85);
    lv_obj_set_style_bg_opa(s_cont_nodos, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(s_cont_nodos, 0, 0);
    lv_obj_set_style_pad_all(s_cont_nodos, 5, 0);
    lv_obj_set_flex_flow(s_cont_nodos, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(s_cont_nodos, LV_DIR_VER);

    // Panel de control inferior (Boton de actuacion)
    lv_obj_t *panel_cmd = lv_obj_create(scr);
    lv_obj_set_size(panel_cmd, 460, 135);
    lv_obj_set_pos(panel_cmd, 10, 655);
    lv_obj_set_style_bg_color(panel_cmd, lv_color_hex(0x1E222A), 0);
    lv_obj_set_style_border_width(panel_cmd, 0, 0);
    lv_obj_set_style_radius(panel_cmd, 10, 0);
    lv_obj_set_style_pad_all(panel_cmd, 10, 0);
    lv_obj_set_flex_flow(panel_cmd, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(panel_cmd, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *btn_cmd = lv_button_create(panel_cmd);
    lv_obj_set_size(btn_cmd, 400, 55);
    lv_obj_set_style_bg_color(btn_cmd, lv_color_hex(0x2563EB), 0);
    lv_obj_set_style_bg_color(btn_cmd, lv_color_hex(0x1D4ED8), LV_STATE_PRESSED);
    lv_obj_set_style_radius(btn_cmd, 8, 0);
    lv_obj_add_event_cb(btn_cmd, on_btn_click, LV_EVENT_CLICKED, NULL);

    lv_obj_t *lbl_btn = lv_label_create(btn_cmd);
    lv_label_set_text(lbl_btn, "CONMUTAR LED HOJA");
    lv_obj_set_style_text_color(lbl_btn, lv_color_hex(0xFFFFFF), 0);
    lv_obj_center(lbl_btn);

    s_lbl_cmd_result = lv_label_create(panel_cmd);
    lv_label_set_text(s_lbl_cmd_result, "Toque el boton para enviar orden por MESH");
    lv_obj_set_style_text_color(s_lbl_cmd_result, lv_color_hex(0x94A3B8), 0);
    lv_obj_set_style_pad_top(s_lbl_cmd_result, 8, 0);

    ui_bridge_registrar_observador(on_bridge_notif, NULL);

    ui_view_test_actualizar();

    ui_port_unlock();

    ESP_LOGI(TAG, "Vista de validacion interactiva creada exitosamente");
    return ESP_OK;
}
