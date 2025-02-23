#ifndef __HW_TIMESTAMP_H__
#define __HW_TIMESTAMP_H__
#include "stm32f10x.h"
#include "user_tim.h"
typedef struct timestamp_groupS
{
    uint32_t count;
    uint32_t beep;
}timestamp_t;
extern timestamp_t timestamp;
void HW_Timestamp_Init(void);

#endif
