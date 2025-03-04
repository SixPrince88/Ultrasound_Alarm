#ifndef __HW_SIGNALS_H__
#define __HW_SIGNALS_H__
#include "stm32f10x.h"
#include "user_gpio.h"
#include "user_delay.h"
typedef enum {
    BEEP = 1,
    ALARM_TURN_LEFT=2,
    ALARM_FORWARD=4,
    ALARM_DINGDING=8,
    ALARM_TURN_RIGHT=16,
    SIGNAL_ALL= 0xFF
}signals;

void HW_Signal_Init(void);
void HW_Signal_On(signals target);
void HW_Signal_Off(signals target);
void HW_Signal_Toggle(signals target);
void Alarm_Start(uint8_t rx_data);
#endif
