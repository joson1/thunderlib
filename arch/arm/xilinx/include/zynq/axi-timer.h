#pragma once
#include <stdint.h>

#define AXI_TIMER_BASE_ADDRESS 0x42800000U
#define XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ 100000000U
#define MAX_COUNT 0xFFFFFFFF

typedef struct 
{
  volatile uint32_t TCSR0; //Timer 0 Control and Status Register
  volatile uint32_t TLR0; //Timer 0 Load Register
  volatile uint32_t TCR0; //Timer 0 Counter Register
  volatile uint32_t RSVD0; //Reserved

  volatile uint32_t TCSR1; //Timer 1 Control and Status Register
  volatile uint32_t TLR1; //Timer 1 Load Register
  volatile uint32_t TCR1; //Timer 1 Counter Register
  volatile uint32_t RSVD1; //Reserved

}AXI_TIMER_TypeDef ;

#define ATIMER1 ((AXI_TIMER_TypeDef*)(AXI_TIMER_BASE_ADDRESS))

