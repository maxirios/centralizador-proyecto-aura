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
extern void action_toggle_theme(lv_event_t * e);
extern void action_set_theme_light(lv_event_t * e);
extern void action_set_theme_dark(lv_event_t * e);
extern void action_toggle_actuator1(lv_event_t * e);
extern void action_toggle_actuator2(lv_event_t * e);
extern void action_toggle_actuator3(lv_event_t * e);
extern void action_filter_all(lv_event_t * e);
extern void action_filter_sensors(lv_event_t * e);
extern void action_filter_actuators(lv_event_t * e);
extern void action_save_config(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/