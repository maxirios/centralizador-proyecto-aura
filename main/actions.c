#include "actions.h"
#include "ui.h"
#include "screens.h"
#include "vars.h"
#include "esp_log.h"
#include "ui_bridge.h"

static const char *TAG = "ui_actions";

void action_nav_dashboard(lv_event_t *e)
{
    ESP_LOGI(TAG, "Navegar a Dashboard");
    loadScreen(SCREEN_ID_DASHBOARD);
}

void action_nav_devices(lv_event_t *e)
{
    ESP_LOGI(TAG, "Navegar a Dispositivos");
    loadScreen(SCREEN_ID_DEVICES);
}

void action_nav_config(lv_event_t *e)
{
    ESP_LOGI(TAG, "Navegar a Config");
    loadScreen(SCREEN_ID_CONFIG);
}

void action_nav_about(lv_event_t *e)
{
    ESP_LOGI(TAG, "Navegar a Acerca de");
    loadScreen(SCREEN_ID_ABOUT);
}

void action_toggle_theme(lv_event_t *e)
{
    uint32_t next = (active_theme_index == THEME_ID_DEFAULT) ? THEME_ID_DARK : THEME_ID_DEFAULT;
    ESP_LOGI(TAG, "Conmutar tema a: %s", (next == THEME_ID_DARK) ? "Oscuro" : "Claro");
    change_color_theme(next);
    set_var_dark_theme(next == THEME_ID_DARK);
}

void action_set_theme_light(lv_event_t *e)
{
    ESP_LOGI(TAG, "Fijar tema Claro");
    change_color_theme(THEME_ID_DEFAULT);
    set_var_dark_theme(false);
}

void action_set_theme_dark(lv_event_t *e)
{
    ESP_LOGI(TAG, "Fijar tema Oscuro");
    change_color_theme(THEME_ID_DARK);
    set_var_dark_theme(true);
}

void action_toggle_actuator1(lv_event_t *e)
{
    bool st = !get_var_act_vent_on();
    set_var_act_vent_on(st);
    ESP_LOGI(TAG, "Actuador 1 (Ventilacion) conmutado a: %s", st ? "ON" : "OFF");
    if (objects.dash_act1_btn_lbl) {
        lv_label_set_text(objects.dash_act1_btn_lbl, st ? "ON" : "OFF");
    }
}

void action_toggle_actuator2(lv_event_t *e)
{
    bool st = !get_var_act_lights_on();
    set_var_act_lights_on(st);
    ESP_LOGI(TAG, "Actuador 2 (Luces) conmutado a: %s", st ? "ON" : "OFF");
    if (objects.dash_act2_btn_lbl) {
        lv_label_set_text(objects.dash_act2_btn_lbl, st ? "ON" : "OFF");
    }
}

void action_toggle_actuator3(lv_event_t *e)
{
    bool st = !get_var_act_led_on();
    set_var_act_led_on(st);
    ESP_LOGI(TAG, "Actuador 3 (LED) conmutado a: %s", st ? "ON" : "OFF");
    if (objects.dash_act3_btn_lbl) {
        lv_label_set_text(objects.dash_act3_btn_lbl, st ? "ON" : "OFF");
    }
}

void action_filter_all(lv_event_t *e)
{
    ESP_LOGI(TAG, "Filtro Dispositivos: Todos");
}

void action_filter_sensors(lv_event_t *e)
{
    ESP_LOGI(TAG, "Filtro Dispositivos: Sensores");
}

void action_filter_actuators(lv_event_t *e)
{
    ESP_LOGI(TAG, "Filtro Dispositivos: Actuadores");
}

void action_save_config(lv_event_t *e)
{
    ESP_LOGI(TAG, "Configuracion guardada");
}
