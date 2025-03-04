/*
 * 通用软件IIC使用方式
 * 1.首先需要定义三个函数
 *
 * 根据bit=0 或者bit=1 在SDA阵脚输出对应的电平，然后根据自己需要的IIC频率delay N us
 * void sda_out(uint8_t bit, void *user_data)
 *
 * 读取SDA电平值然后返回低电平0 或者是高电平1，然后根据自己需要的IIC频率delay N us
 * uint8_t sda_in(void *user_data)
 *
 * 根据bit=0 或者bit=1 在SCL阵脚输出对应的电平，然后根据自己需要的IIC频率delay N us
 * void scl_out(uint8_t bit, void *user_data)
 *
 * 2. 把上面定义的函数 塞进 sw_i2c_OO_t
 * 3. 然后就可以把 sw_i2c_OO_t 传给函数使用了
 */
#ifndef __SW_I2C_H__
#define __SW_I2C_H__

#include "stdint.h"
#include "stdbool.h"

typedef struct
{
    void (*sda_out)(bool bit, void *user_data);
    uint8_t (*sda_in)(void *user_data);
    void (*scl_out)(bool bit, void *user_data);
    void *user_data;
} sw_i2c_OO_t;

uint8_t SW_I2C_Scan(sw_i2c_OO_t *i2c_group, uint8_t *scan_addr);

uint8_t SW_I2C_Read(sw_i2c_OO_t *i2c_group, uint8_t addr, uint8_t *data, uint8_t data_length);
uint8_t SW_I2C_Write(sw_i2c_OO_t *i2c_group, uint8_t addr, uint8_t *data, uint8_t data_length);

int8_t SW_I2C_Read_Byte(sw_i2c_OO_t* i2c,uint8_t dev_addr, uint8_t* data);
int8_t SW_I2C_Write_Byte(sw_i2c_OO_t* i2c, uint8_t dev_addr, uint8_t data);

uint8_t SW_I2C_Reg_Read(sw_i2c_OO_t *i2c_group, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t data_length);
uint8_t SW_I2C_Reg_Write(sw_i2c_OO_t *i2c_group, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t data_length);

#endif // __SW_I2C_H__
