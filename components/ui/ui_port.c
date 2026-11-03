#include "ui_port.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "bsp_display.h"
#include "bsp_touch.h"

static const char *TAG = "ui_port";
static lv_display_t *s_disp = NULL;
static lv_indev_t *s_indev = NULL;

static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    bsp_touch_data_t touch;
    if (bsp_touch_read(&touch) == ESP_OK && touch.presionado) {
        data->point.x = (int32_t)touch.x;
        data->point.y = (int32_t)touch.y;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

esp_err_t ui_port_init(void)
{
    esp_lcd_panel_handle_t panel_handle = bsp_display_get_panel_handle();
    if (!panel_handle) {
        ESP_LOGE(TAG, "Panel display no inicializado");
        return ESP_ERR_INVALID_STATE;
    }

    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    esp_err_t err = lvgl_port_init(&lvgl_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error inicializando lvgl_port: %s", esp_err_to_name(err));
        return err;
    }

    const lvgl_port_display_cfg_t disp_cfg = {
        .panel_handle = panel_handle,
        .buffer_size = BSP_LCD_H_RES * 40,
        .double_buffer = false,
        .hres = BSP_LCD_H_RES,
        .vres = BSP_LCD_V_RES,
        .monochrome = false,
        .flags = {
            .buff_spiram = 1,
            .sw_rotate = 1,
        },
    };

    const lvgl_port_display_rgb_cfg_t rgb_cfg = {
        .flags = {
            .bb_mode = 1,
        },
    };

    s_disp = lvgl_port_add_disp_rgb(&disp_cfg, &rgb_cfg);
    if (!s_disp) {
        ESP_LOGE(TAG, "Error agregando display RGB a lvgl_port");
        return ESP_FAIL;
    }

    lv_display_set_rotation(s_disp, LV_DISPLAY_ROTATION_90);

    if (lvgl_port_lock(100)) {
        s_indev = lv_indev_create();
        if (s_indev) {
            lv_indev_set_type(s_indev, LV_INDEV_TYPE_POINTER);
            lv_indev_set_read_cb(s_indev, touch_read_cb);
            lv_indev_set_display(s_indev, s_disp);
        }
        lvgl_port_unlock();
    }

    ESP_LOGI(TAG, "LVGL v9 y puerto táctil inicializados correctamente en modo portrait");
    return ESP_OK;
}

bool ui_port_lock(uint32_t timeout_ms)
{
    return lvgl_port_lock(timeout_ms);
}

void ui_port_unlock(void)
{
    lvgl_port_unlock();
}

lv_display_t *ui_port_get_display(void)
{
    return s_disp;
}
