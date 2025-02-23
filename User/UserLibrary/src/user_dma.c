#include "user_dma.h"
/*
 *@brief:DMA初始化函数
 *@param:DMA组结构体
 *@retval:无
 */
void User_DMA_Init(dma_init_t *dma)
{
	DMA_DeInit(dma->channel_x);
	DMA_InitTypeDef sys;
	sys.DMA_BufferSize = dma->buff_size; // DMA缓冲区大小

	sys.DMA_DIR = dma->direction; // DMA传输方向

	sys.DMA_MemoryBaseAddr = dma->m_addr; // DMA内存地址

	sys.DMA_MemoryInc = dma->m_inc_state; // DMA内存地址自增

	sys.DMA_MemoryDataSize = dma->m_data_size; // DMA内存数据大小

	sys.DMA_PeripheralBaseAddr = dma->p_addr; // DMA外设地址

	sys.DMA_PeripheralInc = dma->p_inc_state; // DMA外设地址自增

	sys.DMA_PeripheralDataSize = dma->p_data_size; // DMA外设数据大小

	sys.DMA_Mode = DMA_Mode_Circular; // DMA模式

	sys.DMA_Priority = DMA_Priority_High; // DMA优先级

	sys.DMA_M2M = DMA_M2M_Disable; // DMA内存到内存模式

	DMA_Init(DMA1_Channel1, &sys);

	DMA_Cmd(DMA1_Channel1, ENABLE);
}
