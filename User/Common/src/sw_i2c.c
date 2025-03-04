#include "sw_i2c.h"

#define ACK 0x0  // acknowledge (SDA LOW)
#define NACK 0x1 // not acknowledge (SDA HIGH)

#define LOW 0x0
#define HIGH 0x1

#define I2C_READ 0x1
#define I2C_WRITE 0x0
/***************************基础操作抽象层**************************/
static void HAL_SW_I2C_Start(sw_i2c_OO_t *i2c)
{
    i2c->sda_out(HIGH, i2c->user_data);
    i2c->scl_out(HIGH, i2c->user_data);
    i2c->sda_out(LOW, i2c->user_data);
    i2c->scl_out(LOW, i2c->user_data);
}

static void HAL_SW_I2C_Stop(sw_i2c_OO_t *i2c)
{
    i2c->sda_out(LOW, i2c->user_data);
    i2c->scl_out(HIGH, i2c->user_data);
    i2c->sda_out(HIGH, i2c->user_data);
}

/**
 * @brief 输出 sda 电平,然后 scl 输出一个时钟
 * @param i2c
 * @param bit bit level to send, 0:LOW, 1:HIGH
 */
static void HAL_SW_I2C_Write_Bit(sw_i2c_OO_t *i2c, uint8_t bit)
{
    i2c->sda_out(bit, i2c->user_data);
    i2c->scl_out(HIGH, i2c->user_data);
    i2c->scl_out(LOW, i2c->user_data);
}

/**
 * @brief 读 sda 电平值,然后 scl 输出一个时钟
 * @param i2c
 * @return 返回 SDA 电平值, 0:LOW, 1:HIGH
 */
static uint8_t HAL_SW_I2C_Read_Bit(sw_i2c_OO_t *i2c)
{
    uint8_t bit = 0;
    i2c->sda_out(HIGH, i2c->user_data);
    i2c->scl_out(HIGH, i2c->user_data);
    bit = i2c->sda_in(i2c->user_data);
    i2c->scl_out(LOW, i2c->user_data);
    return bit;
}

/**
 * @brief 向IIC输出一个字节
 * @param i2c
 * @param byte
 * @return 从设备反馈的 ACK 电平值
 */
static uint8_t HAL_SW_I2C_Write_Byte(sw_i2c_OO_t *i2c, uint8_t byte)
{
    uint8_t i = 0;
    uint8_t ack = 0;

    for (i = 0; i < 8; ++i)
    {
        HAL_SW_I2C_Write_Bit(i2c, byte & (0x80 >> i));
    }

    ack = HAL_SW_I2C_Read_Bit(i2c);
    return ack;
}

/**
 * @brief 从IIC总线上读取一个字节
 * @param i2c
 * @param ack 向从设备反馈 ACK 或者 NACK
 * @return 读取到的字节
 */
static uint8_t HAL_SW_I2C_Read_Byte(sw_i2c_OO_t *i2c, uint8_t ack)
{
    uint8_t byte = 0;
    uint8_t i = 0;

    i2c->sda_out(HIGH, i2c->user_data);
    for (i = 0; i < 8; ++i)
    {
        i2c->scl_out(HIGH, i2c->user_data);
        byte <<= 1;
        byte |= i2c->sda_in(i2c->user_data);
        i2c->scl_out(LOW, i2c->user_data);
    }

    HAL_SW_I2C_Write_Bit(i2c, ack);
    return byte;
}
/**************************应用层***************************/
/**
 * @brief 从IIC总线上的设备读取多个字节
 * @param i2c
 * @param dev_addr 从设备地址
 * @param[out] data 读取到的字节数组
 * @param data_length 读取大小(字节)
 * @return 0:成功, 1:错误
 */
uint8_t SW_I2C_Read(sw_i2c_OO_t *i2c, uint8_t addr, uint8_t *data, uint8_t data_length)
{
    uint8_t i = 0;
    uint8_t ack_bit = 0;

    /* 起始位 */
    HAL_SW_I2C_Start(i2c);

    /* 地址+读写位 */
    ack_bit = HAL_SW_I2C_Write_Byte(i2c, addr | I2C_READ);
    if (ack_bit)
    {
        /* 从设备没有回复ACK,直接退出 */
        HAL_SW_I2C_Stop(i2c);
        return 1;
    }

    /* 连续读取N-1个数据 给ACK */
    for (i = 0; i < data_length - 1; ++i)
    {
        data[i] = HAL_SW_I2C_Read_Byte(i2c, ACK);
    }

    /* 最后一个数据给 NACK */
    data[i] = HAL_SW_I2C_Read_Byte(i2c, NACK);

    /* 停止位 */
    HAL_SW_I2C_Stop(i2c);
    return 0;
}
/*
 * @brief 向IIC总线上的设备写入多个字节
 * @param i2c
 * @param dev_addr 从设备地址
 * @param data 写入的字节数组
 * @param data_length 写入大小(字节)
 * @return 0:成功, 1:错误
 */
