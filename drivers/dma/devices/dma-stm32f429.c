#include <thunder/dma.h>
#include "stm32f429/dma.h"



extern void (__dma_interrupt_register)(uint8_t ch,void* handler);    



DMA_InitDef dma0_conf = {

    .DMA_Streamx = DMA1_Stream1,
    .Channel = 0,
    .Direction = DMA_MEMORY_TO_MEMORY,
    .Mode = DMA_MODE_NORMAL,

};	
	
DMA_InitDef dma1_conf = {

    .DMA_Streamx = DMA1_Stream1,
    .Channel = 1,
    .Direction = DMA_MEMORY_TO_MEMORY,
    .Mode = DMA_MODE_NORMAL,

};	


void dma0_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{ 
    
}


dmac_dev_t dmac0 = {
    .id = 0,
    .isLocked = 0,
    .start = dma0_start

};




