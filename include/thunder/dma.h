#pragma once
#include <stdint.h>
#include <thunder/device.h>


typedef struct 
{
    uint8_t id;
    uint8_t isLocked;
    void (*start)(uint32_t dst,uint32_t src,uint32_t nBrOfBytes);
    void (*stop)(void);
    uint32_t interrupt_id;
    uint32_t interrupt_mask;
    void (*interrupt_enable)();
    void (*interrupt_disable)();
    void (*interrupt_clear)();
    ListItem_t devItem;
} dmac_dev_t;

 

dmac_dev_t* dmac_request(uint8_t id);
void dmac_dev_attach(dmac_dev_t* dev);
dmac_dev_t* dmac_open(uint32_t id);

void dma_start(dmac_dev_t* dmac,uint32_t dst,uint32_t src,uint32_t length,void* handler);



// int __attribute__((weak)) dma_start(uint32_t DMAn);
int __attribute__((weak)) dma_stop(uint32_t DMAn);
