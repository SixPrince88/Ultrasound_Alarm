#include "user_i2c.h"
#include "user_gpio.h"
#include "user_delay.h"
static void sda_out(bool bit, void *user_data)
{
    i2c_init_t *sda_data = (i2c_init_t *)user_data;
    gpio_init_t sda_pin = {
        .gpio_x = sda_data->sda.gpio_x,
        .pin_x = sda_data->sda.pin_x,
        .mode_x = MODE_OOD};
    User_GPIO_All_Init(&sda_pin, 1);
    GPIO_WriteBit(sda_data->sda.gpio_x, sda_data->sda.pin_x, (BitAction)bit);
}

static uint8_t sda_in(void *user_data)
{
    i2c_init_t *sda_data = (i2c_init_t *)user_data;
    gpio_init_t sda_pin = {
        .gpio_x = sda_data->sda.gpio_x,
        .pin_x = sda_data->sda.pin_x,
        .mode_x = MODE_INF};
    User_GPIO_All_Init(&sda_pin, 1);
    return GPIO_ReadInputDataBit(sda_data->sda.gpio_x, sda_data->sda.pin_x);
}

static void scl_out(bool bit, void *user_data)
{
    i2c_init_t *scl_data = (i2c_init_t *)user_data;
    gpio_init_t scl_pin = {
        .gpio_x = scl_data->scl.gpio_x,
        .pin_x = scl_data->scl.pin_x,
        .mode_x = MODE_OOD};
    User_GPIO_All_Init(&scl_pin, 1);
    GPIO_WriteBit(scl_data->scl.gpio_x, scl_data->scl.pin_x, (BitAction)bit);
    if (scl_data->delay_us)
    {
        User_Delay_Us(scl_data->delay_us);
    }
}
// I2C1
i2c_init_t i2c1_gpio = {
    .scl.gpio_x = GPIOB,
    .scl.pin_x = PIN_6,
    .sda.gpio_x = GPIOB,
    .sda.pin_x = PIN_7,
    .delay_us = 5};

sw_i2c_OO_t sw_i2c1 = {
    .sda_in = sda_in,
    .scl_out = scl_out,
    .sda_out = sda_out,
    .user_data = (void *)&i2c1_gpio,
};

// I2C_OLED
i2c_init_t oled_gpio = {
    .scl.gpio_x = GPIOA,
    .scl.pin_x = PIN_12,
    .sda.gpio_x = GPIOA,
    .sda.pin_x = PIN_15,
    .delay_us = 0};

sw_i2c_OO_t sw_i2c_oled = {
    .sda_in = sda_in,
    .scl_out = scl_out,
    .sda_out = sda_out,
    .user_data = (void *)&oled_gpio,
};

sw_i2c_OO_t *sw_i2c1_ptr = &sw_i2c1;
sw_i2c_OO_t *sw_i2c_oled_ptr = &sw_i2c_oled;
