#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_DASHBOARD_ACTUATORS = 1,
    SCREEN_ID_DASHBOARD_SENSORS = 2,
    SCREEN_ID_DEVICES = 3,
    SCREEN_ID_CONFIG = 4,
    SCREEN_ID_ABOUT = 5,
    _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    lv_obj_t *dashboard_actuators;
    lv_obj_t *dashboard_sensors;
    lv_obj_t *devices;
    lv_obj_t *config;
    lv_obj_t *about;
    lv_obj_t *dashboard_act_header;
    lv_obj_t *dashboard_act_header__header_bar_root;
    lv_obj_t *dashboard_act_header__header_logo;
    lv_obj_t *dashboard_act_header__header_title;
    lv_obj_t *dashboard_act_header__header_subtitle;
    lv_obj_t *dashboard_act_header__header_mesh_badge;
    lv_obj_t *dashboard_act_header__header_mesh_dot;
    lv_obj_t *dashboard_act_header__header_mesh_lbl;
    lv_obj_t *dashboard_act_ticker;
    lv_obj_t *dashboard_act_ticker__ticker_bar_root;
    lv_obj_t *dashboard_act_ticker__ticker_prev_btn;
    lv_obj_t *dashboard_act_ticker__ticker_prev_lbl;
    lv_obj_t *dashboard_act_ticker__ticker_chip_1;
    lv_obj_t *dashboard_act_ticker__ticker_chip_lbl_1;
    lv_obj_t *dashboard_act_ticker__ticker_chip_2;
    lv_obj_t *dashboard_act_ticker__ticker_chip_lbl_2;
    lv_obj_t *dashboard_act_ticker__ticker_chip_3;
    lv_obj_t *dashboard_act_ticker__ticker_chip_lbl_3;
    lv_obj_t *dashboard_act_ticker__ticker_chip_4;
    lv_obj_t *dashboard_act_ticker__ticker_chip_lbl_4;
    lv_obj_t *dashboard_act_ticker__ticker_next_btn;
    lv_obj_t *dashboard_act_ticker__ticker_next_lbl;
    lv_obj_t *dashboard_act_ticker__ticker_prog_bar;
    lv_obj_t *dash_act_subtab_act_btn;
    lv_obj_t *dash_act_subtab_act_lbl;
    lv_obj_t *dash_act_subtab_sens_btn;
    lv_obj_t *dash_act_subtab_sens_lbl;
    lv_obj_t *dash_relays_card;
    lv_obj_t *dash_relays_title;
    lv_obj_t *dash_relays_sub;
    lv_obj_t *dash_relay_tile_1;
    lv_obj_t *dash_relay_num_1;
    lv_obj_t *dash_relay_btn_1;
    lv_obj_t *dash_relay_ico_1;
    lv_obj_t *dash_relay_lbl_1;
    lv_obj_t *dash_relay_tile_2;
    lv_obj_t *dash_relay_num_2;
    lv_obj_t *dash_relay_btn_2;
    lv_obj_t *dash_relay_ico_2;
    lv_obj_t *dash_relay_lbl_2;
    lv_obj_t *dash_relay_tile_3;
    lv_obj_t *dash_relay_num_3;
    lv_obj_t *dash_relay_btn_3;
    lv_obj_t *dash_relay_ico_3;
    lv_obj_t *dash_relay_lbl_3;
    lv_obj_t *dash_relay_tile_4;
    lv_obj_t *dash_relay_num_4;
    lv_obj_t *dash_relay_btn_4;
    lv_obj_t *dash_relay_ico_4;
    lv_obj_t *dash_relay_lbl_4;
    lv_obj_t *dash_relay_tile_5;
    lv_obj_t *dash_relay_num_5;
    lv_obj_t *dash_relay_btn_5;
    lv_obj_t *dash_relay_ico_5;
    lv_obj_t *dash_relay_lbl_5;
    lv_obj_t *dash_act_sec_title;
    lv_obj_t *dash_act_sec_tag;
    lv_obj_t *dash_act_empty_card;
    lv_obj_t *dash_act_empty_title;
    lv_obj_t *dash_act_empty_sub;
    lv_obj_t *dash_n1_act_card;
    lv_obj_t *dash_n1_act_node;
    lv_obj_t *dash_n1_act_badge;
    lv_obj_t *dash_n1_act_badge_lbl;
    lv_obj_t *dash_n1_act_div;
    lv_obj_t *dash_n1_act_title;
    lv_obj_t *dash_n1_act_sub;
    lv_obj_t *dash_n1_act_btn;
    lv_obj_t *dash_n1_act_ico;
    lv_obj_t *dash_n2_act_card;
    lv_obj_t *dash_n2_act_node;
    lv_obj_t *dash_n2_act_badge;
    lv_obj_t *dash_n2_act_badge_lbl;
    lv_obj_t *dash_n2_act_div;
    lv_obj_t *dash_n2_act_title;
    lv_obj_t *dash_n2_act_sub;
    lv_obj_t *dash_n2_act_btn;
    lv_obj_t *dash_n2_act_ico;
    lv_obj_t *dashboard_act_bottom_nav;
    lv_obj_t *dashboard_act_bottom_nav__bottom_nav_root;
    lv_obj_t *dashboard_act_bottom_nav__nav_top_line;
    lv_obj_t *dashboard_act_bottom_nav__nav_btn_dashboard;
    lv_obj_t *dashboard_act_bottom_nav__nav_ico_dashboard;
    lv_obj_t *dashboard_act_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *dashboard_act_bottom_nav__nav_btn_devices;
    lv_obj_t *dashboard_act_bottom_nav__nav_ico_devices;
    lv_obj_t *dashboard_act_bottom_nav__nav_lbl_devices;
    lv_obj_t *dashboard_act_bottom_nav__nav_btn_config;
    lv_obj_t *dashboard_act_bottom_nav__nav_ico_config;
    lv_obj_t *dashboard_act_bottom_nav__nav_lbl_config;
    lv_obj_t *dashboard_act_bottom_nav__nav_btn_about;
    lv_obj_t *dashboard_act_bottom_nav__nav_ico_about;
    lv_obj_t *dashboard_act_bottom_nav__nav_lbl_about;
    lv_obj_t *dash_act_nav_active_bar;
    lv_obj_t *dashboard_sens_header;
    lv_obj_t *dashboard_sens_header__header_bar_root;
    lv_obj_t *dashboard_sens_header__header_logo;
    lv_obj_t *dashboard_sens_header__header_title;
    lv_obj_t *dashboard_sens_header__header_subtitle;
    lv_obj_t *dashboard_sens_header__header_mesh_badge;
    lv_obj_t *dashboard_sens_header__header_mesh_dot;
    lv_obj_t *dashboard_sens_header__header_mesh_lbl;
    lv_obj_t *dashboard_sens_ticker;
    lv_obj_t *dashboard_sens_ticker__ticker_bar_root;
    lv_obj_t *dashboard_sens_ticker__ticker_prev_btn;
    lv_obj_t *dashboard_sens_ticker__ticker_prev_lbl;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_1;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_lbl_1;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_2;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_lbl_2;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_3;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_lbl_3;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_4;
    lv_obj_t *dashboard_sens_ticker__ticker_chip_lbl_4;
    lv_obj_t *dashboard_sens_ticker__ticker_next_btn;
    lv_obj_t *dashboard_sens_ticker__ticker_next_lbl;
    lv_obj_t *dashboard_sens_ticker__ticker_prog_bar;
    lv_obj_t *dash_sens_subtab_act_btn;
    lv_obj_t *dash_sens_subtab_act_lbl;
    lv_obj_t *dash_sens_subtab_sens_btn;
    lv_obj_t *dash_sens_subtab_sens_lbl;
    lv_obj_t *dash_nodes_sec_title;
    lv_obj_t *dash_nodes_sec_tag;
    lv_obj_t *dash_empty_card;
    lv_obj_t *dash_empty_title;
    lv_obj_t *dash_empty_sub;
    lv_obj_t *dash_node1_box;
    lv_obj_t *dash_n1_title;
    lv_obj_t *dash_n1_badge;
    lv_obj_t *dash_n1_badge_lbl;
    lv_obj_t *dash_n1_divider;
    lv_obj_t *dash_n1_s1_lbl;
    lv_obj_t *dash_n1_s1_val;
    lv_obj_t *dash_n1_s1_bar;
    lv_obj_t *dash_n1_s2_lbl;
    lv_obj_t *dash_n1_s2_val;
    lv_obj_t *dash_n1_s2_bar;
    lv_obj_t *dash_n1_s3_lbl;
    lv_obj_t *dash_n1_s3_val;
    lv_obj_t *dash_n1_s3_bar;
    lv_obj_t *dash_n1_s4_lbl;
    lv_obj_t *dash_n1_s4_val;
    lv_obj_t *dash_n1_s4_bar;
    lv_obj_t *dash_n1_pres_box;
    lv_obj_t *dash_n1_pres_title;
    lv_obj_t *dash_n1_pres_badge;
    lv_obj_t *dash_n1_pres_lbl;
    lv_obj_t *dash_node2_box;
    lv_obj_t *dash_n2_title;
    lv_obj_t *dash_n2_badge;
    lv_obj_t *dash_n2_badge_lbl;
    lv_obj_t *dash_n2_divider;
    lv_obj_t *dash_n2_s1_lbl;
    lv_obj_t *dash_n2_s1_val;
    lv_obj_t *dash_n2_s1_bar;
    lv_obj_t *dash_n2_s2_lbl;
    lv_obj_t *dash_n2_s2_val;
    lv_obj_t *dash_n2_s2_bar;
    lv_obj_t *dash_n2_s3_lbl;
    lv_obj_t *dash_n2_s3_val;
    lv_obj_t *dash_n2_s3_bar;
    lv_obj_t *dash_n2_s4_lbl;
    lv_obj_t *dash_n2_s4_val;
    lv_obj_t *dash_n2_s4_bar;
    lv_obj_t *dash_n2_pres_box;
    lv_obj_t *dash_n2_pres_title;
    lv_obj_t *dash_n2_pres_badge;
    lv_obj_t *dash_n2_pres_lbl;
    lv_obj_t *dashboard_sens_bottom_nav;
    lv_obj_t *dashboard_sens_bottom_nav__bottom_nav_root;
    lv_obj_t *dashboard_sens_bottom_nav__nav_top_line;
    lv_obj_t *dashboard_sens_bottom_nav__nav_btn_dashboard;
    lv_obj_t *dashboard_sens_bottom_nav__nav_ico_dashboard;
    lv_obj_t *dashboard_sens_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *dashboard_sens_bottom_nav__nav_btn_devices;
    lv_obj_t *dashboard_sens_bottom_nav__nav_ico_devices;
    lv_obj_t *dashboard_sens_bottom_nav__nav_lbl_devices;
    lv_obj_t *dashboard_sens_bottom_nav__nav_btn_config;
    lv_obj_t *dashboard_sens_bottom_nav__nav_ico_config;
    lv_obj_t *dashboard_sens_bottom_nav__nav_lbl_config;
    lv_obj_t *dashboard_sens_bottom_nav__nav_btn_about;
    lv_obj_t *dashboard_sens_bottom_nav__nav_ico_about;
    lv_obj_t *dashboard_sens_bottom_nav__nav_lbl_about;
    lv_obj_t *dash_sens_nav_active_bar;
    lv_obj_t *devices_header;
    lv_obj_t *devices_header__header_bar_root;
    lv_obj_t *devices_header__header_logo;
    lv_obj_t *devices_header__header_title;
    lv_obj_t *devices_header__header_subtitle;
    lv_obj_t *devices_header__header_mesh_badge;
    lv_obj_t *devices_header__header_mesh_dot;
    lv_obj_t *devices_header__header_mesh_lbl;
    lv_obj_t *dev_sec_title;
    lv_obj_t *dev_sec_total;
    lv_obj_t *dev_empty_card;
    lv_obj_t *dev_empty_title;
    lv_obj_t *dev_empty_sub;
    lv_obj_t *dev_card_1;
    lv_obj_t *dev_c1_id;
    lv_obj_t *dev_c1_badge;
    lv_obj_t *dev_c1_badge_lbl;
    lv_obj_t *dev_c1_div;
    lv_obj_t *dev_c1_ticker;
    lv_obj_t *dev_c1_ticker__ticker_bar_root;
    lv_obj_t *dev_c1_ticker__ticker_prev_btn;
    lv_obj_t *dev_c1_ticker__ticker_prev_lbl;
    lv_obj_t *dev_c1_ticker__ticker_chip_1;
    lv_obj_t *dev_c1_ticker__ticker_chip_lbl_1;
    lv_obj_t *dev_c1_ticker__ticker_chip_2;
    lv_obj_t *dev_c1_ticker__ticker_chip_lbl_2;
    lv_obj_t *dev_c1_ticker__ticker_chip_3;
    lv_obj_t *dev_c1_ticker__ticker_chip_lbl_3;
    lv_obj_t *dev_c1_ticker__ticker_chip_4;
    lv_obj_t *dev_c1_ticker__ticker_chip_lbl_4;
    lv_obj_t *dev_c1_ticker__ticker_next_btn;
    lv_obj_t *dev_c1_ticker__ticker_next_lbl;
    lv_obj_t *dev_c1_ticker__ticker_prog_bar;
    lv_obj_t *dev_card_2;
    lv_obj_t *dev_c2_id;
    lv_obj_t *dev_c2_badge;
    lv_obj_t *dev_c2_badge_lbl;
    lv_obj_t *dev_c2_div;
    lv_obj_t *dev_c2_ticker;
    lv_obj_t *dev_c2_ticker__ticker_bar_root;
    lv_obj_t *dev_c2_ticker__ticker_prev_btn;
    lv_obj_t *dev_c2_ticker__ticker_prev_lbl;
    lv_obj_t *dev_c2_ticker__ticker_chip_1;
    lv_obj_t *dev_c2_ticker__ticker_chip_lbl_1;
    lv_obj_t *dev_c2_ticker__ticker_chip_2;
    lv_obj_t *dev_c2_ticker__ticker_chip_lbl_2;
    lv_obj_t *dev_c2_ticker__ticker_chip_3;
    lv_obj_t *dev_c2_ticker__ticker_chip_lbl_3;
    lv_obj_t *dev_c2_ticker__ticker_chip_4;
    lv_obj_t *dev_c2_ticker__ticker_chip_lbl_4;
    lv_obj_t *dev_c2_ticker__ticker_next_btn;
    lv_obj_t *dev_c2_ticker__ticker_next_lbl;
    lv_obj_t *dev_c2_ticker__ticker_prog_bar;
    lv_obj_t *dev_card_3;
    lv_obj_t *dev_c3_id;
    lv_obj_t *dev_c3_badge;
    lv_obj_t *dev_c3_badge_lbl;
    lv_obj_t *dev_c3_div;
    lv_obj_t *dev_c3_ticker;
    lv_obj_t *dev_c3_ticker__ticker_bar_root;
    lv_obj_t *dev_c3_ticker__ticker_prev_btn;
    lv_obj_t *dev_c3_ticker__ticker_prev_lbl;
    lv_obj_t *dev_c3_ticker__ticker_chip_1;
    lv_obj_t *dev_c3_ticker__ticker_chip_lbl_1;
    lv_obj_t *dev_c3_ticker__ticker_chip_2;
    lv_obj_t *dev_c3_ticker__ticker_chip_lbl_2;
    lv_obj_t *dev_c3_ticker__ticker_chip_3;
    lv_obj_t *dev_c3_ticker__ticker_chip_lbl_3;
    lv_obj_t *dev_c3_ticker__ticker_chip_4;
    lv_obj_t *dev_c3_ticker__ticker_chip_lbl_4;
    lv_obj_t *dev_c3_ticker__ticker_next_btn;
    lv_obj_t *dev_c3_ticker__ticker_next_lbl;
    lv_obj_t *dev_c3_ticker__ticker_prog_bar;
    lv_obj_t *dev_card_4;
    lv_obj_t *dev_c4_id;
    lv_obj_t *dev_c4_badge;
    lv_obj_t *dev_c4_badge_lbl;
    lv_obj_t *dev_c4_div;
    lv_obj_t *dev_c4_ticker;
    lv_obj_t *dev_c4_ticker__ticker_bar_root;
    lv_obj_t *dev_c4_ticker__ticker_prev_btn;
    lv_obj_t *dev_c4_ticker__ticker_prev_lbl;
    lv_obj_t *dev_c4_ticker__ticker_chip_1;
    lv_obj_t *dev_c4_ticker__ticker_chip_lbl_1;
    lv_obj_t *dev_c4_ticker__ticker_chip_2;
    lv_obj_t *dev_c4_ticker__ticker_chip_lbl_2;
    lv_obj_t *dev_c4_ticker__ticker_chip_3;
    lv_obj_t *dev_c4_ticker__ticker_chip_lbl_3;
    lv_obj_t *dev_c4_ticker__ticker_chip_4;
    lv_obj_t *dev_c4_ticker__ticker_chip_lbl_4;
    lv_obj_t *dev_c4_ticker__ticker_next_btn;
    lv_obj_t *dev_c4_ticker__ticker_next_lbl;
    lv_obj_t *dev_c4_ticker__ticker_prog_bar;
    lv_obj_t *devices_bottom_nav;
    lv_obj_t *devices_bottom_nav__bottom_nav_root;
    lv_obj_t *devices_bottom_nav__nav_top_line;
    lv_obj_t *devices_bottom_nav__nav_btn_dashboard;
    lv_obj_t *devices_bottom_nav__nav_ico_dashboard;
    lv_obj_t *devices_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *devices_bottom_nav__nav_btn_devices;
    lv_obj_t *devices_bottom_nav__nav_ico_devices;
    lv_obj_t *devices_bottom_nav__nav_lbl_devices;
    lv_obj_t *devices_bottom_nav__nav_btn_config;
    lv_obj_t *devices_bottom_nav__nav_ico_config;
    lv_obj_t *devices_bottom_nav__nav_lbl_config;
    lv_obj_t *devices_bottom_nav__nav_btn_about;
    lv_obj_t *devices_bottom_nav__nav_ico_about;
    lv_obj_t *devices_bottom_nav__nav_lbl_about;
    lv_obj_t *dev_nav_active_bar;
    lv_obj_t *config_header;
    lv_obj_t *config_header__header_bar_root;
    lv_obj_t *config_header__header_logo;
    lv_obj_t *config_header__header_title;
    lv_obj_t *config_header__header_subtitle;
    lv_obj_t *config_header__header_mesh_badge;
    lv_obj_t *config_header__header_mesh_dot;
    lv_obj_t *config_header__header_mesh_lbl;
    lv_obj_t *cfg_sec_title;
    lv_obj_t *cfg_card_main;
    lv_obj_t *cfg_lbl_theme;
    lv_obj_t *cfg_btn_theme_light;
    lv_obj_t *cfg_lbl_theme_light;
    lv_obj_t *cfg_btn_theme_dark;
    lv_obj_t *cfg_lbl_theme_dark;
    lv_obj_t *cfg_lbl_aula;
    lv_obj_t *cfg_box_aula;
    lv_obj_t *cfg_val_aula;
    lv_obj_t *cfg_lbl_chan;
    lv_obj_t *cfg_box_chan;
    lv_obj_t *cfg_val_chan;
    lv_obj_t *cfg_lbl_gw;
    lv_obj_t *cfg_box_gw;
    lv_obj_t *cfg_gw_name;
    lv_obj_t *cfg_gw_mac;
    lv_obj_t *cfg_gw_badge;
    lv_obj_t *cfg_gw_badge_lbl;
    lv_obj_t *config_bottom_nav;
    lv_obj_t *config_bottom_nav__bottom_nav_root;
    lv_obj_t *config_bottom_nav__nav_top_line;
    lv_obj_t *config_bottom_nav__nav_btn_dashboard;
    lv_obj_t *config_bottom_nav__nav_ico_dashboard;
    lv_obj_t *config_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *config_bottom_nav__nav_btn_devices;
    lv_obj_t *config_bottom_nav__nav_ico_devices;
    lv_obj_t *config_bottom_nav__nav_lbl_devices;
    lv_obj_t *config_bottom_nav__nav_btn_config;
    lv_obj_t *config_bottom_nav__nav_ico_config;
    lv_obj_t *config_bottom_nav__nav_lbl_config;
    lv_obj_t *config_bottom_nav__nav_btn_about;
    lv_obj_t *config_bottom_nav__nav_ico_about;
    lv_obj_t *config_bottom_nav__nav_lbl_about;
    lv_obj_t *cfg_nav_active_bar;
    lv_obj_t *about_header;
    lv_obj_t *about_header__header_bar_root;
    lv_obj_t *about_header__header_logo;
    lv_obj_t *about_header__header_title;
    lv_obj_t *about_header__header_subtitle;
    lv_obj_t *about_header__header_mesh_badge;
    lv_obj_t *about_header__header_mesh_dot;
    lv_obj_t *about_header__header_mesh_lbl;
    lv_obj_t *about_card_hero;
    lv_obj_t *about_logo_img;
    lv_obj_t *about_title;
    lv_obj_t *about_subtitle;
    lv_obj_t *about_fw_pill;
    lv_obj_t *about_fw_lbl;
    lv_obj_t *about_card_sys;
    lv_obj_t *about_sys_title;
    lv_obj_t *about_sys_r1;
    lv_obj_t *about_sys_r2;
    lv_obj_t *about_sys_r3;
    lv_obj_t *about_sys_r4;
    lv_obj_t *about_sys_r5;
    lv_obj_t *about_card_team;
    lv_obj_t *about_team_title;
    lv_obj_t *about_team_r1;
    lv_obj_t *about_bottom_nav;
    lv_obj_t *about_bottom_nav__bottom_nav_root;
    lv_obj_t *about_bottom_nav__nav_top_line;
    lv_obj_t *about_bottom_nav__nav_btn_dashboard;
    lv_obj_t *about_bottom_nav__nav_ico_dashboard;
    lv_obj_t *about_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *about_bottom_nav__nav_btn_devices;
    lv_obj_t *about_bottom_nav__nav_ico_devices;
    lv_obj_t *about_bottom_nav__nav_lbl_devices;
    lv_obj_t *about_bottom_nav__nav_btn_config;
    lv_obj_t *about_bottom_nav__nav_ico_config;
    lv_obj_t *about_bottom_nav__nav_lbl_config;
    lv_obj_t *about_bottom_nav__nav_btn_about;
    lv_obj_t *about_bottom_nav__nav_ico_about;
    lv_obj_t *about_bottom_nav__nav_lbl_about;
    lv_obj_t *about_nav_active_bar;
} objects_t;

