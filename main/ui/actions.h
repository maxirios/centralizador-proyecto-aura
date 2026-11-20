#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_nav_dashboard(lv_event_t * e);
extern void action_nav_devices(lv_event_t * e);
extern void action_nav_config(lv_event_t * e);
extern void action_nav_about(lv_event_t * e);
extern void action_set_theme_light(lv_event_t * e);
extern void action_set_theme_dark(lv_event_t * e);
extern void action_ticker_prev(lv_event_t * e);
extern void action_ticker_next(lv_event_t * e);
extern void action_dash_tab_actuators(lv_event_t * e);
extern void action_dash_tab_sensors(lv_event_t * e);
extern void action_toggle_local_relay1(lv_event_t * e);
extern void action_toggle_local_relay2(lv_event_t * e);
extern void action_toggle_local_relay3(lv_event_t * e);
extern void action_toggle_local_relay4(lv_event_t * e);
extern void action_toggle_local_relay5(lv_event_t * e);
extern void action_toggle_node1_actuator(lv_event_t * e);
extern void action_toggle_node2_actuator(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/