#include "bsp_display.h"
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "bsp_display";

#define BSP_I2C_NUM          I2C_NUM_0
#define BSP_I2C_SDA_PIN      8
#define BSP_I2C_SCL_PIN      9
#define BSP_I2C_FREQ_HZ      400000

#define CH422G_I2C_ADDR_SET  0x24
#define CH422G_I2C_ADDR_IO   0x38
#define CH422G_BL_BIT        (1 << 2)

#define BSP_LCD_PCLK_PIN     7
#define BSP_LCD_DE_PIN       5
#define BSP_LCD_VSYNC_PIN    3
#define BSP_LCD_HSYNC_PIN    46

#define BSP_LCD_DATA0_PIN    14 // B3
#define BSP_LCD_DATA1_PIN    38 // B4
#define BSP_LCD_DATA2_PIN    18 // B5
#define BSP_LCD_DATA3_PIN    17 // B6
#define BSP_LCD_DATA4_PIN    10 // B7

#define BSP_LCD_DATA5_PIN    39 // G2
#define BSP_LCD_DATA6_PIN    0  // G3
#define BSP_LCD_DATA7_PIN    45 // G4
#define BSP_LCD_DATA8_PIN    48 // G5
#define BSP_LCD_DATA9_PIN    47 // G6
#define BSP_LCD_DATA10_PIN   21 // G7

#define BSP_LCD_DATA11_PIN   1  // R3
#define BSP_LCD_DATA12_PIN   2  // R4
#define BSP_LCD_DATA13_PIN   42 // R5
#define BSP_LCD_DATA14_PIN   41 // R6
#define BSP_LCD_DATA15_PIN   40 // R7

static esp_lcd_panel_handle_t s_panel_handle = NULL;
static bool s_i2c_initialized = false;
static uint8_t s_ch422g_io_state = 0x00;

static esp_err_t bsp_i2c_ensure_init(void)
{
    if (s_i2c_initialized) {
        return ESP_OK;
    }
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = BSP_I2C_SDA_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = BSP_I2C_SCL_PIN,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = BSP_I2C_FREQ_HZ,
    };
    esp_err_t err = i2c_param_config(BSP_I2C_NUM, &conf);
    if (err == ESP_OK) {
        err = i2c_driver_install(BSP_I2C_NUM, conf.mode, 0, 0, 0);
    }
    if (err == ESP_OK || err == ESP_ERR_INVALID_STATE) {
        s_i2c_initialized = true;
        return ESP_OK;
    }
    ESP_LOGE(TAG, "Error inicializando bus I2C: %s", esp_err_to_name(err));
    return err;
}

esp_err_t bsp_display_backlight_init(void)
{
    esp_err_t err = bsp_i2c_ensure_init();
    if (err != ESP_OK) {
        return err;
    }

    uint8_t set_cmd = 0x01; // Activa salidas IO en CH422G
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CH422G_I2C_ADDR_SET << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, set_cmd, true);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(BSP_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Expansor CH422G no respondio a configuracion de salidas (err=%s)", esp_err_to_name(err));
    }
    return bsp_display_set_backlight(true);
}

esp_err_t bsp_display_set_backlight(bool on)
{
    esp_err_t err = bsp_i2c_ensure_init();
    if (err != ESP_OK) {
        return err;
    }

    if (on) {
        s_ch422g_io_state |= CH422G_BL_BIT;
    } else {
        s_ch422g_io_state &= ~CH422G_BL_BIT;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CH422G_I2C_ADDR_IO << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, s_ch422g_io_state, true);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(BSP_I2C_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Backlight LCD %s", on ? "ENCENDIDO" : "APAGADO");
    } else {
        ESP_LOGW(TAG, "Error escribiendo estado backlight en CH422G: %s", esp_err_to_name(err));
    }
    return err;
}

esp_err_t bsp_display_init(esp_lcd_panel_handle_t *out_panel_handle)
{
    ESP_LOGI(TAG, "Inicializando display RGB Waveshare ST7262 (800x480 nativo)...");

    bsp_display_backlight_init();

    esp_lcd_rgb_panel_config_t panel_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = {
            .pclk_hz = 16000000,
            .h_res = BSP_LCD_H_RES,
            .v_res = BSP_LCD_V_RES,
            .hsync_pulse_width = 4,
            .hsync_back_porch = 8,
            .hsync_front_porch = 8,
            .vsync_pulse_width = 4,
            .vsync_back_porch = 8,
            .vsync_front_porch = 8,
            .flags = {
                .pclk_active_neg = 1,
            },
        },
        .data_width = 16,
        .bounce_buffer_size_px = 10 * BSP_LCD_H_RES,
        .hsync_gpio_num = BSP_LCD_HSYNC_PIN,
        .vsync_gpio_num = BSP_LCD_VSYNC_PIN,
        .de_gpio_num    = BSP_LCD_DE_PIN,
        .pclk_gpio_num  = BSP_LCD_PCLK_PIN,
        .disp_gpio_num  = -1,
        .data_gpio_nums = {
            BSP_LCD_DATA0_PIN,  BSP_LCD_DATA1_PIN,  BSP_LCD_DATA2_PIN,  BSP_LCD_DATA3_PIN,  BSP_LCD_DATA4_PIN,
            BSP_LCD_DATA5_PIN,  BSP_LCD_DATA6_PIN,  BSP_LCD_DATA7_PIN,  BSP_LCD_DATA8_PIN,  BSP_LCD_DATA9_PIN,  BSP_LCD_DATA10_PIN,
            BSP_LCD_DATA11_PIN, BSP_LCD_DATA12_PIN, BSP_LCD_DATA13_PIN, BSP_LCD_DATA14_PIN, BSP_LCD_DATA15_PIN,
        },
        .flags = {
            .fb_in_psram = 1,
        },
    };

    esp_err_t err = esp_lcd_new_rgb_panel(&panel_config, &s_panel_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Fallo al crear panel RGB: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_lcd_panel_reset(s_panel_handle);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Aviso en panel reset: %s", esp_err_to_name(err));
    }

    err = esp_lcd_panel_init(s_panel_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Fallo al inicializar panel RGB: %s", esp_err_to_name(err));
        return err;
    }

    if (out_panel_handle) {
        *out_panel_handle = s_panel_handle;
    }

    ESP_LOGI(TAG, "Panel LCD RGB inicializado correctamente (800x480, FB en PSRAM)");
    return ESP_OK;
}

esp_lcd_panel_handle_t bsp_display_get_panel_handle(void)
{
    return s_panel_handle;
}
