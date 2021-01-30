#pragma once
#include "stm32f429/sys.h"

#define DMA_DATA_WIDTH_8 0
#define DMA_DATA_WIDTH_16 1
#define DMA_DATA_WIDTH_32 2


#define DMA_PERIPH_TO_MEMORY 0
#define DMA_MEMORY_TO_PERIPH 1 
#define DMA_MEMORY_TO_MEMORY 2

#define DMA_MODE_NORMAL         0     /*!< Normal mode                  */
#define DMA_MODE_CIRCULAR        1     //Circular mode

#define DMA_PRIORITY_LOW            0
#define DMA_PRIORITY_MEDIUM         1
#define DMA_PRIORITY_HIGH           2
#define DMA_PRIORITY_VERY_HIGH      3

#define DMA_BURST_SINGLE      0
#define DMA_BURST_INC4        1
#define DMA_BURST_INC8        2
#define DMA_BURST_INC16       3

#define DMA_INT_TransferComplete 1<<3
#define DMA_INT_HalfTransfer 1<<2
#define DMA_INT_TransferError 1<<1
#define DMA_INT_DirectModeError 1<<0
#define DMA_INT_NONE 0

typedef struct
{
    DMA_Stream_TypeDef   *DMA_Streamx;
    u8                   Channel;
    u8                   Direction;
    u8                   bPeriphInc;
    u8                   bMemInc;
    u16                  Mode;
    u32                  PeriphAddr;
    u32                  Memory0Addr;
    u32                  Memory1Addr;
    u8                   PeriphDataWidth;
    u32                  NumberOfData;
    u8                   MemDataWidth;
    u8                   Priority;
    u8                   MemBurst;
    u8                   PeriphBurst;
    u8                   Interrupt;

} DMA_InitDef;

extern void DMA_Config(DMA_InitDef* DMA_str);
extern void DMA_AddressSet(DMA_InitDef* DMA_str,u32 SrcAddress,u32 DstAddress);
extern void DMA_Start(DMA_InitDef* DMA_str);
