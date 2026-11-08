#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: ScreenRoot
lv_style_t *get_style_screen_root_MAIN_DEFAULT();
void add_style_screen_root(lv_obj_t *obj);
void remove_style_screen_root(lv_obj_t *obj);

// Style: PanelTransparent
lv_style_t *get_style_panel_transparent_MAIN_DEFAULT();
void add_style_panel_transparent(lv_obj_t *obj);
void remove_style_panel_transparent(lv_obj_t *obj);

// Style: PanelHeader
lv_style_t *get_style_panel_header_MAIN_DEFAULT();
void add_style_panel_header(lv_obj_t *obj);
void remove_style_panel_header(lv_obj_t *obj);

// Style: PanelTickerBar
lv_style_t *get_style_panel_ticker_bar_MAIN_DEFAULT();
void add_style_panel_ticker_bar(lv_obj_t *obj);
void remove_style_panel_ticker_bar(lv_obj_t *obj);

// Style: PanelHeaderBadge
lv_style_t *get_style_panel_header_badge_MAIN_DEFAULT();
void add_style_panel_header_badge(lv_obj_t *obj);
void remove_style_panel_header_badge(lv_obj_t *obj);

// Style: PanelStatusDot
lv_style_t *get_style_panel_status_dot_MAIN_DEFAULT();
void add_style_panel_status_dot(lv_obj_t *obj);
void remove_style_panel_status_dot(lv_obj_t *obj);

// Style: PanelBottomNav
lv_style_t *get_style_panel_bottom_nav_MAIN_DEFAULT();
void add_style_panel_bottom_nav(lv_obj_t *obj);
void remove_style_panel_bottom_nav(lv_obj_t *obj);

// Style: PanelDivider
lv_style_t *get_style_panel_divider_MAIN_DEFAULT();
void add_style_panel_divider(lv_obj_t *obj);
void remove_style_panel_divider(lv_obj_t *obj);

// Style: PanelNavIndicator
lv_style_t *get_style_panel_nav_indicator_MAIN_DEFAULT();
void add_style_panel_nav_indicator(lv_obj_t *obj);
void remove_style_panel_nav_indicator(lv_obj_t *obj);

// Style: PanelCard
lv_style_t *get_style_panel_card_MAIN_DEFAULT();
void add_style_panel_card(lv_obj_t *obj);
void remove_style_panel_card(lv_obj_t *obj);

// Style: PanelUnifiedDevice
lv_style_t *get_style_panel_unified_device_MAIN_DEFAULT();
void add_style_panel_unified_device(lv_obj_t *obj);
void remove_style_panel_unified_device(lv_obj_t *obj);

// Style: PanelRelayTile
lv_style_t *get_style_panel_relay_tile_MAIN_DEFAULT();
void add_style_panel_relay_tile(lv_obj_t *obj);
void remove_style_panel_relay_tile(lv_obj_t *obj);

// Style: PanelInputBox
lv_style_t *get_style_panel_input_box_MAIN_DEFAULT();
void add_style_panel_input_box(lv_obj_t *obj);
void remove_style_panel_input_box(lv_obj_t *obj);

// Style: PanelBadgeOnline
lv_style_t *get_style_panel_badge_online_MAIN_DEFAULT();
void add_style_panel_badge_online(lv_obj_t *obj);
void remove_style_panel_badge_online(lv_obj_t *obj);

// Style: PanelBadgeOffline
lv_style_t *get_style_panel_badge_offline_MAIN_DEFAULT();
void add_style_panel_badge_offline(lv_obj_t *obj);
void remove_style_panel_badge_offline(lv_obj_t *obj);

// Style: BtnTickerNav
lv_style_t *get_style_btn_ticker_nav_MAIN_DEFAULT();
void add_style_btn_ticker_nav(lv_obj_t *obj);
void remove_style_btn_ticker_nav(lv_obj_t *obj);

// Style: BtnNavTab
lv_style_t *get_style_btn_nav_tab_MAIN_DEFAULT();
void add_style_btn_nav_tab(lv_obj_t *obj);
void remove_style_btn_nav_tab(lv_obj_t *obj);

// Style: BtnRelaySquircleOn
lv_style_t *get_style_btn_relay_squircle_on_MAIN_DEFAULT();
void add_style_btn_relay_squircle_on(lv_obj_t *obj);
void remove_style_btn_relay_squircle_on(lv_obj_t *obj);

// Style: BtnRelaySquircleOff
lv_style_t *get_style_btn_relay_squircle_off_MAIN_DEFAULT();
void add_style_btn_relay_squircle_off(lv_obj_t *obj);
void remove_style_btn_relay_squircle_off(lv_obj_t *obj);

// Style: BtnToggleOn
lv_style_t *get_style_btn_toggle_on_MAIN_DEFAULT();
void add_style_btn_toggle_on(lv_obj_t *obj);
void remove_style_btn_toggle_on(lv_obj_t *obj);

// Style: BtnToggleOff
lv_style_t *get_style_btn_toggle_off_MAIN_DEFAULT();
void add_style_btn_toggle_off(lv_obj_t *obj);
void remove_style_btn_toggle_off(lv_obj_t *obj);

