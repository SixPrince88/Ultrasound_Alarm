#ifndef __HW_USART_H
#define __HW_USART_H
#include "user_serial.h"
#include "hw_signal.h"
// #define USART_DEBUG USART1
#define MAX_RESEND_TIMES 3	   // 最大重发次数
#define ACK 0x01			   // ACK
typedef struct
{
	uint16_t head;
	uint16_t dist[6];
	uint16_t tail;
}tx_package;
void Serial_Send_Data(void);
void HW_Serial_Receive(void);
#endif
