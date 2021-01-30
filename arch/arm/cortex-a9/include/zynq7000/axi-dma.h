#pragma once
#include <stdint.h>


typedef struct 
{
    volatile uint32_t MM2S_DMACR;
    volatile uint32_t MM2S_DMASR;
    volatile uint32_t MM2S_CURDESC;
    volatile uint32_t MM2S_CURDESC_MSB;
    volatile uint32_t MM2S_TAILDESC;
    volatile uint32_t MM2S_TAILDESC_MSB;
    volatile uint32_t SG_CTL;
    volatile uint32_t S2MM_DMACR;
    volatile uint32_t S2MM_DMASR;
    volatile uint32_t S2MM_CURDESC;
    volatile uint32_t S2MM_CURDESC_MSB;
    volatile uint32_t S2MM_TAILDESC;
    volatile uint32_t S2MM_TAILDESC_MSB;


}AXI_DMA_SGMODE_T;

typedef struct 
{
    volatile uint32_t MM2S_DMACR;
    volatile uint32_t MM2S_DMASR;
    volatile uint32_t Reserved[4];
    volatile uint32_t MM2S_SA;
    volatile uint32_t MM2S_SA_MSB;
    volatile uint32_t Reserved1[2];
    volatile uint32_t MM2S_LENGTH;
    volatile uint32_t Reserved2[1];

    volatile uint32_t S2MM_DMACR;
    volatile uint32_t S2MM_DMASR;
    volatile uint32_t Reserved3[4];
    volatile uint32_t S2MM_DA;
    volatile uint32_t S2MM_DA_MSB;
    volatile uint32_t Reserved4[2];
    volatile uint32_t S2MM_LENGTH;


}AXI_DMA_DRMODE_T;

#define AXIDMA_0_BASEADDR 0x40400000

#define AXIDMA0_DE (((volatile AXI_DMA_DRMODE_T*)AXIDMA_0_BASEADDR))
#define AXIDMA0_SG (((volatile AXI_DMA_SGMODE_T*)AXIDMA_0_BASEADDR))

#define MASK_MM2S_DMACR_RS              (1<<0)
#define MASK_MM2S_DMACR_RESET           (1<<2)
#define MASK_MM2S_DMACR_Cyclic_BD       (1<<4)
#define MASK_MM2S_DMACR_IOC_IrqEn       (1<<12)
#define MASK_MM2S_DMACR_Dly_IrqEn       (1<<13)
#define MASK_MM2S_DMACR_Err_IrqEn       (1<<14)
#define MASK_MM2S_DMACR_IRQThreshold    (1<<16)
#define MASK_MM2S_DMACR_IRQDelay        (1<<24)


#define MASK_MM2S_DMASR_Halted          (1<<0)
#define MASK_MM2S_DMASR_Idle            (1<<1)
#define MASK_MM2S_DMASR_SGIncld         (1<<3)
#define MASK_MM2S_DMASR_DMAIntErr       (1<<4)
#define MASK_MM2S_DMASR_DMASlvErr       (1<<5)
#define MASK_MM2S_DMASR_DMADecErr       (1<<6)
#define MASK_MM2S_DMASR_SGIntErr        (1<<8)
#define MASK_MM2S_DMASR_SGSlvErr        (1<<9)
#define MASK_MM2S_DMASR_SGDecErr        (1<<10)
#define MASK_MM2S_DMASR_IOC_Irq         (1<<12)
#define MASK_MM2S_DMASR_Dly_Irq         (1<<13)
#define MASK_MM2S_DMASR_Err_Irq         (1<<14)
#define MASK_MM2S_DMASR_IRQThresholdSts (1<<16)
#define MASK_MM2S_DMASR_IRQDelaySts     (1<<24)

#define MASK_S2MM_DMACR_RS              (1<<0)
#define MASK_S2MM_DMACR_Reset           (1<<2)
#define MASK_S2MM_DMACR_Keyhole         (1<<3)
#define MASK_S2MM_DMACR_Cyclic_BD       (1<<4)
#define MASK_S2MM_DMACR_IOC_IRqEn       (1<<12)
#define MASK_S2MM_DMACR_Dly_IrqEn       (1<<13)
#define MASK_S2MM_DMACR_Err_IrqEn       (1<<14)
#define MASK_S2MM_DMACR_IRQThreshold    (1<<16)
#define MASK_S2MM_DMACR_IRQDelay        (1<<24)

#define MASK_S2MM_DMASR_Halted          (1<<0)
#define MASK_S2MM_DMASR_Idle            (1<<1)
#define MASK_S2MM_DMASR_SGIncld         (1<<3)
#define MASK_S2MM_DMASR_DMAIntErr       (1<<4)
#define MASK_S2MM_DMASR_DMASlvErr       (1<<5)
#define MASK_S2MM_DMASR_DMADecErr       (1<<6)
#define MASK_S2MM_DMASR_SGIntErr        (1<<8)
#define MASK_S2MM_DMASR_SGSlvErr        (1<<9)
#define MASK_S2MM_DMASR_SGDecErr        (1<<10)
#define MASK_S2MM_DMASR_IOC_Irq         (1<<12)
#define MASK_S2MM_DMASR_Dly_Irq         (1<<13)
#define MASK_S2MM_DMASR_Err_Irq         (1<<14)
#define MASK_S2MM_DMASR_IRQThresholdSts (1<<16)
#define MASK_S2MM_DMASR_IRQDelaySts     (1<<24)
