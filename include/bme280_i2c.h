//
// Created by chihiro on 2024/09/23.
//

#ifndef BME280_I2C_H
#define BME280_I2C_H

#include <hardware/i2c.h>

typedef struct {
    i2c_inst_t* i2c;
    uint gpio_sda;
    uint gpio_sck;
} bme280_config;

typedef struct {
    // temperature params
    uint16_t dig_t1;
    int16_t dig_t2;
    int16_t dig_t3;

    // pressure params
    uint16_t dig_p1;
    int16_t dig_p2;
    int16_t dig_p3;
    int16_t dig_p4;
    int16_t dig_p5;
    int16_t dig_p6;
    int16_t dig_p7;
    int16_t dig_p8;
    int16_t dig_p9;
} bme280_calib_param;

void bme280_init(const bme280_config *config);
void bme280_get_calib_params(bme280_calib_param* params);
void bme280_read_raw(int32_t* temp, int32_t* pressure);
int32_t bme280_convert_temp(int32_t temp, bme280_calib_param* params);
int32_t bme280_convert_pressure(int32_t pressure, int32_t temp, bme280_calib_param* params);

#endif //BME280_I2C_H
