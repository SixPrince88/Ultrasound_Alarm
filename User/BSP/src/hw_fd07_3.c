#include "hw_fd07_3.h"
gpio_init_t fd07_3_pin_E = {.gpio_x = GPIOB, .pin_x = PIN_4, .mode_x = MODE_OPP};
gpio_init_t fd07_3_pin_T[FD07_3_NUM] = {
    {.gpio_x = GPIOB, .pin_x = PIN_10, .mode_x = MODE_INF, .gpio_x_src = GPIOB_Src, .pin_x_src = Pin_10_Src},
    {.gpio_x = GPIOB, .pin_x = PIN_11, .mode_x = MODE_INF, .gpio_x_src = GPIOB_Src, .pin_x_src = Pin_11_Src},
    {.gpio_x = GPIOB, .pin_x = PIN_12, .mode_x = MODE_INF, .gpio_x_src = GPIOB_Src, .pin_x_src = Pin_12_Src},
    //	{.gpio_x = GPIOB, .pin_x = PIN_13, .mode_x = MODE_INF, .gpio_x_src = GPIOB_Src, .pin_x_src = Pin_13_Src},
    //	{.gpio_x = GPIOB, .pin_x = PIN_14, .mode_x = MODE_INF, .gpio_x_src = GPIOB_Src, .pin_x_src = Pin_14_Src},
    //	{.gpio_x = GPIOB, .pin_x = PIN_15, .mode_x = MODE_INF, .gpio_x_src = GPIOB_Src, .pin_x_src = Pin_15_Src}
};
uint8_t fd07_3_updateflag = 0x00;                                  // 传感器数据更新标志
uint32_t fd07_3_start_time[FD07_3_NUM] = {0};                      // 传感器启动时间
uint32_t fd07_3_end_time[FD07_3_NUM] = {0};                        // 传感器结束时间
uint16_t fd07_3_dist_buffer[FD07_3_NUM][FD07_3_BUFFER_SIZE] = {0}; // 传感器数据缓存
uint8_t fd07_3_buffer_index = 0;                                   // 传感器数据缓存索引
uint16_t fd07_3_dist[FD07_3_MAX_NUM] = {0};                        // 传感器距离
void HW_FD07_3_Init(void)
{
    User_GPIO_All_Init(&fd07_3_pin_E, 1);
    User_GPIO_All_Init(fd07_3_pin_T, sizeof(fd07_3_pin_T) / sizeof(fd07_3_pin_T[0]));

    timbase_init_t tim = {.tim_x = TIM3, .arr_x = 65535, .psc_x = 7200 - 1};
    User_TIM_Base_Init(&tim);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_InternalClockConfig(TIM3);
    TIM_Cmd(TIM3, ENABLE);

    exti_init_t exti = {
        .line_x = EXTI_Line10 | EXTI_Line11 | EXTI_Line12, //| EXTI_Line13 | EXTI_Line14 | EXTI_Line15,
        .mode_x = Mode_IT,
        .trig_x = Trig_Double};
    User_EXTI_Init(&exti);
}

void FD07_3_Start(void)
{
    GPIO_ResetBits(fd07_3_pin_E.gpio_x, fd07_3_pin_E.pin_x);
    User_Delay_Ms(1);
    GPIO_SetBits(fd07_3_pin_E.gpio_x, fd07_3_pin_E.pin_x);
}
uint8_t FD07_3_Get_Dist(void)
{
    for (uint8_t i = 0; i < FD07_3_NUM; i++)
    {
        fd07_3_dist_buffer[i][fd07_3_buffer_index] = (uint16_t)(fd07_3_end_time[i] - fd07_3_start_time[i]) * 17;
    }
    fd07_3_buffer_index++;
    if (fd07_3_buffer_index == FD07_3_BUFFER_SIZE)
    {
        fd07_3_buffer_index = 0;
        for (uint8_t i = 0; i < FD07_3_NUM; i++)
        {
            fd07_3_dist[i] = Find_Median(fd07_3_dist_buffer[i], FD07_3_BUFFER_SIZE);
        }
        return 1;
    }
    else{
        return 0;
    }
}
int8_t FD07_3_Get_ITNum(void)
{
    for (uint8_t i = 0; i < FD07_3_NUM; i++)
    {
        if (EXTI_GetITStatus(EXTI_Line10 << i) != RESET)
        {
            return i;
        }
    }
    return -1;
}
void EXTI15_10_IRQHandler(void)
{
    int8_t itnum = FD07_3_Get_ITNum();
    if (itnum != -1)
    {
        EXTI_ClearITPendingBit(EXTI_Line10 << itnum);
        if (GPIO_ReadInputDataBit(fd07_3_pin_T[itnum].gpio_x, fd07_3_pin_T[itnum].pin_x) == SET)
        {
            fd07_3_start_time[itnum] = TIM_GetCounter(TIM3);
        }
        else
        {
            fd07_3_end_time[itnum] = TIM_GetCounter(TIM3);
            fd07_3_updateflag |= (1 << itnum);
        }
    }
}
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_FLAG_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
    }
}
