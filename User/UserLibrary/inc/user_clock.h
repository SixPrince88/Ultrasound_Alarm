#ifndef __MY_CLOCK_H
#define __MY_CLOCK_H
#include "stm32f10x.h"
#define rcc_type uint32_t

#define AHB_DMA1 RCC_AHBPeriph_DMA1
#define AHB_DMA2 RCC_AHBPeriph_DMA2

#define APB1_TIM2 RCC_APB1Periph_TIM2
#define APB1_TIM3 RCC_APB1Periph_TIM3
#define APB1_TIM4 RCC_APB1Periph_TIM4
#define APB1_USART2 RCC_APB1Periph_USART2
#define APB1_USART3 RCC_APB1Periph_USART3
#define APB1_I2C1 RCC_APB1Periph_I2C1
#define APB1_I2C2 RCC_APB1Periph_I2C2
#define APB1_CAN1 RCC_APB1Periph_CAN1
#define APB1_CAN2 RCC_APB1Periph_CAN2
#define APB1_PWR RCC_APB1Periph_PWR

#define APB2_USART1 RCC_APB2Periph_USART1
#define APB2_TIM1 RCC_APB2Periph_TIM1
#define APB2_AFIO RCC_APB2Periph_AFIO
#define APB2_GPIOA RCC_APB2Periph_GPIOA
#define APB2_GPIOB RCC_APB2Periph_GPIOB
#define APB2_GPIOC RCC_APB2Periph_GPIOC
#define APB2_ADC1 RCC_APB2Periph_ADC1
#define APB2_ADC2 RCC_APB2Periph_ADC2



#endif