uint8_t SW_I2C_Write(sw_i2c_OO_t *i2c, uint8_t addr, uint8_t *data, uint8_t data_length)
{
    uint8_t i = 0;
    uint8_t ack_bit = 0;

    /* 起始位 */
    HAL_SW_I2C_Start(i2c);

    /* 地址+读写位 */
    ack_bit = HAL_SW_I2C_Write_Byte(i2c, addr | I2C_WRITE);
    if (ack_bit)
    {
        /* 从设备没有回复ACK,直接退出 */
        HAL_SW_I2C_Stop(i2c);
        return 1;
    }

    /* 连续写入N个数据, 每次读取1 bit的 ACK */
    for (i = 0; i < data_length; ++i)
    {
        ack_bit = HAL_SW_I2C_Write_Byte(i2c, data[i]);
    }

    /* 停止位 */
    HAL_SW_I2C_Stop(i2c);
    return 0;
}
int8_t SW_I2C_Read_Byte(sw_i2c_OO_t *i2c, uint8_t dev_addr, uint8_t *data)
{
    return SW_I2C_Read(i2c, dev_addr, data, 1);
}

int8_t SW_I2C_Write_Byte(sw_i2c_OO_t *i2c, uint8_t dev_addr, uint8_t data)
{
    return SW_I2C_Write(i2c, dev_addr, &data, 1);
}
/*
 * @brief 从IIC总线上的设备读取寄存器
 * @param i2c
 * @param dev_addr 从设备地址
 * @param mem_addr 寄存器地址
 * @param[out] data 读取到的字节数组
 * @param data_length 读取大小(字节)
 * @return 0:成功, 1:错误
 */
uint8_t SW_I2C_Reg_Read(sw_i2c_OO_t *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t data_length)
{
    uint8_t ack_bit = 0;
    HAL_SW_I2C_Start(i2c);
    ack_bit = HAL_SW_I2C_Write_Byte(i2c, dev_addr | I2C_WRITE);
    if (ack_bit)
    {
        HAL_SW_I2C_Stop(i2c);
        return 1;
    }
    ack_bit = HAL_SW_I2C_Write_Byte(i2c, reg_addr);

    return SW_I2C_Read(i2c, dev_addr, data, data_length);
}
/*
 * @brief 向IIC总线上的设备写入寄存器
 * @param i2c
 * @param dev_addr 从设备地址
 * @param mem_addr 寄存器地址
 * @param data 写入的字节数组
 * @param data_length 写入大小(字节)
 * @return 0:成功, 1:错误
 */
uint8_t SW_I2C_Reg_Write(sw_i2c_OO_t *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t data_length)
{
    uint8_t ack_bit = 0;
    HAL_SW_I2C_Start(i2c);
    ack_bit = HAL_SW_I2C_Write_Byte(i2c, dev_addr | I2C_WRITE);
    if (ack_bit)
    {
        HAL_SW_I2C_Stop(i2c);
        return 1;
    }
    ack_bit = HAL_SW_I2C_Write_Byte(i2c, reg_addr);

    return SW_I2C_Write(i2c, dev_addr, data, data_length);
}
/***************************************************************************** */
/**
 * i2c地址扫描
 * @param scan_addr 扫描出来的地址存放
 * @return 返回扫描到的设备数量, 0为无设备发现
 */
uint8_t SW_I2C_Scan(sw_i2c_OO_t *i2c, uint8_t *scan_addr)
{
    int i = 0;
    uint8_t count = 0;
    uint8_t data = 0;
    int8_t ret = 0;

    for (i = 1; i < 127; ++i)
    {
        ret = SW_I2C_Read(i2c, i << 1, &data, 1);
        if (ret == 0)
        {
            scan_addr[count] = i << 1;
            ++count;
        }
    }

    return count;
}
