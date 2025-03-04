#ifndef __USER_GPIO_H
#define __USER_GPIO_H
#include "stm32f10x.h"
#include <stdbool.h>
#include <stdio.h>

#define PIN_0 GPIO_Pin_0
#define PIN_1 GPIO_Pin_1
#define PIN_2 GPIO_Pin_2
#define PIN_3 GPIO_Pin_3
#define PIN_4 GPIO_Pin_4
#define PIN_5 GPIO_Pin_5
#define PIN_6 GPIO_Pin_6
#define PIN_7 GPIO_Pin_7
#define PIN_8 GPIO_Pin_8
#define PIN_9 GPIO_Pin_9
#define PIN_10 GPIO_Pin_10
#define PIN_11 GPIO_Pin_11
#define PIN_12 GPIO_Pin_12
#define PIN_13 GPIO_Pin_13
#define PIN_14 GPIO_Pin_14
#define PIN_15 GPIO_Pin_15

#define MODE_AIN GPIO_Mode_AIN
#define MODE_INF GPIO_Mode_IN_FLOATING
#define MODE_IPD GPIO_Mode_IPD
#define MODE_IPU GPIO_Mode_IPU
#define MODE_OOD GPIO_Mode_Out_OD
#define MODE_OPP GPIO_Mode_Out_PP
#define MODE_AOD GPIO_Mode_AF_OD
#define MODE_APP GPIO_Mode_AF_PP

#define speed_10MHz GPIO_Speed_10MHz
#define speed_2MHz GPIO_Speed_2MHz
#define speed_50MHz GPIO_Speed_50MHz

#define GPIO_Source_Type uint8_t
#define Pin_x_Source_Type uint8_t

#define GPIOA_Src GPIO_PortSourceGPIOA
#define GPIOB_Src GPIO_PortSourceGPIOB
#define GPIOC_SSrc GPIO_PortSourceGPIOC
#define GPIOD_Src GPIO_PortSourceGPIOD
#define GPIOE_Src GPIO_PortSourceGPIOE
#define GPIOF_Src GPIO_PortSourceGPIOF
#define GPIOG_Src GPIO_PortSourceGPIOG

#define Pin_0_Src GPIO_PinSource0
#define Pin_1_Src GPIO_PinSource1
#define Pin_2_Src GPIO_PinSource2
#define Pin_3_Src GPIO_PinSource3
#define Pin_4_Src GPIO_PinSource4
#define Pin_5_Src GPIO_PinSource5
#define Pin_6_Src GPIO_PinSource6
#define Pin_7_Src GPIO_PinSource7
#define Pin_8_Src GPIO_PinSource8
#define Pin_9_Src GPIO_PinSource9
#define Pin_10_Src GPIO_PinSource10
#define Pin_11_Src GPIO_PinSource11
#define Pin_12_Src GPIO_PinSource12
#define Pin_13_Src GPIO_PinSource13
#define Pin_14_Src GPIO_PinSource14
#define Pin_15_Src GPIO_PinSource15

typedef struct
{
    GPIO_TypeDef * gpio_x;
    uint16_t pin_x;
    GPIOMode_TypeDef mode_x;
    GPIO_Source_Type gpio_x_src;
    Pin_x_Source_Type pin_x_src;
    bool invert;
} gpio_init_t;
void User_GPIO_All_Init(gpio_init_t gpio_group[], uint8_t num);
#endif
