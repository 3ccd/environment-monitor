//
// Created by chihiro on 2024/09/23.
//

#include <stdio.h>
#include <pico/stdio.h>
#include <hardware/i2c.h>
#include <hardware/gpio.h>

#include "bme280_i2c.h"
#include "st7789.h"
#include "graphics.h"

#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

#define SPI_SCK_PIN 18
#define SPI_MOSI_PIN 19
#define SPI_MISO_PIN 16
#define SPI_CS_PIN 17
#define LCD_DS_PIN 21
#define LCD_RST_PIN 20
#define LCD_BL_PIN 22

void main(void) {
    stdio_init_all();

    const bme280_config sensor_config = {
        i2c0,
        I2C_SDA_PIN,
        I2C_SCL_PIN
    };

    const st7789_config lcd_config = {
        spi0,
        SPI_MOSI_PIN,
        SPI_SCK_PIN,
        SPI_CS_PIN,
        LCD_DS_PIN,
        LCD_RST_PIN,
        LCD_BL_PIN
    };

    // configure modules
    bme280_init(&sensor_config);
    lv_port_disp_init(&lcd_config);

    // retrieve fixed compensation params
    bme280_calib_param params;
    bme280_get_calib_params(&params);

    int32_t raw_temperature;
    int32_t raw_pressure;

    sleep_ms(250); // sleep so that data polling and register update don't collide

    /*Change the active screen's background color*/
    //lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    //lv_obj_t * label = lv_label_create(lv_screen_active());
    //lv_label_set_text(label, "Hello world");
    //lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    //lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    while (1) {
        //st7789_fill(0xFF00);

        bme280_read_raw(&raw_temperature, &raw_pressure);
        int32_t temperature = bme280_convert_temp(raw_temperature, &params);
        int32_t pressure = bme280_convert_pressure(raw_pressure, raw_temperature, &params);
        printf("Pressure = %.3f kPa\n", pressure / 1000.f);
        printf("Temp. = %.2f C\n", temperature / 100.f);
        // poll every 500ms
        sleep_ms(500);
    }

}
