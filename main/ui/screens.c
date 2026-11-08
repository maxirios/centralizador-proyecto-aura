#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_dashboard() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.dashboard = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 800);
    add_style_screen_root(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // dashboard_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dashboard_header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 62);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 5);
        }
        {
            // dash_sec_env_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dash_sec_env_title = obj;
            lv_obj_set_pos(obj, 16, 74);
            lv_obj_set_size(obj, 280, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "RESUMEN AMBIENTAL DE AULA");
        }
        {
            // dash_sec_env_live
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dash_sec_env_live = obj;
            lv_obj_set_pos(obj, 340, 74);
            lv_obj_set_size(obj, 124, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_live_tag(obj);
            lv_label_set_text_static(obj, "En tiempo real");
        }
        {
            // dash_card_temp
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_card_temp = obj;
            lv_obj_set_pos(obj, 16, 96);
            lv_obj_set_size(obj, 218, 108);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_card_temp_accent
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_card_temp_accent = obj;
                    lv_obj_set_pos(obj, 0, 2);
                    lv_obj_set_size(obj, 5, 102);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_accent_blue(obj);
                }
                {
                    // dash_lbl_temp_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_temp_title = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 188, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "TEMPERATURA (E1-AZ)");
                }
                {
                    // dash_lbl_temp_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_temp_val = obj;
                    lv_obj_set_pos(obj, 16, 36);
                    lv_obj_set_size(obj, 188, 34);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_kpi_value_blue(obj);
                    lv_label_set_text_static(obj, "23.8 °C");
                }
                {
                    // dash_lbl_temp_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_temp_sub = obj;
                    lv_obj_set_pos(obj, 16, 78);
                    lv_obj_set_size(obj, 188, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Nodo Pizarra activo");
                }
            }
        }
        {
            // dash_card_hum
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_card_hum = obj;
            lv_obj_set_pos(obj, 246, 96);
            lv_obj_set_size(obj, 218, 108);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_card_hum_accent
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_card_hum_accent = obj;
                    lv_obj_set_pos(obj, 0, 2);
                    lv_obj_set_size(obj, 5, 102);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_accent_teal(obj);
                }
                {
                    // dash_lbl_hum_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_hum_title = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 188, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "HUMEDAD (E1-AZ)");
                }
                {
                    // dash_lbl_hum_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_hum_val = obj;
                    lv_obj_set_pos(obj, 16, 36);
                    lv_obj_set_size(obj, 188, 34);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_kpi_value_teal(obj);
                    lv_label_set_text_static(obj, "51 %");
                }
                {
                    // dash_lbl_hum_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_hum_sub = obj;
                    lv_obj_set_pos(obj, 16, 78);
                    lv_obj_set_size(obj, 188, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Rango confortable");
                }
            }
        }
        {
            // dash_card_co2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_card_co2 = obj;
            lv_obj_set_pos(obj, 16, 214);
            lv_obj_set_size(obj, 448, 114);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_card_co2_accent
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_card_co2_accent = obj;
                    lv_obj_set_pos(obj, 0, 2);
                    lv_obj_set_size(obj, 5, 108);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_accent_orange(obj);
                }
                {
                    // dash_lbl_co2_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_co2_title = obj;
                    lv_obj_set_pos(obj, 18, 12);
                    lv_obj_set_size(obj, 260, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "CALIDAD DE AIRE CO2 (E1-AZ)");
                }
                {
                    // dash_badge_co2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_badge_co2 = obj;
                    lv_obj_set_pos(obj, 344, 10);
                    lv_obj_set_size(obj, 88, 22);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_lbl_co2_status
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_lbl_co2_status = obj;
                            lv_obj_set_pos(obj, 4, 3);
                            lv_obj_set_size(obj, 80, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "NORMAL");
                        }
                    }
                }
                {
                    // dash_lbl_co2_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_co2_val = obj;
                    lv_obj_set_pos(obj, 18, 36);
                    lv_obj_set_size(obj, 220, 34);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_kpi_value_orange(obj);
                    lv_label_set_text_static(obj, "640 ppm");
                }
                {
                    // dash_bar_co2
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_bar_co2 = obj;
                    lv_obj_set_pos(obj, 18, 76);
                    lv_obj_set_size(obj, 414, 8);
                    lv_bar_set_range(obj, 400, 2000);
                    lv_bar_set_value(obj, 640, LV_ANIM_OFF);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_co2(obj);
                }
                {
                    // dash_lbl_co2_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_lbl_co2_sub = obj;
                    lv_obj_set_pos(obj, 18, 90);
                    lv_obj_set_size(obj, 414, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Umbral de ventilacion: 1000 ppm");
                }
            }
        }
        {
            // dash_sec_act_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dash_sec_act_title = obj;
            lv_obj_set_pos(obj, 16, 342);
            lv_obj_set_size(obj, 300, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "ACTUADORES RAPIDOS DEL AULA");
        }
        {
            // dash_act_row_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_act_row_1 = obj;
            lv_obj_set_pos(obj, 16, 366);
            lv_obj_set_size(obj, 448, 72);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_act1_name
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_act1_name = obj;
                    lv_obj_set_pos(obj, 16, 14);
                    lv_obj_set_size(obj, 310, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "Ventilacion de Aula");
                }
                {
                    // dash_act1_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_act1_meta = obj;
                    lv_obj_set_pos(obj, 16, 40);
                    lv_obj_set_size(obj, 310, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Extraccion forzada - Nodo E1-AZ");
                }
                {
                    // dash_act1_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.dash_act1_btn = obj;
                    lv_obj_set_pos(obj, 348, 16);
                    lv_obj_set_size(obj, 84, 40);
                    lv_obj_add_event_cb(obj, action_toggle_actuator1, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle_on(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_act1_btn_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_act1_btn_lbl = obj;
                            lv_obj_set_pos(obj, 4, 11);
                            lv_obj_set_size(obj, 76, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_btn_light(obj);
                            lv_label_set_text_static(obj, "ON");
                        }
                    }
                }
            }
        }
        {
            // dash_act_row_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_act_row_2 = obj;
            lv_obj_set_pos(obj, 16, 448);
            lv_obj_set_size(obj, 448, 72);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_act2_name
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_act2_name = obj;
                    lv_obj_set_pos(obj, 16, 14);
                    lv_obj_set_size(obj, 310, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "Luces Principales");
                }
                {
                    // dash_act2_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_act2_meta = obj;
                    lv_obj_set_pos(obj, 16, 40);
                    lv_obj_set_size(obj, 310, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Rele 220V - Nodo ACT-RELE-01");
                }
                {
                    // dash_act2_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.dash_act2_btn = obj;
                    lv_obj_set_pos(obj, 348, 16);
                    lv_obj_set_size(obj, 84, 40);
                    lv_obj_add_event_cb(obj, action_toggle_actuator2, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle_off(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_act2_btn_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_act2_btn_lbl = obj;
                            lv_obj_set_pos(obj, 4, 11);
                            lv_obj_set_size(obj, 76, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_btn_muted(obj);
                            lv_label_set_text_static(obj, "OFF");
                        }
                    }
                }
            }
        }
        {
            // dash_act_row_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_act_row_3 = obj;
            lv_obj_set_pos(obj, 16, 530);
            lv_obj_set_size(obj, 448, 72);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_act3_name
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_act3_name = obj;
                    lv_obj_set_pos(obj, 16, 14);
                    lv_obj_set_size(obj, 310, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "LED Indicador de Alerta");
                }
                {
                    // dash_act3_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_act3_meta = obj;
                    lv_obj_set_pos(obj, 16, 40);
                    lv_obj_set_size(obj, 310, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Senal luminica puerta - Nodo E1-PB");
                }
                {
                    // dash_act3_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.dash_act3_btn = obj;
                    lv_obj_set_pos(obj, 348, 16);
                    lv_obj_set_size(obj, 84, 40);
                    lv_obj_add_event_cb(obj, action_toggle_actuator3, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle_on(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_act3_btn_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_act3_btn_lbl = obj;
                            lv_obj_set_pos(obj, 4, 11);
                            lv_obj_set_size(obj, 76, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_btn_light(obj);
                            lv_label_set_text_static(obj, "ON");
                        }
                    }
                }
            }
        }
        {
            // dash_net_strip
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_net_strip = obj;
            lv_obj_set_pos(obj, 16, 614);
            lv_obj_set_size(obj, 448, 110);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_net_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_title = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 280, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "ESTADO DE NODOS EN EL AULA");
                }
                {
                    // dash_net_online_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_online_lbl = obj;
                    lv_obj_set_pos(obj, 16, 38);
                    lv_obj_set_size(obj, 200, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "Conectados: 3");
                }
                {
                    // dash_net_offline_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_offline_lbl = obj;
                    lv_obj_set_pos(obj, 230, 38);
                    lv_obj_set_size(obj, 200, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "Ausentes: 1");
                }
                {
                    // dash_net_gw_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_gw_lbl = obj;
                    lv_obj_set_pos(obj, 16, 68);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Gateway Root: ENLAZADO | Canal 6 | Trama v3");
                }
            }
        }
        {
            // dashboard_bottom_nav
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dashboard_bottom_nav = obj;
            lv_obj_set_pos(obj, 0, 740);
            lv_obj_set_size(obj, 480, 60);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_nav(obj, 56);
        }
        {
            // dash_nav_active_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_nav_active_bar = obj;
            lv_obj_set_pos(obj, 22, 742);
            lv_obj_set_size(obj, 80, 3);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_nav_indicator(obj);
        }
    }
    
    tick_screen_dashboard();
}

