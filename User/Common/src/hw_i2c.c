#include "hw_i2c.h"
void HW_I2C1_Init(void)
{
    gpio_init_t gpio_group = {
        .gpio_x = GPIOB,
        .pin_x = GPIO_Pin_6 | GPIO_Pin_7,
        .mode_x = GPIO_Mode_AF_OD,
    };
    User_GPIO_All_Init(&gpio_group, 1);
    I2C_InitTypeDef sys;
    I2C_StructInit(&sys);
    sys.I2C_Mode = I2C_Mode_I2C;
    sys.I2C_ClockSpeed = 100000;
    sys.I2C_DutyCycle = I2C_DutyCycle_2;
    sys.I2C_Ack = I2C_Ack_Enable;
    sys.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    sys.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C1, &sys);
    I2C_Cmd(I2C1, ENABLE);
}
uint8_t HW_I2C_Read(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t data_length)
{
    // 开始信号
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    // 发送地址
    I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;
    // 接收数据
    for (uint8_t i = 0; i < data_length; i++)
    {
        if (i == data_length - 1)
        {
            I2C_AcknowledgeConfig(I2Cx, DISABLE);
        }
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
            ;
        data[i] = I2C_ReceiveData(I2Cx);
    }
    // 结束信号
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return 0;
}
uint8_t HW_I2C_Write(I2C_TypeDef *I2Cx, uint8_t addr, const uint8_t *data, uint8_t data_length)
{
    // 开始信号
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    // 发送地址
    I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    // 发送数据
    for (uint8_t i = 0; i < data_length; i++)
    {
        I2C_SendData(I2Cx, data[i]);
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            ;
    }
    // 结束信号
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return 0;
}
int8_t HW_I2C_Read_Byte(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t *data)
{
    return HW_I2C_Read(I2Cx, dev_addr, data, 1);
}
int8_t HW_I2C_Write_Byte(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t data)
{
    return HW_I2C_Write(I2Cx, dev_addr, &data, 1);
}
uint8_t HW_I2C_Reg_Read(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint8_t data_length)
{
    // 开始信号
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    // 发送地址
    I2C_Send7bitAddress(I2Cx, dev_addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    // 发送寄存器地址
    I2C_SendData(I2Cx, mem_addr);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    // 重新开始信号
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    // 发送地址
    I2C_Send7bitAddress(I2Cx, dev_addr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;
    // 接收数据
    for (uint8_t i = 0; i < data_length; i++)
    {
        if (i == data_length - 1)
        {
            I2C_AcknowledgeConfig(I2Cx, DISABLE);
        }
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
            ;
        data[i] = I2C_ReceiveData(I2Cx);
    }
    // 结束信号
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return 0;
}
uint8_t HW_I2C_Reg_Write(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t mem_addr, const uint8_t *data, uint8_t data_length)
{
    // 开始信号
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    // 发送地址
    I2C_Send7bitAddress(I2Cx, dev_addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    // 发送寄存器地址
    I2C_SendData(I2Cx, mem_addr);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    // 发送数据
    for (uint8_t i = 0; i < data_length; i++)
    {
        I2C_SendData(I2Cx, data[i]);
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            ;
    }
    // 结束信号
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return 0;
}

uint8_t HW_I2C_Scan(I2C_TypeDef *I2Cx, uint8_t *scan_addr)
{
    int i;
    uint8_t count = 0;
    uint8_t data;
    int8_t ret;
    for (i = 1; i < 127; ++i)
    {
        ret = HW_I2C_Read(I2Cx, i << 1, &data, 1);
        if (ret == 0)
        {
            scan_addr[count] = i << 1;
            ++count;
        }
    }
    return count;
}
