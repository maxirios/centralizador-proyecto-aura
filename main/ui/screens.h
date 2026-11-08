#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_DASHBOARD = 1,
    SCREEN_ID_DEVICES = 2,
    SCREEN_ID_CONFIG = 3,
    SCREEN_ID_ABOUT = 4,
    _SCREEN_ID_LAST = 4
};

typedef struct _objects_t {
    lv_obj_t *dashboard;
    lv_obj_t *devices;
    lv_obj_t *config;
    lv_obj_t *about;
    lv_obj_t *dashboard_header;
    lv_obj_t *dashboard_header__header_bar_root;
    lv_obj_t *dashboard_header__header_logo;
    lv_obj_t *dashboard_header__header_title;
    lv_obj_t *dashboard_header__header_subtitle;
    lv_obj_t *dashboard_header__header_theme_btn;
    lv_obj_t *dashboard_header__header_theme_lbl;
    lv_obj_t *dashboard_header__header_mesh_badge;
    lv_obj_t *dashboard_header__header_mesh_dot;
    lv_obj_t *dashboard_header__header_mesh_lbl;
    lv_obj_t *dash_sec_env_title;
    lv_obj_t *dash_sec_env_live;
    lv_obj_t *dash_card_temp;
    lv_obj_t *dash_card_temp_accent;
    lv_obj_t *dash_lbl_temp_title;
    lv_obj_t *dash_lbl_temp_val;
    lv_obj_t *dash_lbl_temp_sub;
    lv_obj_t *dash_card_hum;
    lv_obj_t *dash_card_hum_accent;
    lv_obj_t *dash_lbl_hum_title;
    lv_obj_t *dash_lbl_hum_val;
    lv_obj_t *dash_lbl_hum_sub;
    lv_obj_t *dash_card_co2;
    lv_obj_t *dash_card_co2_accent;
    lv_obj_t *dash_lbl_co2_title;
    lv_obj_t *dash_badge_co2;
    lv_obj_t *dash_lbl_co2_status;
    lv_obj_t *dash_lbl_co2_val;
    lv_obj_t *dash_bar_co2;
    lv_obj_t *dash_lbl_co2_sub;
    lv_obj_t *dash_sec_act_title;
    lv_obj_t *dash_act_row_1;
    lv_obj_t *dash_act1_name;
    lv_obj_t *dash_act1_meta;
    lv_obj_t *dash_act1_btn;
    lv_obj_t *dash_act1_btn_lbl;
    lv_obj_t *dash_act_row_2;
    lv_obj_t *dash_act2_name;
    lv_obj_t *dash_act2_meta;
    lv_obj_t *dash_act2_btn;
    lv_obj_t *dash_act2_btn_lbl;
    lv_obj_t *dash_act_row_3;
    lv_obj_t *dash_act3_name;
    lv_obj_t *dash_act3_meta;
    lv_obj_t *dash_act3_btn;
    lv_obj_t *dash_act3_btn_lbl;
    lv_obj_t *dash_net_strip;
    lv_obj_t *dash_net_title;
    lv_obj_t *dash_net_online_lbl;
    lv_obj_t *dash_net_offline_lbl;
    lv_obj_t *dash_net_gw_lbl;
    lv_obj_t *dashboard_bottom_nav;
    lv_obj_t *dashboard_bottom_nav__bottom_nav_root;
    lv_obj_t *dashboard_bottom_nav__nav_top_line;
    lv_obj_t *dashboard_bottom_nav__nav_btn_dashboard;
    lv_obj_t *dashboard_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *dashboard_bottom_nav__nav_btn_devices;
    lv_obj_t *dashboard_bottom_nav__nav_lbl_devices;
    lv_obj_t *dashboard_bottom_nav__nav_btn_config;
    lv_obj_t *dashboard_bottom_nav__nav_lbl_config;
    lv_obj_t *dashboard_bottom_nav__nav_btn_about;
    lv_obj_t *dashboard_bottom_nav__nav_lbl_about;
    lv_obj_t *dash_nav_active_bar;
    lv_obj_t *devices_header;
    lv_obj_t *devices_header__header_bar_root;
    lv_obj_t *devices_header__header_logo;
    lv_obj_t *devices_header__header_title;
    lv_obj_t *devices_header__header_subtitle;
    lv_obj_t *devices_header__header_theme_btn;
    lv_obj_t *devices_header__header_theme_lbl;
    lv_obj_t *devices_header__header_mesh_badge;
    lv_obj_t *devices_header__header_mesh_dot;
    lv_obj_t *devices_header__header_mesh_lbl;
    lv_obj_t *dev_sec_title;
    lv_obj_t *dev_sec_total;
    lv_obj_t *dev_chip_all;
    lv_obj_t *dev_chip_all_lbl;
    lv_obj_t *dev_chip_sens;
    lv_obj_t *dev_chip_sens_lbl;
    lv_obj_t *dev_chip_act;
    lv_obj_t *dev_chip_act_lbl;
    lv_obj_t *dev_card_1;
    lv_obj_t *dev_c1_id;
    lv_obj_t *dev_c1_badge;
    lv_obj_t *dev_c1_badge_lbl;
    lv_obj_t *dev_c1_vals;
    lv_obj_t *dev_c1_act;
    lv_obj_t *dev_c1_meta;
    lv_obj_t *dev_card_2;
    lv_obj_t *dev_c2_id;
    lv_obj_t *dev_c2_badge;
    lv_obj_t *dev_c2_badge_lbl;
    lv_obj_t *dev_c2_vals;
    lv_obj_t *dev_c2_act;
    lv_obj_t *dev_c2_meta;
    lv_obj_t *dev_card_3;
    lv_obj_t *dev_c3_id;
    lv_obj_t *dev_c3_badge;
    lv_obj_t *dev_c3_badge_lbl;
    lv_obj_t *dev_c3_vals;
    lv_obj_t *dev_c3_act;
    lv_obj_t *dev_c3_meta;
    lv_obj_t *dev_card_4;
    lv_obj_t *dev_c4_id;
    lv_obj_t *dev_c4_badge;
    lv_obj_t *dev_c4_badge_lbl;
    lv_obj_t *dev_c4_vals;
    lv_obj_t *dev_c4_act;
    lv_obj_t *dev_c4_meta;
    lv_obj_t *devices_bottom_nav;
    lv_obj_t *devices_bottom_nav__bottom_nav_root;
    lv_obj_t *devices_bottom_nav__nav_top_line;
    lv_obj_t *devices_bottom_nav__nav_btn_dashboard;
    lv_obj_t *devices_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *devices_bottom_nav__nav_btn_devices;
    lv_obj_t *devices_bottom_nav__nav_lbl_devices;
    lv_obj_t *devices_bottom_nav__nav_btn_config;
    lv_obj_t *devices_bottom_nav__nav_lbl_config;
    lv_obj_t *devices_bottom_nav__nav_btn_about;
    lv_obj_t *devices_bottom_nav__nav_lbl_about;
    lv_obj_t *dev_nav_active_bar;
    lv_obj_t *config_header;
    lv_obj_t *config_header__header_bar_root;
    lv_obj_t *config_header__header_logo;
    lv_obj_t *config_header__header_title;
    lv_obj_t *config_header__header_subtitle;
    lv_obj_t *config_header__header_theme_btn;
    lv_obj_t *config_header__header_theme_lbl;
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
    lv_obj_t *cfg_lbl_bright;
    lv_obj_t *cfg_lbl_bright_val;
    lv_obj_t *cfg_slider_bright;
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
    lv_obj_t *cfg_row_island;
    lv_obj_t *cfg_island_title;
    lv_obj_t *cfg_island_sub;
    lv_obj_t *cfg_island_sw;
    lv_obj_t *cfg_btn_save;
    lv_obj_t *cfg_lbl_save;
    lv_obj_t *config_bottom_nav;
    lv_obj_t *config_bottom_nav__bottom_nav_root;
    lv_obj_t *config_bottom_nav__nav_top_line;
    lv_obj_t *config_bottom_nav__nav_btn_dashboard;
    lv_obj_t *config_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *config_bottom_nav__nav_btn_devices;
    lv_obj_t *config_bottom_nav__nav_lbl_devices;
    lv_obj_t *config_bottom_nav__nav_btn_config;
    lv_obj_t *config_bottom_nav__nav_lbl_config;
    lv_obj_t *config_bottom_nav__nav_btn_about;
    lv_obj_t *config_bottom_nav__nav_lbl_about;
    lv_obj_t *cfg_nav_active_bar;
    lv_obj_t *about_header;
    lv_obj_t *about_header__header_bar_root;
    lv_obj_t *about_header__header_logo;
    lv_obj_t *about_header__header_title;
    lv_obj_t *about_header__header_subtitle;
    lv_obj_t *about_header__header_theme_btn;
    lv_obj_t *about_header__header_theme_lbl;
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
    lv_obj_t *about_team_r2;
    lv_obj_t *about_bottom_nav;
    lv_obj_t *about_bottom_nav__bottom_nav_root;
    lv_obj_t *about_bottom_nav__nav_top_line;
    lv_obj_t *about_bottom_nav__nav_btn_dashboard;
    lv_obj_t *about_bottom_nav__nav_lbl_dashboard;
    lv_obj_t *about_bottom_nav__nav_btn_devices;
    lv_obj_t *about_bottom_nav__nav_lbl_devices;
    lv_obj_t *about_bottom_nav__nav_btn_config;
    lv_obj_t *about_bottom_nav__nav_lbl_config;
    lv_obj_t *about_bottom_nav__nav_btn_about;
    lv_obj_t *about_bottom_nav__nav_lbl_about;
    lv_obj_t *about_nav_active_bar;
} objects_t;

extern objects_t objects;

void create_screen_dashboard();
void tick_screen_dashboard();

void create_screen_devices();
void tick_screen_devices();

void create_screen_config();
void tick_screen_config();

void create_screen_about();
void tick_screen_about();

void create_user_widget_header_bar(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_header_bar(int startWidgetIndex);

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
    COLOR_ID_BG_BADGE_TEAL,
    COLOR_ID_BG_BADGE_DANGER,
    COLOR_ID_BG_HEADER_BADGE,
    COLOR_ID_BORDER_CARD,
    COLOR_ID_BORDER_INPUT,
    COLOR_ID_TEXT_PRIMARY,
    COLOR_ID_TEXT_MUTED,
    COLOR_ID_TEXT_HEADER_SUB,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][21];
extern uint32_t active_theme_index;

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/