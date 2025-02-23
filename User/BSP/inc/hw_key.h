#ifndef __HW_KEY_H__
#define __HW_KEY_H__
#include "stm32f10x.h"
#include "user_gpio.h"
#include "hw_signal.h"
#include "hw_timestamp.h"
void HW_Key_Init(void);
uint8_t HW_Key_GetSingle(void);
void HW_Key_Scan(void);
uint16_t HW_key_GetDownTime(void);

#endif
