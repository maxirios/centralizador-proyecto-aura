#include "actions.h"
#include "ui.h"
#include "screens.h"
#include "styles.h"
#include "vars.h"
#include "esp_log.h"
#include "ui_bridge.h"
#include "relay_ctrl.h"

static const char *TAG = "ui_actions";
static bool s_dash_subtab_sensors = false;

extern void ui_ticker_step(int delta);

static void sync_theme_buttons(bool dark)
{
    if (objects.cfg_btn_theme_light && objects.cfg_btn_theme_dark) {
        if (dark) {
            remove_style_btn_toggle_on(objects.cfg_btn_theme_light);
            add_style_btn_toggle_off(objects.cfg_btn_theme_light);
            remove_style_label_btn_light(objects.cfg_lbl_theme_light);
            add_style_label_btn_muted(objects.cfg_lbl_theme_light);

            remove_style_btn_toggle_off(objects.cfg_btn_theme_dark);
            add_style_btn_toggle_on(objects.cfg_btn_theme_dark);
            remove_style_label_btn_muted(objects.cfg_lbl_theme_dark);
            add_style_label_btn_light(objects.cfg_lbl_theme_dark);
        } else {
            remove_style_btn_toggle_off(objects.cfg_btn_theme_light);
            add_style_btn_toggle_on(objects.cfg_btn_theme_light);
            remove_style_label_btn_muted(objects.cfg_lbl_theme_light);
            add_style_label_btn_light(objects.cfg_lbl_theme_light);

            remove_style_btn_toggle_on(objects.cfg_btn_theme_dark);
            add_style_btn_toggle_off(objects.cfg_btn_theme_dark);
            remove_style_label_btn_light(objects.cfg_lbl_theme_dark);
            add_style_label_btn_muted(objects.cfg_lbl_theme_dark);
        }
    }
}

static void sync_local_relay_btn(lv_obj_t *btn, bool on)
{
    if (!btn) return;
    if (on) {
        remove_style_btn_relay_squircle_off(btn);
        add_style_btn_relay_squircle_on(btn);
    } else {
        remove_style_btn_relay_squircle_on(btn);
        add_style_btn_relay_squircle_off(btn);
    }
    lv_obj_invalidate(btn);
}

void action_nav_dashboard(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Navegar a Tablero");
    loadScreen(s_dash_subtab_sensors ? SCREEN_ID_DASHBOARD_SENSORS : SCREEN_ID_DASHBOARD_ACTUATORS);
}

void action_nav_devices(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Navegar a Dispositivos");
    loadScreen(SCREEN_ID_DEVICES);
}

void action_nav_config(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Navegar a Configuracion");
    loadScreen(SCREEN_ID_CONFIG);
}

void action_nav_about(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Navegar a Acerca de");
    loadScreen(SCREEN_ID_ABOUT);
}

void action_set_theme_light(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Fijar tema Claro");
    change_color_theme(THEME_ID_DEFAULT);
    set_var_dark_theme(false);
    sync_theme_buttons(false);
}

void action_set_theme_dark(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Fijar tema Oscuro");
    change_color_theme(THEME_ID_DARK);
    set_var_dark_theme(true);
    sync_theme_buttons(true);
}

void action_ticker_prev(lv_event_t *e)
{
    (void)e;
    ui_ticker_step(-1);
}

void action_ticker_next(lv_event_t *e)
{
    (void)e;
    ui_ticker_step(1);
}

void action_dash_tab_actuators(lv_event_t *e)
{
    (void)e;
    s_dash_subtab_sensors = false;
    ESP_LOGI(TAG, "Tablero -> Actuadores");
    loadScreen(SCREEN_ID_DASHBOARD_ACTUATORS);
}

void action_dash_tab_sensors(lv_event_t *e)
{
    (void)e;
    s_dash_subtab_sensors = true;
    ESP_LOGI(TAG, "Tablero -> Sensores");
    loadScreen(SCREEN_ID_DASHBOARD_SENSORS);
}

void action_toggle_local_relay1(lv_event_t *e)
{
    (void)e;
    bool st = relay_ctrl_toggle(0);
    sync_local_relay_btn(objects.dash_relay_btn_1, st);
}

void action_toggle_local_relay2(lv_event_t *e)
{
    (void)e;
    bool st = relay_ctrl_toggle(1);
    sync_local_relay_btn(objects.dash_relay_btn_2, st);
}

void action_toggle_local_relay3(lv_event_t *e)
{
    (void)e;
    bool st = relay_ctrl_toggle(2);
    sync_local_relay_btn(objects.dash_relay_btn_3, st);
}

void action_toggle_local_relay4(lv_event_t *e)
{
    (void)e;
    bool st = relay_ctrl_toggle(3);
    sync_local_relay_btn(objects.dash_relay_btn_4, st);
}

void action_toggle_local_relay5(lv_event_t *e)
{
    (void)e;
    bool st = relay_ctrl_toggle(4);
    sync_local_relay_btn(objects.dash_relay_btn_5, st);
}

static void toggle_remote_node_actuator(uint8_t node_idx, lv_obj_t *sub_lbl)
{
    static ui_estado_aula_t snap;
    if (ui_bridge_get_snapshot(&snap) != ESP_OK) return;
    if (node_idx >= snap.cant_nodos) {
        ESP_LOGW(TAG, "No hay nodo hoja en indice %u para conmutar actuador", (unsigned)node_idx);
        return;
    }
    const ui_nodo_t *n = &snap.nodos[node_idx];
    const char *act_key = (n->actuador_key[0] != '\0') ? n->actuador_key : "led";
    ESP_LOGI(TAG, "Enviando orden conmutar '%s' a nodo %s", act_key, n->hw_id);
    if (sub_lbl) {
        lv_label_set_text(sub_lbl, "Estado: ENVIANDO...");
    }
    ui_bridge_conmutar_actuador(n->mac, act_key);
}

void action_toggle_node1_actuator(lv_event_t *e)
{
    (void)e;
    toggle_remote_node_actuator(0, objects.dash_n1_act_sub);
}

void action_toggle_node2_actuator(lv_event_t *e)
{
    (void)e;
    toggle_remote_node_actuator(1, objects.dash_n2_act_sub);
}
