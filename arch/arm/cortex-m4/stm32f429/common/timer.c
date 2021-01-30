#include "stm32f429/timer.h"
#include "stm32f429/tim.h"

//tim2 ~ tim14
//其中TIM1,TIM8,9,10,11 时钟180M   其它TIM时钟90M
void timerInit(Timer_InitDef *Timer)
{
    u32 n;
    u16 ck_int = 9000;
    switch((u32)Timer->TIMx)
    {
        case (u32)TIM1:
            RCC->APB2ENR |= 1<<0;
            ck_int = 18000;
            break;
        case (u32)TIM8:
            RCC->APB2ENR |= 1<<1;
            ck_int = 18000;
            break;
        case (u32)TIM9:
            RCC->APB2ENR |= 1<<16;
            ck_int = 18000;
            break;
        case (u32)TIM10:
            RCC->APB2ENR |= 1<<17;
            ck_int = 18000;
            break;
        case (u32)TIM11:
            RCC->APB2ENR |= 1<<18;
            ck_int = 18000;
            break;
        case (u32)TIM12:
            RCC->APB1ENR |= 1<<6;
            break;
        case (u32)TIM13:
            RCC->APB1ENR |= 1<<7;
            break;
        case (u32)TIM14:
            RCC->APB1ENR |= 1<<8;
            break;
        default:
            RCC->APB1ENR |= 1 << (((u32)Timer->TIMx - (u32)TIM2) / 0X0400);//tim 2-7
            break;
    }
    
    if (Timer->ms)
    {
        Timer->psc = ck_int;   //10k, 0.1ms计数
        Timer->arr = Timer->ms * 10;  //最大定时时间6553ms
    }
    
    Timer->TIMx->PSC = Timer->psc - 1;
    Timer->TIMx->ARR = Timer->arr - 1;
	Timer->TIMx->SR &= 0XFFFE;
    Timer->TIMx->DIER |= 1 << 0; //set update interrupt
    

    switch ((u32)Timer->TIMx)
    {
        case (u32)TIM1:
            n=TIM1_UP_TIM10_IRQn;
            TIM1_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM2:
            n=TIM2_IRQn;
            TIM2_arr_overflow_Irq = Timer->event_handler;
        break;
    
        case (u32)TIM3:
            n=TIM3_IRQn;
            TIM3_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM4:
            n=TIM4_IRQn;
            TIM4_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM5:
            n=TIM5_IRQn;
            TIM5_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM6:
            n=TIM6_DAC_IRQn;
            TIM6_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM7:
            n=TIM7_IRQn;
            TIM7_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM8:
            n=TIM8_UP_TIM13_IRQn;
            TIM8_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM9:
            n=TIM1_BRK_TIM9_IRQn;
            TIM9_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM10:
            n=TIM1_UP_TIM10_IRQn;
            TIM10_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM11:
            n=TIM1_TRG_COM_TIM11_IRQn;
            TIM11_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM12:
            n=TIM8_BRK_TIM12_IRQn;
            TIM12_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM13:
            n=TIM8_UP_TIM13_IRQn;
            TIM13_arr_overflow_Irq = Timer->event_handler;
        break;
        case (u32)TIM14:
            n=TIM8_TRG_COM_TIM14_IRQn;
            TIM14_arr_overflow_Irq = Timer->event_handler;
        break;
    default:
        break;
    }

    MY_NVIC_Init(Timer->Priority,n);	
    Timer->TIMx->CR1  |= 0x01;    //enable
	
}