void tick_screen_dashboard() {
    tick_user_widget_header_bar(5);
    tick_user_widget_bottom_nav(56);
}

void create_screen_devices() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.devices = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 800);
    add_style_screen_root(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // devices_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.devices_header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 62);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 68);
        }
        {
            // dev_sec_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dev_sec_title = obj;
            lv_obj_set_pos(obj, 16, 74);
            lv_obj_set_size(obj, 260, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "DISPOSITIVOS CONECTADOS");
        }
        {
            // dev_sec_total
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dev_sec_total = obj;
            lv_obj_set_pos(obj, 360, 74);
            lv_obj_set_size(obj, 104, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_live_tag(obj);
            lv_label_set_text_static(obj, "Total: 4 nodos");
        }
        {
            // dev_chip_all
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_chip_all = obj;
            lv_obj_set_pos(obj, 16, 96);
            lv_obj_set_size(obj, 110, 32);
            lv_obj_add_event_cb(obj, action_filter_all, LV_EVENT_CLICKED, (void *)0);
            add_style_btn_filter_active(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_chip_all_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_chip_all_lbl = obj;
                    lv_obj_set_pos(obj, 4, 8);
                    lv_obj_set_size(obj, 102, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_chip_light(obj);
                    lv_label_set_text_static(obj, "Todos (4)");
                }
            }
        }
        {
            // dev_chip_sens
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_chip_sens = obj;
            lv_obj_set_pos(obj, 134, 96);
            lv_obj_set_size(obj, 120, 32);
            lv_obj_add_event_cb(obj, action_filter_sensors, LV_EVENT_CLICKED, (void *)0);
            add_style_btn_filter_idle(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_chip_sens_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_chip_sens_lbl = obj;
                    lv_obj_set_pos(obj, 4, 8);
                    lv_obj_set_size(obj, 112, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_chip_muted(obj);
                    lv_label_set_text_static(obj, "Sensores (2)");
                }
            }
        }
        {
            // dev_chip_act
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_chip_act = obj;
            lv_obj_set_pos(obj, 262, 96);
            lv_obj_set_size(obj, 134, 32);
            lv_obj_add_event_cb(obj, action_filter_actuators, LV_EVENT_CLICKED, (void *)0);
            add_style_btn_filter_idle(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_chip_act_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_chip_act_lbl = obj;
                    lv_obj_set_pos(obj, 4, 8);
                    lv_obj_set_size(obj, 126, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_chip_muted(obj);
                    lv_label_set_text_static(obj, "Actuadores (2)");
                }
            }
        }
        {
            // dev_card_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_1 = obj;
            lv_obj_set_pos(obj, 16, 138);
            lv_obj_set_size(obj, 448, 136);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_c1_id
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c1_id = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 260, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "E1-AZ-TERR-TAN01");
                }
                {
                    // dev_c1_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dev_c1_badge = obj;
                    lv_obj_set_pos(obj, 324, 10);
                    lv_obj_set_size(obj, 108, 24);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dev_c1_badge_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dev_c1_badge_lbl = obj;
                            lv_obj_set_pos(obj, 6, 4);
                            lv_obj_set_size(obj, 96, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "CONECTADO");
                        }
                    }
                }
                {
                    // dev_c1_vals
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c1_vals = obj;
                    lv_obj_set_pos(obj, 16, 44);
                    lv_obj_set_size(obj, 416, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Temp: 23.8 °C   |   Hum: 51 %   |   CO2: 640 ppm");
                }
                {
                    // dev_c1_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c1_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Extraccion forzada: ON");
                }
                {
                    // dev_c1_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c1_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Ultima telemetria: hace 4s - MAC: 34:85:18:7A:51:70");
                }
            }
        }
        {
            // dev_card_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_2 = obj;
            lv_obj_set_pos(obj, 16, 284);
            lv_obj_set_size(obj, 448, 136);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_c2_id
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c2_id = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 260, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "E1-PB-LECA-HFR01");
                }
                {
                    // dev_c2_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dev_c2_badge = obj;
                    lv_obj_set_pos(obj, 324, 10);
                    lv_obj_set_size(obj, 108, 24);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dev_c2_badge_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dev_c2_badge_lbl = obj;
                            lv_obj_set_pos(obj, 6, 4);
                            lv_obj_set_size(obj, 96, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "CONECTADO");
                        }
                    }
                }
                {
                    // dev_c2_vals
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c2_vals = obj;
                    lv_obj_set_pos(obj, 16, 44);
                    lv_obj_set_size(obj, 416, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Temp: 23.4 °C   |   Hum: 53 %");
                }
                {
                    // dev_c2_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c2_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "LED Alerta Puerta: ON");
                }
                {
                    // dev_c2_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c2_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Ultima telemetria: hace 10s - MAC: 34:85:18:7A:51:71");
                }
            }
        }
        {
            // dev_card_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_3 = obj;
            lv_obj_set_pos(obj, 16, 430);
            lv_obj_set_size(obj, 448, 136);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_c3_id
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c3_id = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 260, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "ACT-RELE-AULA-01");
                }
                {
                    // dev_c3_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dev_c3_badge = obj;
                    lv_obj_set_pos(obj, 324, 10);
                    lv_obj_set_size(obj, 108, 24);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dev_c3_badge_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dev_c3_badge_lbl = obj;
                            lv_obj_set_pos(obj, 6, 4);
                            lv_obj_set_size(obj, 96, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "CONECTADO");
                        }
                    }
                }
                {
                    // dev_c3_vals
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c3_vals = obj;
                    lv_obj_set_pos(obj, 16, 44);
                    lv_obj_set_size(obj, 416, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Actuador Rele 220V: APAGADO");
                }
                {
                    // dev_c3_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c3_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Circuito de iluminacion principal");
                }
                {
                    // dev_c3_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c3_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Ultima telemetria: hace 6s - MAC: 34:85:18:7A:51:72");
                }
            }
        }
        {
            // dev_card_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_4 = obj;
            lv_obj_set_pos(obj, 16, 576);
            lv_obj_set_size(obj, 448, 136);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_c4_id
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c4_id = obj;
                    lv_obj_set_pos(obj, 16, 12);
                    lv_obj_set_size(obj, 260, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "SENS-CO2-BACKUP");
                }
                {
                    // dev_c4_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dev_c4_badge = obj;
                    lv_obj_set_pos(obj, 324, 10);
                    lv_obj_set_size(obj, 108, 24);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_offline(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dev_c4_badge_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dev_c4_badge_lbl = obj;
                            lv_obj_set_pos(obj, 6, 4);
                            lv_obj_set_size(obj, 96, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_offline(obj);
                            lv_label_set_text_static(obj, "AUSENTE");
                        }
                    }
                }
                {
                    // dev_c4_vals
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c4_vals = obj;
                    lv_obj_set_pos(obj, 16, 44);
                    lv_obj_set_size(obj, 416, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Sin enlace mesh reciente");
                }
                {
                    // dev_c4_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c4_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Medidas ausentes (NAN)");
                }
                {
                    // dev_c4_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c4_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Visto hace 18 min - MAC: 34:85:18:7A:51:73");
                }
            }
        }
        {
            // devices_bottom_nav
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.devices_bottom_nav = obj;
            lv_obj_set_pos(obj, 0, 740);
            lv_obj_set_size(obj, 480, 60);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_nav(obj, 114);
        }
        {
            // dev_nav_active_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_nav_active_bar = obj;
            lv_obj_set_pos(obj, 140, 742);
            lv_obj_set_size(obj, 80, 3);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_nav_indicator(obj);
        }
    }
    
    tick_screen_devices();
}

