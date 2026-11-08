#include "vars.h"
#include <string.h>

static char s_aula_nombre[64] = "Laboratorio 1";
static int32_t s_mesh_nodes_online = 3;
static int32_t s_mesh_nodes_offline = 1;
static int32_t s_mesh_channel = 6;
static bool s_gw_connected = true;
static bool s_isla_mode = false;
static char s_temp_e1_az[32] = "23.8 °C";
static char s_hum_e1_az[32] = "51 %";
static char s_co2_e1_az[32] = "640 ppm";
static bool s_act_vent_on = true;
static bool s_act_lights_on = false;
static bool s_act_led_on = true;
static bool s_dark_theme = false;
static int32_t s_screen_brightness = 85;

const char *get_var_aula_nombre() { return s_aula_nombre; }
void set_var_aula_nombre(const char *value) {
    if (value) {
        strncpy(s_aula_nombre, value, sizeof(s_aula_nombre) - 1);
        s_aula_nombre[sizeof(s_aula_nombre) - 1] = '\0';
    }
}

int32_t get_var_mesh_nodes_online() { return s_mesh_nodes_online; }
void set_var_mesh_nodes_online(int32_t value) { s_mesh_nodes_online = value; }

int32_t get_var_mesh_nodes_offline() { return s_mesh_nodes_offline; }
void set_var_mesh_nodes_offline(int32_t value) { s_mesh_nodes_offline = value; }

int32_t get_var_mesh_channel() { return s_mesh_channel; }
void set_var_mesh_channel(int32_t value) { s_mesh_channel = value; }

bool get_var_gw_connected() { return s_gw_connected; }
void set_var_gw_connected(bool value) { s_gw_connected = value; }

bool get_var_isla_mode() { return s_isla_mode; }
void set_var_isla_mode(bool value) { s_isla_mode = value; }

const char *get_var_temp_e1_az() { return s_temp_e1_az; }
void set_var_temp_e1_az(const char *value) {
    if (value) {
        strncpy(s_temp_e1_az, value, sizeof(s_temp_e1_az) - 1);
        s_temp_e1_az[sizeof(s_temp_e1_az) - 1] = '\0';
    }
}

const char *get_var_hum_e1_az() { return s_hum_e1_az; }
void set_var_hum_e1_az(const char *value) {
    if (value) {
        strncpy(s_hum_e1_az, value, sizeof(s_hum_e1_az) - 1);
        s_hum_e1_az[sizeof(s_hum_e1_az) - 1] = '\0';
    }
}

const char *get_var_co2_e1_az() { return s_co2_e1_az; }
void set_var_co2_e1_az(const char *value) {
    if (value) {
        strncpy(s_co2_e1_az, value, sizeof(s_co2_e1_az) - 1);
        s_co2_e1_az[sizeof(s_co2_e1_az) - 1] = '\0';
    }
}

bool get_var_act_vent_on() { return s_act_vent_on; }
void set_var_act_vent_on(bool value) { s_act_vent_on = value; }

bool get_var_act_lights_on() { return s_act_lights_on; }
void set_var_act_lights_on(bool value) { s_act_lights_on = value; }

bool get_var_act_led_on() { return s_act_led_on; }
void set_var_act_led_on(bool value) { s_act_led_on = value; }

bool get_var_dark_theme() { return s_dark_theme; }
void set_var_dark_theme(bool value) { s_dark_theme = value; }

int32_t get_var_screen_brightness() { return s_screen_brightness; }
void set_var_screen_brightness(int32_t value) { s_screen_brightness = value; }
