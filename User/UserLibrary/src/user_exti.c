#include "user_exti.h"
/*
 *@brief  EXTI初始化
 *@param  exti_groupS exti
 *@retval None
 */
void User_EXTI_Init(exti_init_t *exti)
{
    EXTI_InitTypeDef sys;
    EXTI_StructInit(&sys);
    sys.EXTI_Line = exti->line_x;
    sys.EXTI_Mode = exti->mode_x;
    sys.EXTI_Trigger = exti->trig_x;
    sys.EXTI_LineCmd = ENABLE;
    EXTI_Init(&sys);
}