void tick_screen_devices() {
    tick_user_widget_header_bar(68);
    tick_user_widget_bottom_nav(114);
}

void create_screen_config() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.config = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 800);
    add_style_screen_root(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // config_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.config_header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 62);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 126);
        }
        {
            // cfg_sec_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cfg_sec_title = obj;
            lv_obj_set_pos(obj, 16, 74);
            lv_obj_set_size(obj, 300, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "AJUSTES DEL CENTRALIZADOR");
        }
        {
            // cfg_card_main
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.cfg_card_main = obj;
            lv_obj_set_pos(obj, 16, 98);
            lv_obj_set_size(obj, 448, 620);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // cfg_lbl_theme
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cfg_lbl_theme = obj;
                    lv_obj_set_pos(obj, 20, 18);
                    lv_obj_set_size(obj, 408, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "TEMA VISUAL DE PANTALLA");
                }
                {
                    // cfg_btn_theme_light
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.cfg_btn_theme_light = obj;
                    lv_obj_set_pos(obj, 20, 42);
                    lv_obj_set_size(obj, 198, 40);
                    lv_obj_add_event_cb(obj, action_set_theme_light, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle_on(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_lbl_theme_light
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_lbl_theme_light = obj;
                            lv_obj_set_pos(obj, 8, 11);
                            lv_obj_set_size(obj, 182, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_btn_light(obj);
                            lv_label_set_text_static(obj, "Modo Claro");
                        }
                    }
                }
                {
                    // cfg_btn_theme_dark
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.cfg_btn_theme_dark = obj;
                    lv_obj_set_pos(obj, 230, 42);
                    lv_obj_set_size(obj, 198, 40);
                    lv_obj_add_event_cb(obj, action_set_theme_dark, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle_off(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_lbl_theme_dark
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_lbl_theme_dark = obj;
                            lv_obj_set_pos(obj, 8, 11);
                            lv_obj_set_size(obj, 182, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_btn_muted(obj);
                            lv_label_set_text_static(obj, "Modo Oscuro");
                        }
                    }
                }
                {
                    // cfg_lbl_bright
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cfg_lbl_bright = obj;
                    lv_obj_set_pos(obj, 20, 102);
                    lv_obj_set_size(obj, 320, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "BRILLO DE PANTALLA (VELO SW)");
                }
                {
                    // cfg_lbl_bright_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cfg_lbl_bright_val = obj;
                    lv_obj_set_pos(obj, 348, 102);
                    lv_obj_set_size(obj, 80, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "85 %");
                }
                {
                    // cfg_slider_bright
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.cfg_slider_bright = obj;
                    lv_obj_set_pos(obj, 20, 130);
                    lv_obj_set_size(obj, 408, 16);
                    lv_slider_set_range(obj, 10, 100);
                    lv_slider_set_value(obj, 85, LV_ANIM_ON);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
                    add_style_slider_brightness(obj);
                }
                {
                    // cfg_lbl_aula
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cfg_lbl_aula = obj;
                    lv_obj_set_pos(obj, 20, 170);
                    lv_obj_set_size(obj, 408, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "AULA ASIGNADA (NVS / BEACON)");
                }
                {
                    // cfg_box_aula
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.cfg_box_aula = obj;
                    lv_obj_set_pos(obj, 20, 194);
                    lv_obj_set_size(obj, 408, 44);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_val_aula
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_val_aula = obj;
                            lv_obj_set_pos(obj, 14, 13);
                            lv_obj_set_size(obj, 380, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_body(obj);
                            lv_label_set_text_static(obj, "Laboratorio 1 - Electronica");
                        }
                    }
                }
                {
                    // cfg_lbl_chan
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cfg_lbl_chan = obj;
                    lv_obj_set_pos(obj, 20, 256);
                    lv_obj_set_size(obj, 408, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "CANAL DE RADIO ESP-WIFI-MESH");
                }
                {
                    // cfg_box_chan
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.cfg_box_chan = obj;
                    lv_obj_set_pos(obj, 20, 280);
                    lv_obj_set_size(obj, 408, 44);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_val_chan
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_val_chan = obj;
                            lv_obj_set_pos(obj, 14, 13);
                            lv_obj_set_size(obj, 380, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_body(obj);
                            lv_label_set_text_static(obj, "Canal 6 (2.437 GHz) - Mesh ID Activo");
                        }
                    }
                }
                {
                    // cfg_lbl_gw
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cfg_lbl_gw = obj;
                    lv_obj_set_pos(obj, 20, 342);
                    lv_obj_set_size(obj, 408, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "ENLACE CON NODO RAIZ (GATEWAY)");
                }
                {
                    // cfg_box_gw
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.cfg_box_gw = obj;
                    lv_obj_set_pos(obj, 20, 366);
                    lv_obj_set_size(obj, 408, 64);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_gw_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_gw_name = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 260, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_body(obj);
                            lv_label_set_text_static(obj, "Gateway Mesh Aula");
                        }
                        {
                            // cfg_gw_mac
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_gw_mac = obj;
                            lv_obj_set_pos(obj, 14, 36);
                            lv_obj_set_size(obj, 260, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text_static(obj, "MAC: 34:85:18:7A:00:01");
                        }
                        {
                            // cfg_gw_badge
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.cfg_gw_badge = obj;
                            lv_obj_set_pos(obj, 294, 20);
                            lv_obj_set_size(obj, 100, 24);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_badge_online(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // cfg_gw_badge_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.cfg_gw_badge_lbl = obj;
                                    lv_obj_set_pos(obj, 6, 4);
                                    lv_obj_set_size(obj, 88, 16);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_badge_online(obj);
                                    lv_label_set_text_static(obj, "ENLAZADO");
                                }
                            }
                        }
                    }
                }
                {
                    // cfg_row_island
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.cfg_row_island = obj;
                    lv_obj_set_pos(obj, 20, 448);
                    lv_obj_set_size(obj, 408, 68);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_island_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_island_title = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 280, 18);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_body(obj);
                            lv_label_set_text_static(obj, "Modo Isla Autonomo");
                        }
                        {
                            // cfg_island_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_island_sub = obj;
                            lv_obj_set_pos(obj, 14, 38);
                            lv_obj_set_size(obj, 280, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text_static(obj, "Operar localmente sin conexion a servidor");
                        }
                        {
                            // cfg_island_sw
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.cfg_island_sw = obj;
                            lv_obj_set_pos(obj, 338, 20);
                            lv_obj_set_size(obj, 54, 28);
                            add_style_switch_aura(obj);
                        }
                    }
                }
                {
                    // cfg_btn_save
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.cfg_btn_save = obj;
                    lv_obj_set_pos(obj, 20, 544);
                    lv_obj_set_size(obj, 408, 48);
                    lv_obj_add_event_cb(obj, action_save_config, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_primary_aura(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cfg_lbl_save
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cfg_lbl_save = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 380, 20);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_btn_light(obj);
                            lv_label_set_text_static(obj, "Guardar y Aplicar Cambios");
                        }
                    }
                }
            }
        }
        {
            // config_bottom_nav
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.config_bottom_nav = obj;
            lv_obj_set_pos(obj, 0, 740);
            lv_obj_set_size(obj, 480, 60);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_nav(obj, 164);
        }
        {
            // cfg_nav_active_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.cfg_nav_active_bar = obj;
            lv_obj_set_pos(obj, 258, 742);
            lv_obj_set_size(obj, 80, 3);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_nav_indicator(obj);
        }
    }
    
    tick_screen_config();
}

