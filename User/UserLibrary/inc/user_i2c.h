#ifndef __USER_I2C_H__
#define __USER_I2C_H__
/*
 * i2c 库
 * thebszk 2024/7/24
 */

#include "stm32f10x.h"
#include "sw_i2c.h"
#include "hw_i2c.h"
#include "user_gpio.h"

typedef struct
{
    gpio_init_t sda;
    gpio_init_t scl;
    uint32_t delay_us;
} i2c_init_t;

extern sw_i2c_OO_t *sw_i2c1_ptr;
extern sw_i2c_OO_t *sw_i2c_oled_ptr;

#endif //__I2C_H__
