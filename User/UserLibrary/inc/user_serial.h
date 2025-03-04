#ifndef __USER_SERIAL_H
#define __USER_SERIAL_H
#include "stm32f10x.h"
#include "user_gpio.h"
#include <stdarg.h>
#include <stdio.h>

#define MODE_RX USART_Mode_Rx
#define MODE_TX USART_Mode_Tx
#define MODE_RXTX USART_Mode_Rx | USART_Mode_Tx
typedef struct
{
	USART_TypeDef * usart_x;
	uint32_t baudrate;
	uint16_t mode_x;
} usart_init_t;

void User_Serial_Init(usart_init_t *usart);
void User_Serial_SendByte(USART_TypeDef *usart_x, uint8_t Byte);
void User_Serial_SendString(USART_TypeDef *usart_x, char *string);
void User_Serial_printf(USART_TypeDef *usart_x, char *format, ...);
void User_Serial_Test(USART_TypeDef *usartx);

#endif
