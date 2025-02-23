#include "hw_signal.h"
/*
 *@brief 信号灯组
 *@param GPIOx 信号灯组对应的GPIOx
 *@param Pinx 信号灯组对应的引脚
 *@param Mode 信号灯组对应的模式
 *@retval None
 */
gpio_init_t signal_gpio[] = {
    {.gpio_x = GPIOC, .pin_x = PIN_13, .mode_x = MODE_OPP},
};

/*
 *@brief 信号组拉高
 *@param target 信号组控制目标
 *@retval None
 */
void HW_Signal_On(signals target)
{
    for (int i = 0; i < sizeof(signal_gpio) / sizeof(signal_gpio[0]); i++)
    {
        if ((target & (1 << i)) != 0)
        {
            if(signal_gpio[i].invert==false){
                GPIO_SetBits(signal_gpio[i].gpio_x, signal_gpio[i].pin_x);
            }
            else{
                GPIO_ResetBits(signal_gpio[i].gpio_x, signal_gpio[i].pin_x);
            }
        }
    }
}
/*
 *@brief 信号组拉低
 *@param target 信号组控制目标
 *@retval None
 */
void HW_Signal_Off(signals target)
{
    for (int i = 0; i < sizeof(signal_gpio) / sizeof(signal_gpio[0]); i++)
    {
        if ((target & (1 << i)) != 0)
        {
            if(signal_gpio[i].invert==false){
                GPIO_ResetBits(signal_gpio[i].gpio_x, signal_gpio[i].pin_x);
            }
            else{
                GPIO_SetBits(signal_gpio[i].gpio_x, signal_gpio[i].pin_x);
            }
        }
    }
}
/*
 *@brief 信号组翻转
 *@param target 信号组控制目标
 *@retval None
 */
void HW_Signal_Toggle(signals target)
{
    for (int i = 0; i < sizeof(signal_gpio) / sizeof(signal_gpio[0]); i++)
    {
        if ((target & (1 << i)) != 0)
        {
            GPIO_WriteBit(signal_gpio[i].gpio_x, signal_gpio[i].pin_x, (BitAction)!GPIO_ReadOutputDataBit(signal_gpio[i].gpio_x, signal_gpio[i].pin_x));
        }
    }
}
void HW_Signal_Init(void)
{
    User_GPIO_All_Init(signal_gpio, sizeof(signal_gpio) / sizeof(signal_gpio[0]));
    HW_Signal_Off(SIGNAL_ALL);
}
