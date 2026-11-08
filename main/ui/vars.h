#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_AULA_NOMBRE = 0,
    FLOW_GLOBAL_VARIABLE_MESH_NODES_ONLINE = 1,
    FLOW_GLOBAL_VARIABLE_MESH_NODES_OFFLINE = 2,
    FLOW_GLOBAL_VARIABLE_MESH_CHANNEL = 3,
    FLOW_GLOBAL_VARIABLE_GW_CONNECTED = 4,
    FLOW_GLOBAL_VARIABLE_ISLA_MODE = 5,
    FLOW_GLOBAL_VARIABLE_TEMP_E1_AZ = 6,
    FLOW_GLOBAL_VARIABLE_HUM_E1_AZ = 7,
    FLOW_GLOBAL_VARIABLE_CO2_E1_AZ = 8,
    FLOW_GLOBAL_VARIABLE_ACT_VENT_ON = 9,
    FLOW_GLOBAL_VARIABLE_ACT_LIGHTS_ON = 10,
    FLOW_GLOBAL_VARIABLE_ACT_LED_ON = 11,
    FLOW_GLOBAL_VARIABLE_DARK_THEME = 12,
    FLOW_GLOBAL_VARIABLE_SCREEN_BRIGHTNESS = 13
};

// Native global variables

extern const char *get_var_aula_nombre();
extern void set_var_aula_nombre(const char *value);
extern int32_t get_var_mesh_nodes_online();
extern void set_var_mesh_nodes_online(int32_t value);
extern int32_t get_var_mesh_nodes_offline();
extern void set_var_mesh_nodes_offline(int32_t value);
extern int32_t get_var_mesh_channel();
extern void set_var_mesh_channel(int32_t value);
extern bool get_var_gw_connected();
extern void set_var_gw_connected(bool value);
extern bool get_var_isla_mode();
extern void set_var_isla_mode(bool value);
extern const char *get_var_temp_e1_az();
extern void set_var_temp_e1_az(const char *value);
extern const char *get_var_hum_e1_az();
extern void set_var_hum_e1_az(const char *value);
extern const char *get_var_co2_e1_az();
extern void set_var_co2_e1_az(const char *value);
extern bool get_var_act_vent_on();
extern void set_var_act_vent_on(bool value);
extern bool get_var_act_lights_on();
extern void set_var_act_lights_on(bool value);
extern bool get_var_act_led_on();
extern void set_var_act_led_on(bool value);
extern bool get_var_dark_theme();
extern void set_var_dark_theme(bool value);
extern int32_t get_var_screen_brightness();
extern void set_var_screen_brightness(int32_t value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/