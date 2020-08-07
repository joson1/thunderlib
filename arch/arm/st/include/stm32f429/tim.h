#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f429/sys.h"

#define TIM_CHANNEL_1 (1<<0)
#define TIM_CHANNEL_2 (1<<1)
#define TIM_CHANNEL_3 (1<<2)
#define TIM_CHANNEL_4 (1<<3)

extern void (*TIM1_arr_overflow_Irq)() ;
extern void (*TIM2_arr_overflow_Irq)() ;
extern void (*TIM3_arr_overflow_Irq)() ;
extern void (*TIM4_arr_overflow_Irq)() ;
extern void (*TIM5_arr_overflow_Irq)() ;
extern void (*TIM6_arr_overflow_Irq)() ;
extern void (*TIM7_arr_overflow_Irq)() ;
extern void (*TIM8_arr_overflow_Irq)() ;
extern void (*TIM9_arr_overflow_Irq)() ;
extern void (*TIM10_arr_overflow_Irq)();
extern void (*TIM11_arr_overflow_Irq)();
extern void (*TIM12_arr_overflow_Irq)();
extern void (*TIM13_arr_overflow_Irq)();
extern void (*TIM14_arr_overflow_Irq)();

#endif
