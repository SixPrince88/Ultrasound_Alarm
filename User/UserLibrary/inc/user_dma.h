#ifndef __USER_DMA_H
#define __USER_DMA_H
#include "stm32f10x.h"
#define P2M DMA_DIR_PeripheralSRC
#define M2P DMA_DIR_PeripheralDST

#define M_Addr_Inc DMA_MemoryInc_Enable
#define M_No_Addr_Inc DMA_MemoryInc_Disable
#define M_Size_Byte DMA_MemoryDataSize_Byte
#define M_Size_HalfWord DMA_MemoryDataSize_HalfWord
#define M_Size_Word DMA_MemoryDataSize_Word

#define P_Addr_Inc DMA_PeripheralInc_Enable
#define P_No_Addr_Inc DMA_PeripheralInc_Disable
#define P_Size_Byte DMA_PeripheralDataSize_Byte
#define P_Size_HalfWord DMA_PeripheralDataSize_HalfWord
#define P_Size_Word DMA_PeripheralDataSize_Word

typedef struct
{
    DMA_Channel_TypeDef * channel_x;
    uint32_t buff_size;
    uint32_t direction;

    uint32_t m_addr;
    uint32_t m_inc_state;
    uint32_t m_data_size;

    uint32_t p_addr;
    uint32_t p_inc_state;
    uint32_t p_data_size;
} dma_init_t;
void User_DMA_Init(dma_init_t *dma);

#endif
