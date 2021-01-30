#include <thunder/dma.h>
#include <zynq7000/axi-dma.h>
#include <stdio.h>





void axi_dma_mm2s_init(uint32_t addr_src)
{
    
    
    AXIDMA0_DE->MM2S_DMACR = MASK_MM2S_DMACR_RS;
    AXIDMA0_DE->MM2S_SA = addr_src;
}

void axi_dma_mm2s_start(uint32_t NbrOfBytes)
{
    AXIDMA0_DE->MM2S_LENGTH = NbrOfBytes;
}


void axi_dma_s2mm_init(uint32_t addr_dst)
{
    AXIDMA0_DE->S2MM_DMACR = MASK_S2MM_DMACR_RS|MASK_S2MM_DMACR_IOC_IRqEn;
    AXIDMA0_DE->S2MM_DA    = addr_dst;
}


void axi_dma_s2mm_start(uint32_t NbrOfBytes)
{
    AXIDMA0_DE->S2MM_LENGTH = NbrOfBytes;
}



uint32_t dma_request(char* dst,char* src, uint32_t length)
{

    axi_dma_mm2s_init((uint32_t)src);
    axi_dma_mm2s_start(length);
    while( !((AXIDMA0_DE->MM2S_DMASR)&(MASK_MM2S_DMASR_Idle)) )

    
    axi_dma_s2mm_init( (uint32_t)dst);
    axi_dma_s2mm_start(length);

}

