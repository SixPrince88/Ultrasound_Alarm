#include "hw_timestamp.h"
timestamp_t timestamp = {0}; // 时间戳组
void HW_Timestamp_Init(void)
{
    timbase_init_t tim_group = {
        .tim_x = TIM4,
        .arr_x = 1000 - 1,
        .psc_x = 72 - 1};
    User_TIM_Base_Init(&tim_group);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        timestamp.count++;
    }
}

