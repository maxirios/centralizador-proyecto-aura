#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: ScreenRoot
//

void init_style_screen_root_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][8]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_screen_root_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_screen_root_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_screen_root(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_screen_root_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_screen_root(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_screen_root_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelTransparent
//

void init_style_panel_transparent_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][8]));
    lv_style_set_bg_opa(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_transparent_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_transparent_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_transparent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_transparent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_transparent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_transparent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelHeader
//

void init_style_panel_header_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_header_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_header_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_header(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_header_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_header(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_header_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelTickerBar
//

void init_style_panel_ticker_bar_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_ticker_bar_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_ticker_bar_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_ticker_bar(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_ticker_bar_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_ticker_bar(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_ticker_bar_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelHeaderBadge
//

void init_style_panel_header_badge_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 16);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_header_badge_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_header_badge_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_header_badge(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_header_badge_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_header_badge(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_header_badge_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelStatusDot
//

void init_style_panel_status_dot_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][5]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 5);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_status_dot_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_status_dot_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_status_dot(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_status_dot_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_status_dot(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_status_dot_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelBottomNav
//

void init_style_panel_bottom_nav_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_bottom_nav_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_bottom_nav_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_bottom_nav(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_bottom_nav_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_bottom_nav(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_bottom_nav_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelDivider
//

void init_style_panel_divider_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_divider_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_divider_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_divider(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_divider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_divider(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_divider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelNavIndicator
//

void init_style_panel_nav_indicator_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 2);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_nav_indicator_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_nav_indicator_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_nav_indicator(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_nav_indicator_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_nav_indicator(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_nav_indicator_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelCard
//

void init_style_panel_card_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 10);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_card_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_card_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_card(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_card_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_card(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_card_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelUnifiedDevice
//

void init_style_panel_unified_device_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_unified_device_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_unified_device_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_unified_device(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_unified_device_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_unified_device(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_unified_device_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelRelayTile
//

void init_style_panel_relay_tile_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][12]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 9);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_relay_tile_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_relay_tile_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_relay_tile(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_relay_tile_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_relay_tile(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_relay_tile_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelInputBox
//

void init_style_panel_input_box_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][12]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_input_box_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_input_box_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_input_box(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_input_box_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_input_box(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_input_box_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelBadgeOnline
//

void init_style_panel_badge_online_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 10);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_badge_online_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_badge_online_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_badge_online(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_badge_online_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_badge_online(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_badge_online_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelBadgeOffline
//

void init_style_panel_badge_offline_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][6]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 10);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_badge_offline_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_badge_offline_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_badge_offline(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_badge_offline_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_badge_offline(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_badge_offline_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnTickerNav
//

void init_style_btn_ticker_nav_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][12]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 6);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_ticker_nav_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_ticker_nav_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_ticker_nav(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_ticker_nav_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_ticker_nav(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_ticker_nav_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnNavTab
//

void init_style_btn_nav_tab_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_nav_tab_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_nav_tab_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_nav_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_nav_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_nav_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_nav_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnRelaySquircleOn
//

void init_style_btn_relay_squircle_on_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 12);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_relay_squircle_on_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_relay_squircle_on_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_relay_squircle_on(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_relay_squircle_on_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_relay_squircle_on(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_relay_squircle_on_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnRelaySquircleOff
//

void init_style_btn_relay_squircle_off_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][4]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 12);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_relay_squircle_off_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_relay_squircle_off_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_relay_squircle_off(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_relay_squircle_off_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_relay_squircle_off(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_relay_squircle_off_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnToggleOn
//

void init_style_btn_toggle_on_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_toggle_on_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_toggle_on_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_toggle_on(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_toggle_on_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_toggle_on(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_toggle_on_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnToggleOff
//

void init_style_btn_toggle_off_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][20]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_toggle_off_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_toggle_off_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_toggle_off(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_toggle_off_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_toggle_off(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_toggle_off_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnPrimaryAura
//

void init_style_btn_primary_aura_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_primary_aura_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_primary_aura_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_primary_aura(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_primary_aura_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_primary_aura(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_primary_aura_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelHeaderTitle
//

void init_style_label_header_title_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_LEFT);
};

lv_style_t *get_style_label_header_title_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_header_title_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_header_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_header_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_header_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_header_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelHeaderSub
//

void init_style_label_header_sub_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][21]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_LEFT);
};

lv_style_t *get_style_label_header_sub_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_header_sub_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_header_sub(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_header_sub_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_header_sub(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_header_sub_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelHeaderBadge
//

void init_style_label_header_badge_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_header_badge_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_header_badge_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_header_badge(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_header_badge_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_header_badge(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_header_badge_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelNavTab
//

void init_style_label_nav_tab_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_nav_tab_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_nav_tab_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_nav_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_nav_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_nav_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_nav_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelTickerCenter
//

void init_style_label_ticker_center_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_ticker_center_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_ticker_center_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_ticker_center(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_ticker_center_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_ticker_center(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_ticker_center_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelRelayNum
//

void init_style_label_relay_num_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_relay_num_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_relay_num_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_relay_num(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_relay_num_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_relay_num(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_relay_num_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelSectionTitle
//

void init_style_label_section_title_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][20]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_LEFT);
};

lv_style_t *get_style_label_section_title_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_section_title_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_section_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_section_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_section_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_section_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelLiveTag
//

void init_style_label_live_tag_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_label_live_tag_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_live_tag_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_live_tag(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_live_tag_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_live_tag(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_live_tag_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelCardTitle
//

void init_style_label_card_title_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_LEFT);
};

lv_style_t *get_style_label_card_title_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_card_title_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_card_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_card_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_card_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_card_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelHeroTitle
//

void init_style_label_hero_title_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_22);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_hero_title_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_hero_title_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_hero_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_hero_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_hero_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_hero_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelBody
//

void init_style_label_body_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_LEFT);
};

lv_style_t *get_style_label_body_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_body_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_body(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_body_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_body(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_body_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMuted
//

void init_style_label_muted_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][20]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_LEFT);
};

lv_style_t *get_style_label_muted_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_muted_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_muted(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_muted_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_muted(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_muted_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMutedCenter
//

void init_style_label_muted_center_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][20]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_muted_center_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_muted_center_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_muted_center(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_muted_center_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_muted_center(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_muted_center_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelBadgeOnline
//

void init_style_label_badge_online_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_badge_online_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_badge_online_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_badge_online(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_badge_online_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_badge_online(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_badge_online_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelBadgeOffline
//

void init_style_label_badge_offline_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][6]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_badge_offline_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_badge_offline_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_badge_offline(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_badge_offline_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_badge_offline(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_badge_offline_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelBtnLight
//

void init_style_label_btn_light_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_btn_light_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_btn_light_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_btn_light(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_btn_light_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_btn_light(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_btn_light_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelBtnMuted
//

void init_style_label_btn_muted_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][20]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_btn_muted_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_btn_muted_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_btn_muted(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_btn_muted_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_btn_muted(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_btn_muted_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BarSensorTeal
//

void init_style_bar_sensor_teal_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_bar_sensor_teal_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_sensor_teal_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_bar_sensor_teal_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_bar_sensor_teal_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_sensor_teal_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_bar_sensor_teal(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_bar_sensor_teal_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_bar_sensor_teal_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_bar_sensor_teal(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_bar_sensor_teal_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_bar_sensor_teal_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: BarSensorBlue
//

void init_style_bar_sensor_blue_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_bar_sensor_blue_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_sensor_blue_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_bar_sensor_blue_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_bar_sensor_blue_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_sensor_blue_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_bar_sensor_blue(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_bar_sensor_blue_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_bar_sensor_blue_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_bar_sensor_blue(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_bar_sensor_blue_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_bar_sensor_blue_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: SwitchAura
//

void init_style_switch_aura_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 14);
};

lv_style_t *get_style_switch_aura_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_aura_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_switch_aura_INDICATOR_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 14);
};

lv_style_t *get_style_switch_aura_INDICATOR_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_aura_INDICATOR_CHECKED(style);
    }
    return style;
};

void init_style_switch_aura_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 12);
};

lv_style_t *get_style_switch_aura_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_aura_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_switch_aura(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_switch_aura_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_switch_aura_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_switch_aura_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_switch_aura(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_switch_aura_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_switch_aura_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_switch_aura_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_screen_root,
        add_style_panel_transparent,
        add_style_panel_header,
        add_style_panel_ticker_bar,
        add_style_panel_header_badge,
        add_style_panel_status_dot,
        add_style_panel_bottom_nav,
        add_style_panel_divider,
        add_style_panel_nav_indicator,
        add_style_panel_card,
        add_style_panel_unified_device,
        add_style_panel_relay_tile,
        add_style_panel_input_box,
        add_style_panel_badge_online,
        add_style_panel_badge_offline,
        add_style_btn_ticker_nav,
        add_style_btn_nav_tab,
        add_style_btn_relay_squircle_on,
        add_style_btn_relay_squircle_off,
        add_style_btn_toggle_on,
        add_style_btn_toggle_off,
        add_style_btn_primary_aura,
        add_style_label_header_title,
        add_style_label_header_sub,
        add_style_label_header_badge,
        add_style_label_nav_tab,
        add_style_label_ticker_center,
        add_style_label_relay_num,
        add_style_label_section_title,
        add_style_label_live_tag,
        add_style_label_card_title,
        add_style_label_hero_title,
        add_style_label_body,
        add_style_label_muted,
        add_style_label_muted_center,
        add_style_label_badge_online,
        add_style_label_badge_offline,
        add_style_label_btn_light,
        add_style_label_btn_muted,
        add_style_bar_sensor_teal,
        add_style_bar_sensor_blue,
        add_style_switch_aura,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_screen_root,
        remove_style_panel_transparent,
        remove_style_panel_header,
        remove_style_panel_ticker_bar,
        remove_style_panel_header_badge,
        remove_style_panel_status_dot,
        remove_style_panel_bottom_nav,
        remove_style_panel_divider,
        remove_style_panel_nav_indicator,
        remove_style_panel_card,
        remove_style_panel_unified_device,
        remove_style_panel_relay_tile,
        remove_style_panel_input_box,
        remove_style_panel_badge_online,
        remove_style_panel_badge_offline,
        remove_style_btn_ticker_nav,
        remove_style_btn_nav_tab,
        remove_style_btn_relay_squircle_on,
        remove_style_btn_relay_squircle_off,
        remove_style_btn_toggle_on,
        remove_style_btn_toggle_off,
        remove_style_btn_primary_aura,
        remove_style_label_header_title,
        remove_style_label_header_sub,
        remove_style_label_header_badge,
        remove_style_label_nav_tab,
        remove_style_label_ticker_center,
        remove_style_label_relay_num,
        remove_style_label_section_title,
        remove_style_label_live_tag,
        remove_style_label_card_title,
        remove_style_label_hero_title,
        remove_style_label_body,
        remove_style_label_muted,
        remove_style_label_muted_center,
        remove_style_label_badge_online,
        remove_style_label_badge_offline,
        remove_style_label_btn_light,
        remove_style_label_btn_muted,
        remove_style_bar_sensor_teal,
        remove_style_bar_sensor_blue,
        remove_style_switch_aura,
    };
    remove_style_funcs[styleIndex](obj);
}