// Style: BtnPrimaryAura
lv_style_t *get_style_btn_primary_aura_MAIN_DEFAULT();
void add_style_btn_primary_aura(lv_obj_t *obj);
void remove_style_btn_primary_aura(lv_obj_t *obj);

// Style: LabelHeaderTitle
lv_style_t *get_style_label_header_title_MAIN_DEFAULT();
void add_style_label_header_title(lv_obj_t *obj);
void remove_style_label_header_title(lv_obj_t *obj);

// Style: LabelHeaderSub
lv_style_t *get_style_label_header_sub_MAIN_DEFAULT();
void add_style_label_header_sub(lv_obj_t *obj);
void remove_style_label_header_sub(lv_obj_t *obj);

// Style: LabelHeaderBadge
lv_style_t *get_style_label_header_badge_MAIN_DEFAULT();
void add_style_label_header_badge(lv_obj_t *obj);
void remove_style_label_header_badge(lv_obj_t *obj);

// Style: LabelNavTab
lv_style_t *get_style_label_nav_tab_MAIN_DEFAULT();
void add_style_label_nav_tab(lv_obj_t *obj);
void remove_style_label_nav_tab(lv_obj_t *obj);

// Style: LabelTickerCenter
lv_style_t *get_style_label_ticker_center_MAIN_DEFAULT();
void add_style_label_ticker_center(lv_obj_t *obj);
void remove_style_label_ticker_center(lv_obj_t *obj);

// Style: LabelRelayNum
lv_style_t *get_style_label_relay_num_MAIN_DEFAULT();
void add_style_label_relay_num(lv_obj_t *obj);
void remove_style_label_relay_num(lv_obj_t *obj);

// Style: LabelSectionTitle
lv_style_t *get_style_label_section_title_MAIN_DEFAULT();
void add_style_label_section_title(lv_obj_t *obj);
void remove_style_label_section_title(lv_obj_t *obj);

// Style: LabelLiveTag
lv_style_t *get_style_label_live_tag_MAIN_DEFAULT();
void add_style_label_live_tag(lv_obj_t *obj);
void remove_style_label_live_tag(lv_obj_t *obj);

// Style: LabelCardTitle
lv_style_t *get_style_label_card_title_MAIN_DEFAULT();
void add_style_label_card_title(lv_obj_t *obj);
void remove_style_label_card_title(lv_obj_t *obj);

// Style: LabelHeroTitle
lv_style_t *get_style_label_hero_title_MAIN_DEFAULT();
void add_style_label_hero_title(lv_obj_t *obj);
void remove_style_label_hero_title(lv_obj_t *obj);

// Style: LabelBody
lv_style_t *get_style_label_body_MAIN_DEFAULT();
void add_style_label_body(lv_obj_t *obj);
void remove_style_label_body(lv_obj_t *obj);

// Style: LabelMuted
lv_style_t *get_style_label_muted_MAIN_DEFAULT();
void add_style_label_muted(lv_obj_t *obj);
void remove_style_label_muted(lv_obj_t *obj);

// Style: LabelMutedCenter
lv_style_t *get_style_label_muted_center_MAIN_DEFAULT();
void add_style_label_muted_center(lv_obj_t *obj);
void remove_style_label_muted_center(lv_obj_t *obj);

// Style: LabelBadgeOnline
lv_style_t *get_style_label_badge_online_MAIN_DEFAULT();
void add_style_label_badge_online(lv_obj_t *obj);
void remove_style_label_badge_online(lv_obj_t *obj);

// Style: LabelBadgeOffline
lv_style_t *get_style_label_badge_offline_MAIN_DEFAULT();
void add_style_label_badge_offline(lv_obj_t *obj);
void remove_style_label_badge_offline(lv_obj_t *obj);

// Style: LabelBtnLight
lv_style_t *get_style_label_btn_light_MAIN_DEFAULT();
void add_style_label_btn_light(lv_obj_t *obj);
void remove_style_label_btn_light(lv_obj_t *obj);

// Style: LabelBtnMuted
lv_style_t *get_style_label_btn_muted_MAIN_DEFAULT();
void add_style_label_btn_muted(lv_obj_t *obj);
void remove_style_label_btn_muted(lv_obj_t *obj);

// Style: BarSensorTeal
lv_style_t *get_style_bar_sensor_teal_MAIN_DEFAULT();
lv_style_t *get_style_bar_sensor_teal_INDICATOR_DEFAULT();
void add_style_bar_sensor_teal(lv_obj_t *obj);
void remove_style_bar_sensor_teal(lv_obj_t *obj);

// Style: BarSensorBlue
lv_style_t *get_style_bar_sensor_blue_MAIN_DEFAULT();
lv_style_t *get_style_bar_sensor_blue_INDICATOR_DEFAULT();
void add_style_bar_sensor_blue(lv_obj_t *obj);
void remove_style_bar_sensor_blue(lv_obj_t *obj);

// Style: SwitchAura
lv_style_t *get_style_switch_aura_MAIN_DEFAULT();
lv_style_t *get_style_switch_aura_INDICATOR_CHECKED();
lv_style_t *get_style_switch_aura_KNOB_DEFAULT();
void add_style_switch_aura(lv_obj_t *obj);
void remove_style_switch_aura(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/