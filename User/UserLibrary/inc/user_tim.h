#ifndef __USER_TIM_H
#define __USER_TIM_H
#include "stm32f10x.h"
#define TIM_PSC uint16_t
#define TIM_ARR uint16_t
typedef struct
{
	TIM_TypeDef *tim_x;
	TIM_ARR arr_x;
	TIM_PSC psc_x;
} timbase_init_t;
typedef struct
{
	TIM_TypeDef * tim_x;
	int channel_x;
} oc_init_t;
enum ic_mode_type
{
	mode_ic,
	mode_pwmi,
};
typedef struct
{
	TIM_TypeDef *tim_x;
	int mode_x;
	uint16_t ic_channel_x;
} ic_init_t;

enum oc_channel_type
{
	OC_CHANNEL_1,
	OC_CHANNEL_2,
	OC_CHANNEL_3,
	OC_CHANNEL_4,
};
void User_TIM_Base_Init(timbase_init_t *tim);
void User_TIM_OC_All_Init(oc_init_t OCgroup[], char Num);
void User_TIM_IC_All_Init(ic_init_t ICgroup[], char num);
void User_TIM_Encoder_Init(TIM_TypeDef * timx);
#endif