extern objects_t objects;

void create_screen_dashboard_actuators();
void tick_screen_dashboard_actuators();

void create_screen_dashboard_sensors();
void tick_screen_dashboard_sensors();

void create_screen_devices();
void tick_screen_devices();

void create_screen_config();
void tick_screen_config();

void create_screen_about();
void tick_screen_about();

void create_user_widget_header_bar(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_header_bar(int startWidgetIndex);

void create_user_widget_ticker_bar(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_ticker_bar(int startWidgetIndex);

void create_user_widget_bottom_nav(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_bottom_nav(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Color themes

enum Themes {
    THEME_ID_DEFAULT,
    THEME_ID_DARK,
};
enum Colors {
    COLOR_ID_AURA_BLUE,
    COLOR_ID_AURA_BLUE_LIGHT,
    COLOR_ID_AURA_ORANGE,
    COLOR_ID_AURA_TEAL,
    COLOR_ID_AURA_GRAY,
    COLOR_ID_STATUS_GREEN,
    COLOR_ID_STATUS_DANGER,
    COLOR_ID_FOREGROUND_WHITE,
    COLOR_ID_BG_SCREEN,
    COLOR_ID_BG_CARD,
    COLOR_ID_BG_HEADER,
    COLOR_ID_BG_NAV,
    COLOR_ID_BG_INPUT,
    COLOR_ID_BG_TICKER_ALT,
    COLOR_ID_BG_BADGE_TEAL,
    COLOR_ID_BG_BADGE_DANGER,
    COLOR_ID_BG_BADGE_ORANGE,
    COLOR_ID_BG_HEADER_BADGE,
    COLOR_ID_BORDER_CARD,
    COLOR_ID_BORDER_INPUT,
    COLOR_ID_TEXT_PRIMARY,
    COLOR_ID_TEXT_MUTED,
    COLOR_ID_TEXT_HEADER_SUB,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][23];
extern uint32_t active_theme_index;

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/