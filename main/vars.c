#include "vars.h"

static bool s_dark_theme = false;

bool get_var_dark_theme() {
    return s_dark_theme;
}

void set_var_dark_theme(bool value) {
    s_dark_theme = value;
}
