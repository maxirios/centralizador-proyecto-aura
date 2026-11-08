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
            lv_obj_set_size(obj, 480, 56);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 5);
        }
        {
            // dash_ticker_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_ticker_bar = obj;
            lv_obj_set_pos(obj, 0, 56);
            lv_obj_set_size(obj, 480, 34);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_ticker_bar(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_ticker_tag
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_ticker_tag = obj;
                    lv_obj_set_pos(obj, 8, 6);
                    lv_obj_set_size(obj, 82, 22);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_ticker_tag_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ticker_tag_lbl = obj;
                            lv_obj_set_pos(obj, 4, 3);
                            lv_obj_set_size(obj, 74, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "TICKER");
                        }
                    }
                }
                {
                    // dash_ticker_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_ticker_lbl = obj;
                    lv_obj_set_pos(obj, 98, 8);
                    lv_obj_set_size(obj, 370, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Sin lecturas en malla");
                }
            }
        }
        {
            // dash_relays_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_relays_card = obj;
            lv_obj_set_pos(obj, 12, 98);
            lv_obj_set_size(obj, 456, 126);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_relays_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_relays_title = obj;
                    lv_obj_set_pos(obj, 14, 8);
                    lv_obj_set_size(obj, 300, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "INTERRUPTORES DEL CENTRALIZADOR");
                }
                {
                    // dash_relays_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_relays_sub = obj;
                    lv_obj_set_pos(obj, 320, 8);
                    lv_obj_set_size(obj, 122, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "5 Canales");
                }
                {
                    // dash_relay_tile_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_relay_tile_1 = obj;
                    lv_obj_set_pos(obj, 14, 30);
                    lv_obj_set_size(obj, 82, 88);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_relay_tile(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_relay_num_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_num_1 = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 74, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_relay_num(obj);
                            lv_label_set_text_static(obj, "1");
                        }
                        {
                            // dash_relay_btn_1
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_relay_btn_1 = obj;
                            lv_obj_set_pos(obj, 19, 22);
                            lv_obj_set_size(obj, 44, 44);
                            lv_obj_add_event_cb(obj, action_toggle_local_relay1, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_on(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_relay_ico_1
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_relay_ico_1 = obj;
                                    lv_obj_set_pos(obj, 12, 12);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                        {
                            // dash_relay_lbl_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_lbl_1 = obj;
                            lv_obj_set_pos(obj, 2, 68);
                            lv_obj_set_size(obj, 78, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted_center(obj);
                            lv_label_set_text_static(obj, "");
                        }
                    }
                }
                {
                    // dash_relay_tile_2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_relay_tile_2 = obj;
                    lv_obj_set_pos(obj, 100, 30);
                    lv_obj_set_size(obj, 82, 88);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_relay_tile(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_relay_num_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_num_2 = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 74, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_relay_num(obj);
                            lv_label_set_text_static(obj, "2");
                        }
                        {
                            // dash_relay_btn_2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_relay_btn_2 = obj;
                            lv_obj_set_pos(obj, 19, 22);
                            lv_obj_set_size(obj, 44, 44);
                            lv_obj_add_event_cb(obj, action_toggle_local_relay2, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_off(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_relay_ico_2
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_relay_ico_2 = obj;
                                    lv_obj_set_pos(obj, 12, 12);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                        {
                            // dash_relay_lbl_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_lbl_2 = obj;
                            lv_obj_set_pos(obj, 2, 68);
                            lv_obj_set_size(obj, 78, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted_center(obj);
                            lv_label_set_text_static(obj, "");
                        }
                    }
                }
                {
                    // dash_relay_tile_3
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_relay_tile_3 = obj;
                    lv_obj_set_pos(obj, 186, 30);
                    lv_obj_set_size(obj, 82, 88);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_relay_tile(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_relay_num_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_num_3 = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 74, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_relay_num(obj);
                            lv_label_set_text_static(obj, "3");
                        }
                        {
                            // dash_relay_btn_3
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_relay_btn_3 = obj;
                            lv_obj_set_pos(obj, 19, 22);
                            lv_obj_set_size(obj, 44, 44);
                            lv_obj_add_event_cb(obj, action_toggle_local_relay3, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_off(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_relay_ico_3
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_relay_ico_3 = obj;
                                    lv_obj_set_pos(obj, 12, 12);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                        {
                            // dash_relay_lbl_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_lbl_3 = obj;
                            lv_obj_set_pos(obj, 2, 68);
                            lv_obj_set_size(obj, 78, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted_center(obj);
                            lv_label_set_text_static(obj, "");
                        }
                    }
                }
                {
                    // dash_relay_tile_4
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_relay_tile_4 = obj;
                    lv_obj_set_pos(obj, 272, 30);
                    lv_obj_set_size(obj, 82, 88);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_relay_tile(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_relay_num_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_num_4 = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 74, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_relay_num(obj);
                            lv_label_set_text_static(obj, "4");
                        }
                        {
                            // dash_relay_btn_4
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_relay_btn_4 = obj;
                            lv_obj_set_pos(obj, 19, 22);
                            lv_obj_set_size(obj, 44, 44);
                            lv_obj_add_event_cb(obj, action_toggle_local_relay4, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_off(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_relay_ico_4
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_relay_ico_4 = obj;
                                    lv_obj_set_pos(obj, 12, 12);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                        {
                            // dash_relay_lbl_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_lbl_4 = obj;
                            lv_obj_set_pos(obj, 2, 68);
                            lv_obj_set_size(obj, 78, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted_center(obj);
                            lv_label_set_text_static(obj, "");
                        }
                    }
                }
                {
                    // dash_relay_tile_5
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_relay_tile_5 = obj;
                    lv_obj_set_pos(obj, 358, 30);
                    lv_obj_set_size(obj, 82, 88);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_relay_tile(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_relay_num_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_num_5 = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 74, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_relay_num(obj);
                            lv_label_set_text_static(obj, "5");
                        }
                        {
                            // dash_relay_btn_5
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_relay_btn_5 = obj;
                            lv_obj_set_pos(obj, 19, 22);
                            lv_obj_set_size(obj, 44, 44);
                            lv_obj_add_event_cb(obj, action_toggle_local_relay5, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_off(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_relay_ico_5
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_relay_ico_5 = obj;
                                    lv_obj_set_pos(obj, 12, 12);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                        {
                            // dash_relay_lbl_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_relay_lbl_5 = obj;
                            lv_obj_set_pos(obj, 2, 68);
                            lv_obj_set_size(obj, 78, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted_center(obj);
                            lv_label_set_text_static(obj, "");
                        }
                    }
                }
            }
        }
        {
            // dash_nodes_sec_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dash_nodes_sec_title = obj;
            lv_obj_set_pos(obj, 16, 232);
            lv_obj_set_size(obj, 280, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "NODOS HOJA EN MALLA (TIEMPO REAL)");
        }
        {
            // dash_nodes_sec_tag
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dash_nodes_sec_tag = obj;
            lv_obj_set_pos(obj, 310, 232);
            lv_obj_set_size(obj, 154, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_live_tag(obj);
            lv_label_set_text_static(obj, "Sin promediar");
        }
        {
            // dash_empty_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_empty_card = obj;
            lv_obj_set_pos(obj, 12, 254);
            lv_obj_set_size(obj, 456, 110);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_empty_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_empty_title = obj;
                    lv_obj_set_pos(obj, 18, 28);
                    lv_obj_set_size(obj, 420, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted_center(obj);
                    lv_label_set_text_static(obj, "Esperando nodos hojas...");
                }
                {
                    // dash_empty_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_empty_sub = obj;
                    lv_obj_set_pos(obj, 18, 56);
                    lv_obj_set_size(obj, 420, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted_center(obj);
                    lv_label_set_text_static(obj, "Los contenedores apareceran al conectarse por ESP-MESH");
                }
            }
        }
        {
            // dash_node1_box
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_node1_box = obj;
            lv_obj_set_pos(obj, 12, 254);
            lv_obj_set_size(obj, 456, 190);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_unified_device(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_n1_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_title = obj;
                    lv_obj_set_pos(obj, 14, 10);
                    lv_obj_set_size(obj, 290, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "Nodo Hoja #1");
                }
                {
                    // dash_n1_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_sub = obj;
                    lv_obj_set_pos(obj, 14, 32);
                    lv_obj_set_size(obj, 290, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Esperando datos...");
                }
                {
                    // dash_n1_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n1_badge = obj;
                    lv_obj_set_pos(obj, 346, 12);
                    lv_obj_set_size(obj, 96, 24);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_n1_badge_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n1_badge_lbl = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 88, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "ONLINE");
                        }
                    }
                }
                {
                    // dash_n1_divider
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n1_divider = obj;
                    lv_obj_set_pos(obj, 14, 52);
                    lv_obj_set_size(obj, 428, 1);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_divider(obj);
                }
                {
                    // dash_n1_s1_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s1_lbl = obj;
                    lv_obj_set_pos(obj, 14, 60);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "TEMPERATURA");
                }
                {
                    // dash_n1_s1_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s1_val = obj;
                    lv_obj_set_pos(obj, 136, 60);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- °C");
                }
                {
                    // dash_n1_s1_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n1_s1_bar = obj;
                    lv_obj_set_pos(obj, 14, 80);
                    lv_obj_set_size(obj, 206, 6);
                    lv_bar_set_range(obj, 0, 50);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_teal(obj);
                }
                {
                    // dash_n1_s2_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s2_lbl = obj;
                    lv_obj_set_pos(obj, 236, 60);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "HUMEDAD");
                }
                {
                    // dash_n1_s2_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s2_val = obj;
                    lv_obj_set_pos(obj, 358, 60);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- %");
                }
                {
                    // dash_n1_s2_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n1_s2_bar = obj;
                    lv_obj_set_pos(obj, 236, 80);
                    lv_obj_set_size(obj, 206, 6);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_teal(obj);
                }
                {
                    // dash_n1_s3_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s3_lbl = obj;
                    lv_obj_set_pos(obj, 14, 96);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "LUZ VENTANA");
                }
                {
                    // dash_n1_s3_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s3_val = obj;
                    lv_obj_set_pos(obj, 136, 96);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- lx");
                }
                {
                    // dash_n1_s3_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n1_s3_bar = obj;
                    lv_obj_set_pos(obj, 14, 116);
                    lv_obj_set_size(obj, 206, 6);
                    lv_bar_set_range(obj, 0, 1000);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_blue(obj);
                }
                {
                    // dash_n1_s4_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s4_lbl = obj;
                    lv_obj_set_pos(obj, 236, 96);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "LUZ AULA");
                }
                {
                    // dash_n1_s4_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n1_s4_val = obj;
                    lv_obj_set_pos(obj, 358, 96);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- lx");
                }
                {
                    // dash_n1_s4_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n1_s4_bar = obj;
                    lv_obj_set_pos(obj, 236, 116);
                    lv_obj_set_size(obj, 206, 6);
                    lv_bar_set_range(obj, 0, 1000);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_blue(obj);
                }
                {
                    // dash_n1_pres_box
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n1_pres_box = obj;
                    lv_obj_set_pos(obj, 14, 134);
                    lv_obj_set_size(obj, 206, 42);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_n1_pres_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n1_pres_title = obj;
                            lv_obj_set_pos(obj, 10, 13);
                            lv_obj_set_size(obj, 90, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_section_title(obj);
                            lv_label_set_text_static(obj, "PRESENCIA");
                        }
                        {
                            // dash_n1_pres_badge
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.dash_n1_pres_badge = obj;
                            lv_obj_set_pos(obj, 106, 9);
                            lv_obj_set_size(obj, 90, 24);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_badge_online(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_n1_pres_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_n1_pres_lbl = obj;
                                    lv_obj_set_pos(obj, 4, 4);
                                    lv_obj_set_size(obj, 82, 16);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_badge_online(obj);
                                    lv_label_set_text_static(obj, "SIN DATO");
                                }
                            }
                        }
                    }
                }
                {
                    // dash_n1_act_box
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n1_act_box = obj;
                    lv_obj_set_pos(obj, 236, 134);
                    lv_obj_set_size(obj, 206, 42);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_n1_act_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n1_act_title = obj;
                            lv_obj_set_pos(obj, 10, 5);
                            lv_obj_set_size(obj, 136, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_section_title(obj);
                            lv_label_set_text_static(obj, "ACTUADOR HOJA");
                        }
                        {
                            // dash_n1_act_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n1_act_sub = obj;
                            lv_obj_set_pos(obj, 10, 22);
                            lv_obj_set_size(obj, 136, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text_static(obj, "Sin actuador");
                        }
                        {
                            // dash_n1_act_btn
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_n1_act_btn = obj;
                            lv_obj_set_pos(obj, 156, 3);
                            lv_obj_set_size(obj, 42, 36);
                            lv_obj_add_event_cb(obj, action_toggle_node1_actuator, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_off(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_n1_act_ico
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_n1_act_ico = obj;
                                    lv_obj_set_pos(obj, 11, 8);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // dash_node2_box
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_node2_box = obj;
            lv_obj_set_pos(obj, 12, 452);
            lv_obj_set_size(obj, 456, 190);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_unified_device(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_n2_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_title = obj;
                    lv_obj_set_pos(obj, 14, 10);
                    lv_obj_set_size(obj, 290, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_card_title(obj);
                    lv_label_set_text_static(obj, "Nodo Hoja #2");
                }
                {
                    // dash_n2_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_sub = obj;
                    lv_obj_set_pos(obj, 14, 32);
                    lv_obj_set_size(obj, 290, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Esperando datos...");
                }
                {
                    // dash_n2_badge
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n2_badge = obj;
                    lv_obj_set_pos(obj, 346, 12);
                    lv_obj_set_size(obj, 96, 24);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_badge_online(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_n2_badge_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n2_badge_lbl = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 88, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_badge_online(obj);
                            lv_label_set_text_static(obj, "ONLINE");
                        }
                    }
                }
                {
                    // dash_n2_divider
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n2_divider = obj;
                    lv_obj_set_pos(obj, 14, 52);
                    lv_obj_set_size(obj, 428, 1);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_divider(obj);
                }
                {
                    // dash_n2_s1_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s1_lbl = obj;
                    lv_obj_set_pos(obj, 14, 60);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "TEMPERATURA");
                }
                {
                    // dash_n2_s1_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s1_val = obj;
                    lv_obj_set_pos(obj, 136, 60);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- °C");
                }
                {
                    // dash_n2_s1_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n2_s1_bar = obj;
                    lv_obj_set_pos(obj, 14, 80);
                    lv_obj_set_size(obj, 206, 6);
                    lv_bar_set_range(obj, 0, 50);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_teal(obj);
                }
                {
                    // dash_n2_s2_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s2_lbl = obj;
                    lv_obj_set_pos(obj, 236, 60);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "HUMEDAD");
                }
                {
                    // dash_n2_s2_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s2_val = obj;
                    lv_obj_set_pos(obj, 358, 60);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- %");
                }
                {
                    // dash_n2_s2_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n2_s2_bar = obj;
                    lv_obj_set_pos(obj, 236, 80);
                    lv_obj_set_size(obj, 206, 6);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_teal(obj);
                }
                {
                    // dash_n2_s3_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s3_lbl = obj;
                    lv_obj_set_pos(obj, 14, 96);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "LUZ VENTANA");
                }
                {
                    // dash_n2_s3_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s3_val = obj;
                    lv_obj_set_pos(obj, 136, 96);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- lx");
                }
                {
                    // dash_n2_s3_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n2_s3_bar = obj;
                    lv_obj_set_pos(obj, 14, 116);
                    lv_obj_set_size(obj, 206, 6);
                    lv_bar_set_range(obj, 0, 1000);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_blue(obj);
                }
                {
                    // dash_n2_s4_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s4_lbl = obj;
                    lv_obj_set_pos(obj, 236, 96);
                    lv_obj_set_size(obj, 120, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "LUZ AULA");
                }
                {
                    // dash_n2_s4_val
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_n2_s4_val = obj;
                    lv_obj_set_pos(obj, 358, 96);
                    lv_obj_set_size(obj, 84, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_live_tag(obj);
                    lv_label_set_text_static(obj, "-- lx");
                }
                {
                    // dash_n2_s4_bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.dash_n2_s4_bar = obj;
                    lv_obj_set_pos(obj, 236, 116);
                    lv_obj_set_size(obj, 206, 6);
                    lv_bar_set_range(obj, 0, 1000);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_bar_sensor_blue(obj);
                }
                {
                    // dash_n2_pres_box
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n2_pres_box = obj;
                    lv_obj_set_pos(obj, 14, 134);
                    lv_obj_set_size(obj, 206, 42);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_n2_pres_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n2_pres_title = obj;
                            lv_obj_set_pos(obj, 10, 13);
                            lv_obj_set_size(obj, 90, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_section_title(obj);
                            lv_label_set_text_static(obj, "PRESENCIA");
                        }
                        {
                            // dash_n2_pres_badge
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.dash_n2_pres_badge = obj;
                            lv_obj_set_pos(obj, 106, 9);
                            lv_obj_set_size(obj, 90, 24);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_badge_online(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_n2_pres_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_n2_pres_lbl = obj;
                                    lv_obj_set_pos(obj, 4, 4);
                                    lv_obj_set_size(obj, 82, 16);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_badge_online(obj);
                                    lv_label_set_text_static(obj, "SIN DATO");
                                }
                            }
                        }
                    }
                }
                {
                    // dash_n2_act_box
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_n2_act_box = obj;
                    lv_obj_set_pos(obj, 236, 134);
                    lv_obj_set_size(obj, 206, 42);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_input_box(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_n2_act_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n2_act_title = obj;
                            lv_obj_set_pos(obj, 10, 5);
                            lv_obj_set_size(obj, 136, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_section_title(obj);
                            lv_label_set_text_static(obj, "ACTUADOR HOJA");
                        }
                        {
                            // dash_n2_act_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_n2_act_sub = obj;
                            lv_obj_set_pos(obj, 10, 22);
                            lv_obj_set_size(obj, 136, 16);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text_static(obj, "Sin actuador");
                        }
                        {
                            // dash_n2_act_btn
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.dash_n2_act_btn = obj;
                            lv_obj_set_pos(obj, 156, 3);
                            lv_obj_set_size(obj, 42, 36);
                            lv_obj_add_event_cb(obj, action_toggle_node2_actuator, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_relay_squircle_off(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_n2_act_ico
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.dash_n2_act_ico = obj;
                                    lv_obj_set_pos(obj, 11, 8);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_image_set_src(obj, &img_icon_power_20);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // dash_net_strip
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_net_strip = obj;
            lv_obj_set_pos(obj, 12, 650);
            lv_obj_set_size(obj, 456, 82);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_net_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_title = obj;
                    lv_obj_set_pos(obj, 14, 8);
                    lv_obj_set_size(obj, 280, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_section_title(obj);
                    lv_label_set_text_static(obj, "ESTADO DE LA RED ESP-WIFI-MESH");
                }
                {
                    // dash_net_online_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_online_lbl = obj;
                    lv_obj_set_pos(obj, 14, 30);
                    lv_obj_set_size(obj, 200, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Hojas activas: 0");
                }
                {
                    // dash_net_offline_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_offline_lbl = obj;
                    lv_obj_set_pos(obj, 230, 30);
                    lv_obj_set_size(obj, 200, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_body(obj);
                    lv_label_set_text_static(obj, "Ausentes: 0");
                }
                {
                    // dash_net_gw_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dash_net_gw_lbl = obj;
                    lv_obj_set_pos(obj, 14, 54);
                    lv_obj_set_size(obj, 428, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Buscando Gateway... | Modo Isla");
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
            create_user_widget_bottom_nav(obj, 111);
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
    tick_user_widget_bottom_nav(111);
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
            lv_obj_set_size(obj, 480, 56);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 127);
        }
        {
            // dev_sec_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dev_sec_title = obj;
            lv_obj_set_pos(obj, 16, 68);
            lv_obj_set_size(obj, 260, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "DISPOSITIVOS CONECTADOS");
        }
        {
            // dev_sec_total
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dev_sec_total = obj;
            lv_obj_set_pos(obj, 340, 68);
            lv_obj_set_size(obj, 124, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_live_tag(obj);
            lv_label_set_text_static(obj, "Total: 0 nodos");
        }
        {
            // dev_chip_all
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_chip_all = obj;
            lv_obj_set_pos(obj, 16, 90);
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
                    lv_label_set_text_static(obj, "Todos (0)");
                }
            }
        }
        {
            // dev_chip_sens
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_chip_sens = obj;
            lv_obj_set_pos(obj, 134, 90);
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
                    lv_label_set_text_static(obj, "Sensores");
                }
            }
        }
        {
            // dev_chip_act
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_chip_act = obj;
            lv_obj_set_pos(obj, 262, 90);
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
                    lv_label_set_text_static(obj, "Actuadores");
                }
            }
        }
        {
            // dev_empty_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_empty_card = obj;
            lv_obj_set_pos(obj, 16, 134);
            lv_obj_set_size(obj, 448, 110);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dev_empty_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_empty_title = obj;
                    lv_obj_set_pos(obj, 16, 28);
                    lv_obj_set_size(obj, 416, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted_center(obj);
                    lv_label_set_text_static(obj, "Esperando nodos hojas...");
                }
                {
                    // dev_empty_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_empty_sub = obj;
                    lv_obj_set_pos(obj, 16, 56);
                    lv_obj_set_size(obj, 416, 18);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted_center(obj);
                    lv_label_set_text_static(obj, "Ningun dispositivo ha reportado telemetria aun");
                }
            }
        }
        {
            // dev_card_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_1 = obj;
            lv_obj_set_pos(obj, 16, 134);
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
                    lv_label_set_text_static(obj, "Nodo #1");
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
                    lv_label_set_text_static(obj, "Esperando mediciones...");
                }
                {
                    // dev_c1_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c1_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Actuador: --");
                }
                {
                    // dev_c1_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c1_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "MAC: --");
                }
            }
        }
        {
            // dev_card_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_2 = obj;
            lv_obj_set_pos(obj, 16, 280);
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
                    lv_label_set_text_static(obj, "Nodo #2");
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
                    lv_label_set_text_static(obj, "Esperando mediciones...");
                }
                {
                    // dev_c2_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c2_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Actuador: --");
                }
                {
                    // dev_c2_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c2_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "MAC: --");
                }
            }
        }
        {
            // dev_card_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_3 = obj;
            lv_obj_set_pos(obj, 16, 426);
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
                    lv_label_set_text_static(obj, "Nodo #3");
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
                    lv_label_set_text_static(obj, "Esperando mediciones...");
                }
                {
                    // dev_c3_act
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c3_act = obj;
                    lv_obj_set_pos(obj, 16, 70);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "Actuador: --");
                }
                {
                    // dev_c3_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c3_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "MAC: --");
                }
            }
        }
        {
            // dev_card_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dev_card_4 = obj;
            lv_obj_set_pos(obj, 16, 572);
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
                    lv_label_set_text_static(obj, "Nodo #4");
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
                    lv_label_set_text_static(obj, "Medidas ausentes");
                }
                {
                    // dev_c4_meta
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.dev_c4_meta = obj;
                    lv_obj_set_pos(obj, 16, 98);
                    lv_obj_set_size(obj, 416, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_label_set_text_static(obj, "MAC: --");
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
            create_user_widget_bottom_nav(obj, 176);
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
    tick_user_widget_header_bar(127);
    tick_user_widget_bottom_nav(176);
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
            lv_obj_set_size(obj, 480, 56);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 192);
        }
        {
            // cfg_sec_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cfg_sec_title = obj;
            lv_obj_set_pos(obj, 16, 68);
            lv_obj_set_size(obj, 300, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_section_title(obj);
            lv_label_set_text_static(obj, "AJUSTES DEL CENTRALIZADOR");
        }
        {
            // cfg_card_main
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.cfg_card_main = obj;
            lv_obj_set_pos(obj, 16, 92);
            lv_obj_set_size(obj, 448, 626);
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
                            lv_label_set_text_static(obj, "Estado de enlace con raiz");
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
            create_user_widget_bottom_nav(obj, 230);
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
    tick_user_widget_header_bar(192);
    tick_user_widget_bottom_nav(230);
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
            lv_obj_set_size(obj, 480, 56);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header_bar(obj, 246);
        }
        {
            // about_card_hero
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_card_hero = obj;
            lv_obj_set_pos(obj, 16, 72);
            lv_obj_set_size(obj, 448, 332);
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
                            lv_label_set_text_static(obj, "Firmware v1.3.0 - ESP32-S3 (7\" Touch)");
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
            create_user_widget_bottom_nav(obj, 273);
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
    tick_user_widget_header_bar(246);
    tick_user_widget_bottom_nav(273);
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
            lv_obj_set_size(obj, 480, 56);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_header(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // header_logo
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 12, 4);
                    lv_obj_set_size(obj, 48, 48);
                    lv_image_set_src(obj, &img_logo_header_48);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                }
                {
                    // header_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 68, 8);
                    lv_obj_set_size(obj, 210, 20);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_header_title(obj);
                    lv_label_set_text_static(obj, "AURA CENTRALIZADOR");
                }
                {
                    // header_subtitle
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 68, 30);
                    lv_obj_set_size(obj, 210, 16);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_header_sub(obj);
                    lv_label_set_text_static(obj, "Aula: Laboratorio 1");
                }
                {
                    // header_theme_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 292, 10);
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
                    lv_obj_set_pos(obj, 354, 12);
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
                            lv_label_set_text_static(obj, "Mesh OK (0)");
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
                    lv_obj_set_pos(obj, 6, 4);
                    lv_obj_set_size(obj, 112, 52);
                    lv_obj_add_event_cb(obj, action_nav_dashboard, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_ico_dashboard
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 45, 4);
                            lv_obj_set_size(obj, 22, 22);
                            lv_image_set_src(obj, &img_icon_dash_22);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                        }
                        {
                            // nav_lbl_dashboard
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 4, 30);
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
                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                    lv_obj_set_pos(obj, 124, 4);
                    lv_obj_set_size(obj, 112, 52);
                    lv_obj_add_event_cb(obj, action_nav_devices, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_ico_devices
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                            lv_obj_set_pos(obj, 45, 4);
                            lv_obj_set_size(obj, 22, 22);
                            lv_image_set_src(obj, &img_icon_devices_22);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                        }
                        {
                            // nav_lbl_devices
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                            lv_obj_set_pos(obj, 4, 30);
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
                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                    lv_obj_set_pos(obj, 242, 4);
                    lv_obj_set_size(obj, 112, 52);
                    lv_obj_add_event_cb(obj, action_nav_config, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_ico_config
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 45, 4);
                            lv_obj_set_size(obj, 22, 22);
                            lv_image_set_src(obj, &img_icon_config_22);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                        }
                        {
                            // nav_lbl_config
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                            lv_obj_set_pos(obj, 4, 30);
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
                    ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                    lv_obj_set_pos(obj, 360, 4);
                    lv_obj_set_size(obj, 112, 52);
                    lv_obj_add_event_cb(obj, action_nav_about, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_nav_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nav_ico_about
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                            lv_obj_set_pos(obj, 45, 4);
                            lv_obj_set_size(obj, 22, 22);
                            lv_image_set_src(obj, &img_icon_about_22);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                        }
                        {
                            // nav_lbl_about
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                            lv_obj_set_pos(obj, 4, 30);
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
    lv_style_set_text_color(get_style_screen_root_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_bg_color(get_style_panel_header_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    lv_style_set_bg_color(get_style_panel_ticker_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    lv_style_set_border_color(get_style_panel_ticker_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_panel_header_badge_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    lv_style_set_border_color(get_style_panel_header_badge_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_panel_status_dot_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    lv_style_set_bg_color(get_style_panel_bottom_nav_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    lv_style_set_bg_color(get_style_panel_divider_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_panel_nav_indicator_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_bg_color(get_style_panel_card_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    lv_style_set_border_color(get_style_panel_card_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_panel_unified_device_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    lv_style_set_border_color(get_style_panel_unified_device_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_panel_relay_tile_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    lv_style_set_border_color(get_style_panel_relay_tile_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_panel_input_box_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    lv_style_set_border_color(get_style_panel_input_box_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_bg_color(get_style_panel_badge_online_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    lv_style_set_border_color(get_style_panel_badge_online_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_panel_badge_offline_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    lv_style_set_border_color(get_style_panel_badge_offline_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][6]));
    lv_style_set_bg_color(get_style_btn_header_theme_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    lv_style_set_border_color(get_style_btn_header_theme_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_btn_header_theme_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_nav_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    lv_style_set_text_color(get_style_btn_nav_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_bg_color(get_style_btn_relay_squircle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_border_color(get_style_btn_relay_squircle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_text_color(get_style_btn_relay_squircle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_relay_squircle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    lv_style_set_border_color(get_style_btn_relay_squircle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_btn_relay_squircle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_toggle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_btn_toggle_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_toggle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    lv_style_set_border_color(get_style_btn_toggle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_text_color(get_style_btn_toggle_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_bg_color(get_style_btn_primary_aura_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    lv_style_set_text_color(get_style_btn_primary_aura_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_filter_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    lv_style_set_text_color(get_style_btn_filter_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_bg_color(get_style_btn_filter_idle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    lv_style_set_border_color(get_style_btn_filter_idle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_text_color(get_style_btn_filter_idle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_text_color(get_style_label_header_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_header_sub_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][21]));
    lv_style_set_text_color(get_style_label_header_badge_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_nav_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_relay_num_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_text_color(get_style_label_section_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_text_color(get_style_label_live_tag_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_label_card_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_hero_title_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_body_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    lv_style_set_text_color(get_style_label_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_text_color(get_style_label_muted_center_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_text_color(get_style_label_badge_online_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_text_color(get_style_label_badge_offline_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][6]));
    lv_style_set_text_color(get_style_label_btn_light_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_btn_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_text_color(get_style_label_chip_light_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_style_set_text_color(get_style_label_chip_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    lv_style_set_bg_color(get_style_bar_sensor_teal_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_bar_sensor_teal_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_bar_sensor_blue_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    lv_style_set_bg_color(get_style_bar_sensor_blue_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    lv_style_set_bg_color(get_style_slider_brightness_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_bg_color(get_style_slider_brightness_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    lv_style_set_bg_color(get_style_slider_brightness_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    lv_style_set_bg_color(get_style_switch_aura_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    lv_style_set_bg_color(get_style_switch_aura_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][3]));
    lv_style_set_bg_color(get_style_switch_aura_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    lv_obj_invalidate(objects.dashboard);
    lv_obj_invalidate(objects.devices);
    lv_obj_invalidate(objects.config);
    lv_obj_invalidate(objects.about);
}
uint32_t theme_colors[2][22] = {
    { 0xff004069, 0xff0d588a, 0xfffe9304, 0xff00b2ad, 0xff494949, 0xff22c55e, 0xffef4444, 0xffffffff, 0xffeaeff5, 0xfff8fafd, 0xff004069, 0xffffffff, 0xffffffff, 0xffe0f7f6, 0xfffee2e2, 0xfffff3e0, 0xff0d588a, 0xffcbdceb, 0xffcbdceb, 0xff1e293b, 0xff5a6e85, 0xffcbdceb },
    { 0xff004069, 0xff38bdf8, 0xfffe9304, 0xff00b2ad, 0xff64748b, 0xff22c55e, 0xffef4444, 0xffffffff, 0xff0b1320, 0xff162235, 0xff071524, 0xff162235, 0xff0b1320, 0xff0d3b3e, 0xff3b181e, 0xff3d2610, 0xff162235, 0xff283c56, 0xff334b6e, 0xfff8fafc, 0xff94a3b8, 0xff94a3b8 },
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