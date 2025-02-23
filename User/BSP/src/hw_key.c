#include "hw_key.h"
/*
 *@brief:按键初始化函数
 *@param:无
 *@retval:无
 */
void HW_Key_Init(void)
{
    gpio_init_t gpio = {
        .gpio_x = GPIOC,
        .pin_x = PIN_14 | PIN_15,
        .mode_x = MODE_IPU};
    User_GPIO_All_Init(&gpio, 1);
}
/*
 *@brief:获取单个按键状态，避免多个按键同时按下
 *@param:无
 *@retval:1-按键1按下，2-按键2按下，0-没有按下
 */
uint8_t HW_Key_GetSingle(void)
{
    if (!GPIO_ReadInputDataBit(GPIOC, PIN_14))
    {
        return 1;
    }
    else if (!GPIO_ReadInputDataBit(GPIOC, PIN_15))
    {
        return 2;
    }
    return 0; // 没有按下
}
/*
 *@brief:按键声音控制函数
 *@param:无
 */
uint8_t down_num = 0;
uint16_t down_time = 0;
/*
 *@brief:按键扫描函数，用于检测按键按下，并记录按键按下时间（需要配合定时器扫描）
 *@param:无
 *@retval:无
 */
void HW_Key_Scan(void)
{
    static uint8_t last_state = 0;
    uint8_t now_state = HW_Key_GetSingle();
    // 按钮按下
    if (now_state != 0 && last_state == 0)
    {
        down_num = now_state;
        down_time = 0;
        timestamp.beep = timestamp.count;
        // 按钮按下中
    }
    else if (now_state != 0 && last_state != 0)
    {
        down_time++;
        // 按钮松开
    }
    else if (now_state == 0 && last_state != 0)
    {
        down_num = -last_state;
    }
    // 保存上一次按键状态
    last_state = now_state;
    // 按键按下时间小于1s
    if (timestamp.beep != 0 && (timestamp.count - timestamp.beep < 50))
    {
        HW_Signal_On(BEEP);
    }
    else
    {
        HW_Signal_Off(BEEP);
    }
}
/*
 *@brief:获取按下的按键编号
 *@param:无
 *@retval:按键按下编号，0-没有按下，1-按键1按下，2-按键2按下
 */
uint8_t HW_Key_GetDown(void)
{
    if (down_num == 0)
    { // 没有按下
        return 0;
    }
    else
    {                           // 按键按下
        uint8_t ret = down_num; // 记录按键按下编号
        down_num = 0;           // 按键按下状态清零
        return ret;             // 返回按键按下编号
    }
}
/*
 *@brief:获取按键按下时间，单位为扫描按钮的时间（1ms），只在下一次按下时间清零
 *@param:无
 *@retval:按键按下时间
 */
uint16_t HW_Key_GetTime(void)
{
    return down_time;
}
