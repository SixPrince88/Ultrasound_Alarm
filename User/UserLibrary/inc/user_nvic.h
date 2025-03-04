#ifndef __USER_NVIC_H
#define __USER_NVIC_H
#include "stm32f10x.h"

#define NVIC_PriGourp_type uint32_t

typedef struct
{
	int channel_x;
	uint8_t pre_level;
	uint8_t sub_level;
} nvic_init_t;
void User_NVIC_All_Init(NVIC_PriGourp_type NVIC_PriGourp, nvic_init_t nvic_group[], char num);
#endif
