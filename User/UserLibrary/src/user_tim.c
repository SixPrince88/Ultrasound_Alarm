#include "user_tim.h"
/*
 *@brief:定时器初始化
 *@param:timBaseGroupS tim[] 定时器组
 *@param:char Num 定时器组个数
 *@retval:void
 */
void User_TIM_Base_Init(timbase_init_t *tim)
{
	TIM_TimeBaseInitTypeDef sys;
	TIM_TimeBaseStructInit(&sys);
	sys.TIM_ClockDivision = TIM_CKD_DIV1;
	sys.TIM_CounterMode = TIM_CounterMode_Up;
	sys.TIM_Period = tim->arr_x;
	sys.TIM_Prescaler = tim->psc_x;
	sys.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(tim->tim_x, &sys);
}
void User_TIM_OC_Init(oc_init_t *OC)
{
	TIM_OCInitTypeDef sys;
	TIM_OCStructInit(&sys);
	sys.TIM_OCMode = TIM_OCMode_PWM1;
	sys.TIM_OutputState = TIM_OutputState_Enable;
	sys.TIM_OCPolarity = TIM_OCPolarity_High;
	sys.TIM_Pulse = 0;
	// 初始化指定通道的输出比较
	switch (OC->channel_x)
	{
	case OC_CHANNEL_1:
		TIM_OC1Init(OC->tim_x, &sys);
		break;
	case OC_CHANNEL_2:
		TIM_OC2Init(OC->tim_x, &sys);
		break;
	case OC_CHANNEL_3:
		TIM_OC3Init(OC->tim_x, &sys);
		break;
	case OC_CHANNEL_4:
		TIM_OC4Init(OC->tim_x, &sys);
		break;
	}
	// 如果是TIM1，则进行额外的配置
	if (OC->tim_x == TIM1)
	{
		TIM_CtrlPWMOutputs(OC->tim_x, ENABLE);
		// 启用指定通道的预装载
		switch (OC->channel_x)
		{
		case OC_CHANNEL_1:
			TIM_OC1PreloadConfig(OC->tim_x, TIM_OCPreload_Enable);
			break;
		case OC_CHANNEL_2:
			TIM_OC2PreloadConfig(OC->tim_x, TIM_OCPreload_Enable);
			break;
		case OC_CHANNEL_3:
			TIM_OC3PreloadConfig(OC->tim_x, TIM_OCPreload_Enable);
			break;
		case OC_CHANNEL_4:
			TIM_OC4PreloadConfig(OC->tim_x, TIM_OCPreload_Enable);
			break;
		}
		TIM_ARRPreloadConfig(OC->tim_x, ENABLE);
	}
	// 启动定时器
	TIM_Cmd(OC->tim_x, ENABLE);
}
void User_TIM_OC_All_Init(oc_init_t OCgroup[], char Num)
{
	for (int i = 0; i < Num; i++)
	{
		if (OCgroup[i].tim_x == 0)
			continue;
		User_TIM_OC_Init(&OCgroup[i]);
	}
}
void User_TIM_IC_Init(ic_init_t *IC)
{
	TIM_ICInitTypeDef sys;
	TIM_ICStructInit(&sys);
	sys.TIM_ICFilter = 10;
	sys.TIM_Channel = IC->ic_channel_x;
	sys.TIM_ICPolarity = TIM_ICPolarity_Rising;
	sys.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	sys.TIM_ICSelection = TIM_ICSelection_DirectTI;
	if (IC->mode_x == mode_ic)
		TIM_ICInit(IC->tim_x, &sys);
	if (IC->mode_x == mode_pwmi)
		TIM_PWMIConfig(IC->tim_x, &sys);
	TIM_SelectInputTrigger(IC->tim_x, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(IC->tim_x, TIM_SlaveMode_Reset);
	TIM_Cmd(IC->tim_x, ENABLE);
}
void User_TIM_IC_All_Init(ic_init_t ICgroup[], char num)
{
	for (int i = 0; i < num; i++)
	{
		if (ICgroup[i].tim_x == 0)
			continue;
		User_TIM_IC_Init(&ICgroup[i]);
	}
}
void User_TIM_Encoder_Init(TIM_TypeDef *timx)
{
	// 编码器初始化
	TIM_EncoderInterfaceConfig(timx, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	// 滤波器初始化
	TIM_ICInitTypeDef sys;
	TIM_ICStructInit(&sys);
	sys.TIM_ICFilter = 10;
	TIM_ICInit(timx, &sys);
	// 启动定时器
	TIM_ClearFlag(timx, TIM_FLAG_Update);
	TIM_ITConfig(timx, TIM_IT_Update, ENABLE);
	TIM_SetCounter(timx, 0);
	TIM_Cmd(timx, ENABLE);
}
