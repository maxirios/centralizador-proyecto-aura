#include "relay_ctrl.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "relay_ctrl";

#ifndef CONFIG_AURA_LOCAL_RELAYS_COUNT
#define CONFIG_AURA_LOCAL_RELAYS_COUNT 5
#endif

#ifndef CONFIG_AURA_RELAY_1_GPIO
#define CONFIG_AURA_RELAY_1_GPIO 6
#endif
#ifndef CONFIG_AURA_RELAY_1_LABEL
#define CONFIG_AURA_RELAY_1_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_2_GPIO
#define CONFIG_AURA_RELAY_2_GPIO 15
#endif
#ifndef CONFIG_AURA_RELAY_2_LABEL
#define CONFIG_AURA_RELAY_2_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_3_GPIO
#define CONFIG_AURA_RELAY_3_GPIO 16
#endif
#ifndef CONFIG_AURA_RELAY_3_LABEL
#define CONFIG_AURA_RELAY_3_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_4_GPIO
#define CONFIG_AURA_RELAY_4_GPIO 11
#endif
#ifndef CONFIG_AURA_RELAY_4_LABEL
#define CONFIG_AURA_RELAY_4_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_5_GPIO
#define CONFIG_AURA_RELAY_5_GPIO 12
#endif
#ifndef CONFIG_AURA_RELAY_5_LABEL
#define CONFIG_AURA_RELAY_5_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_6_GPIO
#define CONFIG_AURA_RELAY_6_GPIO -1
#endif
#ifndef CONFIG_AURA_RELAY_6_LABEL
#define CONFIG_AURA_RELAY_6_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_7_GPIO
#define CONFIG_AURA_RELAY_7_GPIO -1
#endif
#ifndef CONFIG_AURA_RELAY_7_LABEL
#define CONFIG_AURA_RELAY_7_LABEL ""
#endif

#ifndef CONFIG_AURA_RELAY_8_GPIO
#define CONFIG_AURA_RELAY_8_GPIO -1
#endif
#ifndef CONFIG_AURA_RELAY_8_LABEL
#define CONFIG_AURA_RELAY_8_LABEL ""
#endif

typedef struct {
    int gpio;
    const char *label;
    bool state;
    bool gpio_valid;
} relay_slot_t;

static relay_slot_t s_relays[AURA_MAX_LOCAL_RELAYS] = {
    { CONFIG_AURA_RELAY_1_GPIO, CONFIG_AURA_RELAY_1_LABEL, false, false },
    { CONFIG_AURA_RELAY_2_GPIO, CONFIG_AURA_RELAY_2_LABEL, false, false },
    { CONFIG_AURA_RELAY_3_GPIO, CONFIG_AURA_RELAY_3_LABEL, false, false },
    { CONFIG_AURA_RELAY_4_GPIO, CONFIG_AURA_RELAY_4_LABEL, false, false },
    { CONFIG_AURA_RELAY_5_GPIO, CONFIG_AURA_RELAY_5_LABEL, false, false },
    { CONFIG_AURA_RELAY_6_GPIO, CONFIG_AURA_RELAY_6_LABEL, false, false },
    { CONFIG_AURA_RELAY_7_GPIO, CONFIG_AURA_RELAY_7_LABEL, false, false },
    { CONFIG_AURA_RELAY_8_GPIO, CONFIG_AURA_RELAY_8_LABEL, false, false },
};

static bool es_pin_reservado_pantalla(int gpio)
{
    static const int reservados[] = {
        0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 14, 17, 18, 19, 20, 21,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
    };
    for (size_t i = 0; i < sizeof(reservados) / sizeof(reservados[0]); i++) {
        if (gpio == reservados[i]) {
            return true;
        }
    }
    return false;
}

esp_err_t relay_ctrl_init(void)
{
    int count = relay_ctrl_get_count();
    for (int i = 0; i < count; i++) {
        int pin = s_relays[i].gpio;
        if (pin >= 0 && GPIO_IS_VALID_OUTPUT_GPIO(pin) && !es_pin_reservado_pantalla(pin)) {
            gpio_config_t io_conf = {
                .pin_bit_mask = (1ULL << pin),
                .mode = GPIO_MODE_OUTPUT,
                .pull_up_en = GPIO_PULLUP_DISABLE,
                .pull_down_en = GPIO_PULLDOWN_DISABLE,
                .intr_type = GPIO_INTR_DISABLE,
            };
            if (gpio_config(&io_conf) == ESP_OK) {
                gpio_set_level((gpio_num_t)pin, s_relays[i].state ? 1 : 0);
                s_relays[i].gpio_valid = true;
                ESP_LOGI(TAG, "Rele %d inicializado en GPIO %d (label='%s')",
                         i + 1, pin, s_relays[i].label);
            }
        } else {
            s_relays[i].gpio_valid = false;
            ESP_LOGI(TAG, "Rele %d inicializado en modo logico (GPIO=%d, label='%s')",
                     i + 1, pin, s_relays[i].label);
        }
    }
    return ESP_OK;
}

int relay_ctrl_get_count(void)
{
    int c = CONFIG_AURA_LOCAL_RELAYS_COUNT;
    if (c < 1) c = 1;
    if (c > AURA_MAX_LOCAL_RELAYS) c = AURA_MAX_LOCAL_RELAYS;
    return c;
}

bool relay_ctrl_get_state(int idx)
{
    if (idx < 0 || idx >= AURA_MAX_LOCAL_RELAYS) return false;
    return s_relays[idx].state;
}

void relay_ctrl_set_state(int idx, bool on)
{
    if (idx < 0 || idx >= AURA_MAX_LOCAL_RELAYS) return;
    s_relays[idx].state = on;
    if (s_relays[idx].gpio_valid) {
        gpio_set_level((gpio_num_t)s_relays[idx].gpio, on ? 1 : 0);
    }
    ESP_LOGI(TAG, "Rele %d (%s) -> %s",
             idx + 1,
             s_relays[idx].label[0] ? s_relays[idx].label : "sin etiqueta",
             on ? "ON" : "OFF");
}

bool relay_ctrl_toggle(int idx)
{
    if (idx < 0 || idx >= AURA_MAX_LOCAL_RELAYS) return false;
    bool next = !s_relays[idx].state;
    relay_ctrl_set_state(idx, next);
    return next;
}

const char *relay_ctrl_get_label(int idx)
{
    if (idx < 0 || idx >= AURA_MAX_LOCAL_RELAYS) return "";
    return s_relays[idx].label ? s_relays[idx].label : "";
}

int relay_ctrl_get_gpio(int idx)
{
    if (idx < 0 || idx >= AURA_MAX_LOCAL_RELAYS) return -1;
    return s_relays[idx].gpio;
}
