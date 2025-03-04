#include "hw_serial.h"
#include "hw_fd07_3.h"
tx_package tx_buffer = {0}; // 发送缓冲区
bool fd07_3_send_flag;		// 发送标志位
static uint8_t rx_cmd = 0;
static bool resend_flag = true;				 // 重发标志位
static uint8_t resend_times = 0;			 // 重发次数
extern uint16_t fd07_3_dist[FD07_3_MAX_NUM]; // 距离数组

void Serial_Send_Data(void)
{
	tx_buffer.head = 0x8888;
	tx_buffer.tail = 0x7777;
	memcpy(tx_buffer.dist, fd07_3_dist, sizeof(fd07_3_dist));
	do
	{
		if (resend_times++ > 2)
		{
			resend_flag = false;
			resend_times = 0;
			return;
		}
		else
		{
			User_Delay_Ms(100); // 等待100ms后重发
		}
		uint8_t *tx_data_offset = (uint8_t *)&tx_buffer;
		// 发送数据
		for (uint8_t i = 0; i < sizeof(tx_buffer); i++)
		{
			User_Serial_SendByte(USART1, *(tx_data_offset++));
		}
		resend_flag = true;
		User_Delay_Ms(1);
	} while (resend_flag);
}
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // 如果接收到数据
	{
		rx_cmd = USART_ReceiveData(USART1); // 读取接收到的数据
		if (rx_cmd == ACK)
		{
			resend_flag = false;
			resend_times = 0;
		}
	}
}
void HW_Serial_Receive(void)
{
	switch (rx_cmd)
	{
	case 'Y':
		fd07_3_send_flag = true; // 数据发送开始
		break;
	case 'N':
		fd07_3_send_flag = false; // 数据发送结束
		break;
	case 'A':
		HW_Signal_On(ALARM_TURN_LEFT); // 左转警报开启
		break;
	case 'a':
		HW_Signal_Off(ALARM_TURN_LEFT); // 左转警报关闭
		break;
	case 'B':
		HW_Signal_On(ALARM_FORWARD); // 前进警报开启
		break;
	case 'b':
		HW_Signal_Off(ALARM_FORWARD); // 前进警报关闭
		break;
	case 'C':
		HW_Signal_On(ALARM_DINGDING); // 叮叮警报开启
		break;
	case 'c':
		HW_Signal_Off(ALARM_DINGDING); // 叮叮警报关闭
		break;
	case 'D':
		HW_Signal_On(ALARM_TURN_RIGHT); // 右转警报开启
		break;
	case 'd':
		HW_Signal_Off(ALARM_TURN_RIGHT); // 右转警报关闭
		break;
	}
	User_Serial_SendByte(USART1, ACK); // 接收到指令后发送应答位
}