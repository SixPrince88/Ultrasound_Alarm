#include "user_serial.h"
/*
 *@brief:usart初始化
 *@param:usartGroupS usart
 *@return:void
 */
void User_Serial_Init(usart_init_t *usart)
{
	USART_InitTypeDef sys;
	sys.USART_BaudRate = usart->baudrate;
	sys.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	sys.USART_Mode = usart->mode_x;
	sys.USART_Parity = USART_Parity_No;
	sys.USART_StopBits = USART_StopBits_1;
	sys.USART_WordLength = USART_WordLength_8b;
	USART_Init(usart->usart_x, &sys);
	USART_ITConfig(usart->usart_x, USART_IT_RXNE, ENABLE);
	USART_Cmd(usart->usart_x, ENABLE);
}
/*
 *@brief:发送一个字节
 *@param:usart_type usart
 *@param:char Byte
 *@return:void
 */
void User_Serial_SendByte(USART_TypeDef *usart_x, uint8_t Byte)
{
	USART_SendData(usart_x, Byte); // 填充数据至 USART3的DR寄存器

	// USART_FLAG_TXE: 发送寄存器为空标志位。对USART_DR的写操作时，将该位清零。
  	while (USART_GetFlagStatus(usart_x, USART_FLAG_TXE) == RESET)
		; // 等待发送完成
}
/*
 *@brief:发送字符串
 *@param:usart_type usart
 *@param:char* string
 *@return:void
 */
void User_Serial_SendString(USART_TypeDef *usart_x, char *string)
{
	uint8_t i = 0;
	for (i = 0; string[i] != '\0'; i++)
	{
		User_Serial_SendByte(usart_x, string[i]);
	}
}
/*
 *@brief:重定向printf函数
 *@param:int ch
 *@param:FILE *f
 *@return:int
 */
/*
int fputc(int ch, FILE *f)
{
	User_Serial_SendByte(USART_DEBUG, ch);
	while (USART_GetFlagStatus(USART_DEBUG, USART_FLAG_TXE) == RESET)
		; // 等待发送完成
	return ch;
}
*/
/*
 *@brief:重定向fgetc函数
 *@param:FILE *f
 *@return:int
 */
/*
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART_DEBUG, USART_FLAG_RXNE) == RESET)
		;
	return USART_ReceiveData(USART_DEBUG);
}
*/
/*
 *@brief:打印格式化字符串
 *@param:usart_type usart
 *@param:serial_data_groupS *data
 *@return:void
 */
void User_Serial_printf(USART_TypeDef *usart_x, char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	User_Serial_SendString(usart_x, String);
}
/*
 *@brief:串口测试
 *@param:usart_type usart
 *@return:void
 */
void User_Serial_Test(USART_TypeDef *usartx)
{
	uint8_t rx_data = USART_ReceiveData(usartx);
	User_Serial_SendByte(usartx, rx_data);
}