#include "user_gpio.h"
/*
 *@function:GPIO初始化
 *@param:gpio_init_t *gpio
 *@return:void
 */
void User_GPIO_Init(gpio_init_t *gpio)
{
	GPIO_InitTypeDef sys;
	GPIO_StructInit(&sys);
	sys.GPIO_Mode = gpio->mode_x;
	sys.GPIO_Pin = gpio->pin_x;
	sys.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gpio->gpio_x, &sys);
	if (gpio->gpio_x_src)
	{
		GPIO_EXTILineConfig(gpio->gpio_x_src, gpio->pin_x_src);
	}
}
/*
 *@function:GPIO批量初始化
 *@param:gpio_init_t *gpio_group[],char num
 *@return:void
 */
void User_GPIO_All_Init(gpio_init_t gpio_group[], uint8_t num)
{
	for (uint8_t i = 0; i < num; i++)
	{
		if (gpio_group[i].gpio_x == 0)
			continue;
		User_GPIO_Init(&gpio_group[i]);
	}
}
