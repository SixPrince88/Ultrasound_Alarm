#include "user_nvic.h"
/*
 *@brief:初始化NVIC
 *@param:nvic_groupS nvic
 *@retval:无
 */
void User_NVIC_Init(nvic_init_t *nvic)
{
	NVIC_InitTypeDef sys;
	sys.NVIC_IRQChannel = nvic->channel_x;
	sys.NVIC_IRQChannelCmd = ENABLE;
	sys.NVIC_IRQChannelPreemptionPriority = nvic->pre_level;
	sys.NVIC_IRQChannelSubPriority = nvic->sub_level;
	NVIC_Init(&sys);
}
/*
 *@brief:初始化所有NVIC
 *@param:无
 *@retval:无
 */
void User_NVIC_All_Init(NVIC_PriGourp_type NVIC_PriGourp, nvic_init_t nvic_group[], char num)
{
	NVIC_PriorityGroupConfig(NVIC_PriGourp);
	for (int i = 0; i < num; i++)
	{
		if ((nvic_group[i].channel_x) == 0)
			continue;
		User_NVIC_Init(&nvic_group[i]);
	}
}
