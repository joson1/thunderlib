#include <thunder/dma.h>
#include <stdio.h>




extern void (__dma_interrupt_register)(uint8_t ch,void* handler);    


void dmac_dev_attach(dmac_dev_t* dev)
{
    dev_register(dev,DEV_MAJOR_DMA,dev->id);
}

dmac_dev_t* dmac_open(uint32_t id)
{
    return dev_open(DEV_MAJOR_DMA,id);
}


void dma_start(dmac_dev_t* dmac,uint32_t dst,uint32_t src,uint32_t length,void* handler)
{
    __dma_interrupt_register(dmac->id,handler);
    dmac->start(dst,src,length);
}



int __attribute__((weak)) dma_stop(uint32_t DMAn)
{
    printf("ERR NO DMA DEVICES!\r\n");

}


//return DMAn
uint32_t __attribute__((weak)) dma_request(char* dst,char* src, uint32_t length)
{
    printf("ERR NO DMA DEVICES!\r\n");
}

