#ifndef __HW_OLED_H
#define __HW_OLED_H
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "hw_oled_data.h"
#include "user_gpio.h"
#include "user_delay.h"
/*参数宏定义*********************/

/*FontSize参数取值*/
/*此参数值不仅用于判断，而且用于计算横向字符偏移，默认值为字体像素宽度*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled参数数值*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*********************参数宏定义*/
/*I2C引脚配置*********************/
#define OLED_W_SCL(bit) GPIO_WriteBit(GPIOA, PIN_12, (BitAction)bit)// OLED写SCL高低电平,单片机主频过高需要加延时
#define OLED_W_SDA(bit) GPIO_WriteBit(GPIOA, PIN_15, (BitAction)bit) // OLED写SDA高低电平
/*SPI引脚配置*********************/
#define OLED_W_D0(bit) GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)bit)//OLED写D0（CLK）高低电平
#define OLED_W_D1(bit) GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)bit)//OLED写D1（MOSI）高低电平
#define OLED_W_RES(bit) GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)bit)//OLED写RES（RST）高低电平
#define OLED_W_DC(bit) GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)bit)//OLED写DC（DC）高低电平
#define OLED_W_CS(bit) GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)bit)//OLED写CS（CS）高低电平
/*通信方式选择*********************/
#define OLED_GPIO_Init HW_OLED_I2C_Init
#define OLED_WriteCommand OLED_I2C_WriteCommand
#define OLED_WriteData OLED_I2C_WriteData
/*函数声明*********************/

/*初始化函数*/
void HW_OLED_Init(void);

/*更新函数*/
void OLED_Update(void);
void OLED_UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*显存控制函数*/
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*显示函数*/
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);

/*绘图函数*/
void OLED_DrawPoint(int16_t X, int16_t Y);
uint8_t OLED_GetPoint(int16_t X, int16_t Y);
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
void OLED_DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

/*********************函数声明*/
void HW_OLED_Show(void);
#endif


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
