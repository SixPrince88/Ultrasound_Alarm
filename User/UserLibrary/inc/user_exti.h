#ifndef __USER_EXTI_H
#define __USER_EXTI_H
#include "stm32f10x.h"
#include "user_gpio.h"
#define Line0 EXTI_Line_0
#define Line1 EXTI_Line_1
#define Line2 EXTI_Line_2
#define Line3 EXTI_Line_3
#define Line4 EXTI_Line_4
#define Line5 EXTI_Line_5
#define Line6 EXTI_Line_6
#define Line7 EXTI_Line_7
#define Line8 EXTI_Line_8
#define Line9 EXTI_Line_9
#define Line10 EXTI_Line_10
#define Line11 EXTI_Line_11
#define Line12 EXTI_Line_12
#define Line13 EXTI_Line_13
#define Line14 EXTI_Line_14
#define Line15 EXTI_Line_15
#define Line16 EXTI_Line_16
#define Line17 EXTI_Line_17
#define Line18 EXTI_Line_18
#define Line19 EXTI_Line_19

#define Mode_IT EXTI_Mode_Interrupt
#define Mode_Event EXTI_Mode_Event

#define Trig_Rise EXTI_Trigger_Rising
#define Trig_Fall EXTI_Trigger_Falling
#define Trig_Double EXTI_Trigger_Rising_Falling

typedef struct
{
    uint32_t line_x;
    EXTIMode_TypeDef mode_x;
    EXTITrigger_TypeDef trig_x;
} exti_init_t;

void User_EXTI_Init(exti_init_t *exti);

#endif
