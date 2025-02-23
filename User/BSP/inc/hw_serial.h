#ifndef __HW_USART_H
#define __HW_USART_H
#include "user_serial.h"
#include "hw_signal.h"
typedef struct
{
	uint8_t cmd;
	uint8_t data1;
	uint8_t data2;
	uint16_t data3;
	uint32_t data4;
}user_package;
void HW_Serial_Package_Send(void);
uint8_t HW_Serial_GetRxFlag(void);
void HW_Serial_Package_Receive(void);
void HW_USART1_Control(void);
#endif
