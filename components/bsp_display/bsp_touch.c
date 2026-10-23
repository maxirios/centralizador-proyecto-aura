#include "bsp_touch.h"
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "bsp_display.h"

static const char *TAG = "bsp_touch";

#define GT911_REG_CMD           0x8040
#define GT911_REG_CFG_VERSION   0x8047
#define GT911_REG_PRODUCT_ID    0x8140
#define GT911_REG_STATUS        0x814E
#define GT911_REG_POINT1        0x814F

#define BSP_TOUCH_INT_GPIO       GPIO_NUM_4
#define CH422G_I2C_ADDR_SET      0x24
#define CH422G_I2C_ADDR_IO       0x38

static uint8_t s_gt911_addr = BSP_TOUCH_GT911_ADDR_PRIM;
static bool s_touch_initialized = false;

static void gt911_hardware_reset(void)
{
    uint8_t set_cmd = 0x01;
    if (i2c_master_write_to_device(BSP_TOUCH_I2C_NUM, CH422G_I2C_ADDR_SET, &set_cmd, 1, pdMS_TO_TICKS(50)) != ESP_OK) {
        return;
    }

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BSP_TOUCH_INT_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    // 0x2C: TP_RST LOW, LCD_RST HIGH
    uint8_t write_buf = 0x2C;
    i2c_master_write_to_device(BSP_TOUCH_I2C_NUM, CH422G_I2C_ADDR_IO, &write_buf, 1, pdMS_TO_TICKS(50));
    vTaskDelay(pdMS_TO_TICKS(10));

    // INT en LOW para seleccionar direccion 0x5D
    gpio_set_level(BSP_TOUCH_INT_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(10));

    // 0x2E: TP_RST HIGH, LCD_RST HIGH
    write_buf = 0x2E;
    i2c_master_write_to_device(BSP_TOUCH_I2C_NUM, CH422G_I2C_ADDR_IO, &write_buf, 1, pdMS_TO_TICKS(50));
    vTaskDelay(pdMS_TO_TICKS(50));

    gpio_set_direction(BSP_TOUCH_INT_GPIO, GPIO_MODE_INPUT);
}

static esp_err_t gt911_read_reg(uint16_t reg, uint8_t *data, size_t len)
{
    uint8_t reg_buf[2] = { (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF) };
    return i2c_master_write_read_device(BSP_TOUCH_I2C_NUM, s_gt911_addr, reg_buf, 2, data, len, pdMS_TO_TICKS(50));
}

static esp_err_t gt911_write_reg(uint16_t reg, const uint8_t *data, size_t len)
{
    uint8_t buf[len + 2];
    buf[0] = (uint8_t)(reg >> 8);
    buf[1] = (uint8_t)(reg & 0xFF);
    if (len > 0 && data != NULL) {
        memcpy(&buf[2], data, len);
    }
    return i2c_master_write_to_device(BSP_TOUCH_I2C_NUM, s_gt911_addr, buf, len + 2, pdMS_TO_TICKS(50));
}

esp_err_t bsp_touch_init(void)
{
    ESP_LOGI(TAG, "Inicializando controlador tactil Goodix GT911 en I2C...");

    esp_err_t err = bsp_i2c_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error inicializando I2C para tactil: %s", esp_err_to_name(err));
        return err;
    }

    gt911_hardware_reset();

    uint8_t prod_id[4] = {0};
    s_gt911_addr = BSP_TOUCH_GT911_ADDR_PRIM;
    err = gt911_read_reg(GT911_REG_PRODUCT_ID, prod_id, 4);

    if (err != ESP_OK) {
        s_gt911_addr = BSP_TOUCH_GT911_ADDR_SEC;
        err = gt911_read_reg(GT911_REG_PRODUCT_ID, prod_id, 4);
    }

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Touch GT911 detectado en direccion 0x%02X (Product ID: %.4s)", s_gt911_addr, prod_id);
        s_touch_initialized = true;
    } else {
        ESP_LOGW(TAG, "No se detecto respuesta I2C del GT911 en 0x5D ni 0x14 (posible panel desconectado)");
        s_touch_initialized = false;
        return err;
    }

    return ESP_OK;
}

esp_err_t bsp_touch_read(bsp_touch_data_t *data)
{
    if (!data) {
        return ESP_ERR_INVALID_ARG;
    }
    memset(data, 0, sizeof(bsp_touch_data_t));

    if (!s_touch_initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    uint8_t status = 0;
    esp_err_t err = gt911_read_reg(GT911_REG_STATUS, &status, 1);
    if (err != ESP_OK) {
        return err;
    }

    bool buffer_ready = (status & 0x80) != 0;
    uint8_t touch_count = status & 0x0F;

    if (!buffer_ready || touch_count == 0) {
        uint8_t zero = 0;
        gt911_write_reg(GT911_REG_STATUS, &zero, 1);
        return ESP_OK;
    }

    uint8_t point_buf[7];
    err = gt911_read_reg(GT911_REG_POINT1, point_buf, sizeof(point_buf));
    uint8_t zero = 0;
    gt911_write_reg(GT911_REG_STATUS, &zero, 1);

    if (err != ESP_OK) {
        return err;
    }

    uint16_t raw_x = point_buf[1] | (point_buf[2] << 8);
    uint16_t raw_y = point_buf[3] | (point_buf[4] << 8);

    // Mapeo de ejes a orientacion vertical portrait (480x800):
    // Hardware nativo: 800 horizontal x 480 vertical.
    // Portrait: x = raw_y (0..479), y = (800 - 1 - raw_x) (0..799).
    uint16_t portrait_x = raw_y;
    uint16_t portrait_y = (BSP_LCD_H_RES > raw_x) ? (BSP_LCD_H_RES - 1 - raw_x) : 0;

    if (portrait_x >= BSP_LCD_PORTRAIT_WIDTH) {
        portrait_x = BSP_LCD_PORTRAIT_WIDTH - 1;
    }
    if (portrait_y >= BSP_LCD_PORTRAIT_HEIGHT) {
        portrait_y = BSP_LCD_PORTRAIT_HEIGHT - 1;
    }

    data->x = portrait_x;
    data->y = portrait_y;
    data->puntos = touch_count;
    data->presionado = true;

    return ESP_OK;
}