void tick_screen_config() {
    tick_user_widget_header_bar(126);
    tick_user_widget_bottom_nav(164);
}

void create_screen_about() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.about = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 800);
    add_style_screen_root(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // about_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 62);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 176);
        }
        {
            // about_card_hero
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_card_hero = obj;
            lv_obj_set_pos(obj, 16, 78);
            lv_obj_set_size(obj, 448, 326);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // about_logo_img
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.about_logo_img = obj;
                    lv_obj_set_pos(obj, 134, 12);
                    lv_obj_set_size(obj, 180, 180);
                    lv_image_set_src(obj, &img_logo_about_240);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // about_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_title = obj;
                    lv_obj_set_pos(obj, 24, 200);
                    lv_obj_set_size(obj, 400, 26);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_hero_title(obj);
                    lv_label_set_text_static(obj, "AURA");
                }
                {
                    // about_subtitle
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_subtitle = obj;
                    lv_obj_set_pos(obj, 24, 232);
                    lv_obj_set_size(obj, 400, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted_center(obj);
                    lv_label_set_text_static(obj, "Administracion Unificada de Recursos y Accesos");
                }
                {
                    // about_fw_pill
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.about_fw_pill = obj;
                    lv_obj_set_pos(obj, 64, 262);
                    lv_obj_set_size(obj, 320, 28);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // about_fw_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.about_fw_lbl = obj;
                            lv_obj_set_pos(obj, 10, 6);
                            lv_obj_set_size(obj, 300, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "Firmware v1.2.0 - ESP32-S3 (7\" Touch)");
                        }
                    }
                }
            }
        }
        {
            // about_card_sys
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_card_sys = obj;
            lv_obj_set_pos(obj, 16, 418);
            lv_obj_set_size(obj, 448, 178);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // about_sys_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_sys_title = obj;
                    lv_obj_set_pos(obj, 18, 14);
                    lv_obj_set_size(obj, 412, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "INFORMACION DEL SISTEMA");
                }
                {
                    // about_sys_r1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_sys_r1 = obj;
                    lv_obj_set_pos(obj, 18, 40);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Repo: github.com/maxirios/centralizador-proyecto-aura");
                }
                {
                    // about_sys_r2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_sys_r2 = obj;
                    lv_obj_set_pos(obj, 18, 68);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Protocolo: ESP-WIFI-MESH + Trama AURA v3");
                }
                {
                    // about_sys_r3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_sys_r3 = obj;
                    lv_obj_set_pos(obj, 18, 96);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Display: Waveshare 7\" Touch LCD (ST7262 + GT911)");
                }
                {
                    // about_sys_r4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_sys_r4 = obj;
                    lv_obj_set_pos(obj, 18, 124);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Orientacion: Vertical Portrait (480 x 800 px)");
                }
                {
                    // about_sys_r5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_sys_r5 = obj;
                    lv_obj_set_pos(obj, 18, 150);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Entorno: ESP-IDF + LVGL v9.5 (PSRAM Octal)");
                }
            }
        }
        {
            // about_card_team
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_card_team = obj;
            lv_obj_set_pos(obj, 16, 608);
            lv_obj_set_size(obj, 448, 114);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // about_team_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_team_title = obj;
                    lv_obj_set_pos(obj, 18, 14);
                    lv_obj_set_size(obj, 412, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "EQUIPO Y COLABORADORES");
                }
                {
                    // about_team_r1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_team_r1 = obj;
                    lv_obj_set_pos(obj, 18, 42);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "- Proyecto de Innovacion en Aulas Inteligentes (UNRaf)");
                }
                {
                    // about_team_r2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.about_team_r2 = obj;
                    lv_obj_set_pos(obj, 18, 70);
                    lv_obj_set_size(obj, 412, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "- Area de Hardware Embebido y Comunicaciones Mesh");
                }
            }
        }
        {
            // about_bottom_nav
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_bottom_nav = obj;
            lv_obj_set_pos(obj, 0, 740);
            lv_obj_set_size(obj, 480, 60);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_nav(obj, 203);
        }
        {
            // about_nav_active_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_nav_active_bar = obj;
            lv_obj_set_pos(obj, 376, 742);
            lv_obj_set_size(obj, 80, 3);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_nav_indicator(obj);
        }
    }
    
    tick_screen_about();
}

