#include "user_delay.h"

void User_Delay_Us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;	// 设置定时器重装值
	SysTick->VAL = 0x00;		// 清空当前计数值
	SysTick->CTRL = 0x00000005; // 设置时钟源为HCLK，启动定时器
	while (!(SysTick->CTRL & 0x00010000))
		;						// 等待计数到0
	SysTick->CTRL = 0x00000004; // 关闭定时器
}

void User_Delay_Ms(uint32_t xms)
{
	while (xms--)
	{
		User_Delay_Us(1000);
	}
}

void User_Delay_S(uint32_t xs)
{
	while (xs--)
	{
		User_Delay_Us(1000);
	}
}