void tick_screen_about() {
    tick_user_widget_header_bar(176);
    tick_user_widget_bottom_nav(203);
}

void create_user_widget_header_bar(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // HeaderBar_root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 62);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_header(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // header_logo
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 12, 7);
                    lv_obj_set_size(obj, 48, 48);
                    lv_image_set_src(obj, &img_logo_header_48);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // header_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 68, 12);
                    lv_obj_set_size(obj, 210, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_header_title(obj);
                    lv_label_set_text_static(obj, "AURA CENTRALIZADOR");
                }
                {
                    // header_subtitle
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 68, 34);
                    lv_obj_set_size(obj, 210, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_header_sub(obj);
                    lv_label_set_text_static(obj, "Aula: Laboratorio 1");
                }
                {
                    // header_theme_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 292, 13);
                    lv_obj_set_size(obj, 54, 36);
                    lv_obj_add_event_cb(obj, action_toggle_theme, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_header_theme(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // header_theme_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 2, 10);
                            lv_obj_set_size(obj, 50, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_header_badge(obj);
                            lv_label_set_text_static(obj, "TEMA");
                        }
                    }
                }
                {
                    // header_mesh_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 354, 15);
                    lv_obj_set_size(obj, 114, 32);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_header_badge(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // header_mesh_dot
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                            lv_obj_set_pos(obj, 10, 11);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_status_dot(obj);
                        }
                        {
                            // header_mesh_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 24, 8);
                            lv_obj_set_size(obj, 84, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_header_badge(obj);
                            lv_label_set_text_static(obj, "Mesh OK (4)");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_header_bar(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_bottom_nav(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // BottomNav_root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 60);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_bottom_nav(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // nav_top_line
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 480, 1);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_divider(obj);
                }
                {
                    // nav_btn_dashboard
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 6, 6);
                    lv_obj_set_size(obj, 112, 48);
                    lv_obj_add_event_cb(obj, action_nav_dashboard, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_lbl_dashboard
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 4, 16);
                            lv_obj_set_size(obj, 104, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_nav_tab(obj);
                            lv_label_set_text_static(obj, "Dashboard");
                        }
                    }
                }
                {
                    // nav_btn_devices
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 124, 6);
                    lv_obj_set_size(obj, 112, 48);
                    lv_obj_add_event_cb(obj, action_nav_devices, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_lbl_devices
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 4, 16);
                            lv_obj_set_size(obj, 104, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_nav_tab(obj);
                            lv_label_set_text_static(obj, "Dispositivos");
                        }
                    }
                }
                {
                    // nav_btn_config
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 242, 6);
                    lv_obj_set_size(obj, 112, 48);
                    lv_obj_add_event_cb(obj, action_nav_config, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_lbl_config
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                            lv_obj_set_pos(obj, 4, 16);
                            lv_obj_set_size(obj, 104, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_nav_tab(obj);
                            lv_label_set_text_static(obj, "Config");
                        }
                    }
                }
                {
                    // nav_btn_about
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                    lv_obj_set_pos(obj, 360, 6);
                    lv_obj_set_size(obj, 112, 48);
                    lv_obj_add_event_cb(obj, action_nav_about, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_lbl_about
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 4, 16);
                            lv_obj_set_size(obj, 104, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_nav_tab(obj);
                            lv_label_set_text_static(obj, "Acerca de");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_bottom_nav(int startWidgetIndex) {
    (void)startWidgetIndex;
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_dashboard,
    tick_screen_devices,
    tick_screen_config,
    tick_screen_about,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 4) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;
void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    lv_style_set_bg_color(get_style_screen_root_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][8]));
    lv_style_set_text_color(get_style_screen_root_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_bg_color(get_style_panel_header_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    lv_style_set_bg_color(get_style_panel_header_badge_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    lv_style_set_border_color(get_style_panel_header_badge_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_panel_status_dot_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    lv_style_set_bg_color(get_style_panel_bottom_nav_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    lv_style_set_bg_color(get_style_panel_divider_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    lv_style_set_bg_color(get_style_panel_nav_indicator_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    lv_style_set_bg_color(get_style_panel_card_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    lv_style_set_border_color(get_style_panel_card_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    lv_style_set_bg_color(get_style_panel_input_box_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    lv_style_set_border_color(get_style_panel_input_box_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_panel_accent_blue_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    lv_style_set_bg_color(get_style_panel_accent_teal_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_panel_accent_orange_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_bg_color(get_style_panel_badge_online_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    lv_style_set_border_color(get_style_panel_badge_online_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_panel_badge_offline_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    lv_style_set_border_color(get_style_panel_badge_offline_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][6]));
    lv_style_set_bg_color(get_style_btn_header_theme_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    lv_style_set_border_color(get_style_btn_header_theme_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_text_color(get_style_btn_header_theme_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_nav_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    lv_style_set_text_color(get_style_btn_nav_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_bg_color(get_style_btn_toggle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_btn_toggle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_toggle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    lv_style_set_border_color(get_style_btn_toggle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_text_color(get_style_btn_toggle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_bg_color(get_style_btn_primary_aura_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    lv_style_set_text_color(get_style_btn_primary_aura_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_filter_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    lv_style_set_text_color(get_style_btn_filter_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_filter_idle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    lv_style_set_border_color(get_style_btn_filter_idle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    lv_style_set_text_color(get_style_btn_filter_idle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_header_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_header_sub_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_text_color(get_style_label_header_badge_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_nav_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_label_section_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_live_tag_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_label_kpi_value_blue_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_label_kpi_value_teal_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_label_kpi_value_orange_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_text_color(get_style_label_card_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_label_hero_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_label_body_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_label_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_muted_center_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_badge_online_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_label_badge_offline_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][6]));
    lv_style_set_text_color(get_style_label_btn_light_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_btn_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_chip_light_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_chip_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_bg_color(get_style_bar_co2_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    lv_style_set_bg_color(get_style_bar_co2_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_slider_brightness_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_slider_brightness_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    lv_style_set_bg_color(get_style_slider_brightness_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_bg_color(get_style_switch_aura_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_switch_aura_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_switch_aura_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_obj_invalidate(objects.dashboard);
    lv_obj_invalidate(objects.devices);
    lv_obj_invalidate(objects.config);
    lv_obj_invalidate(objects.about);
}
uint32_t theme_colors[2][21] = {
    { 0xff004069, 0xff0d588a, 0xfffe9304, 0xff00b2ad, 0xff494949, 0xff22c55e, 0xffef4444, 0xffffffff, 0xfff4f6f9, 0xffffffff, 0xff004069, 0xffffffff, 0xfff8fafc, 0xffe0f7f6, 0xfffee2e2, 0xff0d588a, 0xffe2e8f0, 0xffcbd5e1, 0xff1e293b, 0xff64748b, 0xffcbd5e1 },
    { 0xff004069, 0xff38bdf8, 0xfffe9304, 0xff00b2ad, 0xff64748b, 0xff22c55e, 0xffef4444, 0xffffffff, 0xff0f172a, 0xff1e293b, 0xff0b1e2d, 0xff1e293b, 0xff0f172a, 0xff0d3b3e, 0xff3b181e, 0xff1e293b, 0xff334155, 0xff475569, 0xfff8fafc, 0xff94a3b8, 0xff94a3b8 },
};

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_dashboard();
    create_screen_devices();
    create_screen_config();
    create_screen_about();
}