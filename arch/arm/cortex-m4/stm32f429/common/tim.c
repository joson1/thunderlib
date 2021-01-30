#include "stm32f429/tim.h"
#include "stddef.h"

void (*TIM1_arr_overflow_Irq)()  = NULL;
void (*TIM2_arr_overflow_Irq)()  = NULL;
void (*TIM3_arr_overflow_Irq)()  = NULL;
void (*TIM4_arr_overflow_Irq)()  = NULL;
void (*TIM5_arr_overflow_Irq)()  = NULL;
void (*TIM6_arr_overflow_Irq)()  = NULL;
void (*TIM7_arr_overflow_Irq)()  = NULL;
void (*TIM8_arr_overflow_Irq)()  = NULL;
void (*TIM9_arr_overflow_Irq)()  = NULL;
void (*TIM10_arr_overflow_Irq)() = NULL;
void (*TIM11_arr_overflow_Irq)() = NULL;
void (*TIM12_arr_overflow_Irq)() = NULL;
void (*TIM13_arr_overflow_Irq)() = NULL;
void (*TIM14_arr_overflow_Irq)() = NULL;

void TIM1_UP_TIM10_IRQHandler()
{
    if(TIM1_arr_overflow_Irq!=0)
    if((TIM1->SR)&0X0001)
    {
		TIM1->SR &= 0XFFFE;
        TIM1_arr_overflow_Irq();	
    }
    
    if(TIM10_arr_overflow_Irq!=0)
    if((TIM10->SR)&0X0001)
    {
        TIM10_arr_overflow_Irq();
        TIM10->SR &= 0XFFFE;
    }
}

void TIM2_IRQHandler()
{
    if((TIM2->SR)&0X0001)
    {
        TIM2_arr_overflow_Irq();
        TIM2->SR &= 0XFFFE;
    }
}

void TIM3_IRQHandler()
{
    if(TIM3->SR&0x0001)
    {
        TIM3_arr_overflow_Irq();
    }

    TIM3->SR &= 0XFFFE;
}

void TIM4_IRQHandler()
{
    if(TIM4->SR & 0x0001)
    {
        TIM4_arr_overflow_Irq();
    }
    
    TIM4->SR &= 0XFFFE;    
}

void TIM5_IRQHandler()
{
    if(TIM5->SR&0x0001)
    {
        TIM5_arr_overflow_Irq();
    }
    
    TIM5->SR &= 0XFFFE;        
}
void TIM6_DAC_IRQHandler()
{
    if(TIM6->SR & 0x0001)
    {
        TIM6_arr_overflow_Irq();
    }
    
    TIM6->SR &= 0XFFFE;        
}

void TIM7_IRQHandler()
{
    if(TIM7->SR & 0x0001)
    {
        TIM7_arr_overflow_Irq();
    }

    TIM7->SR &= 0XFFFE;        
}

void TIM8_UP_TIM13_IRQHandler()
{
    if(TIM8_arr_overflow_Irq!=0)
    if((TIM8->SR)&0X0001)
    {
        TIM8_arr_overflow_Irq();
        TIM8->SR &= 0XFFFE;
    }

    if(TIM13_arr_overflow_Irq!=0)
    if((TIM13->SR)&0X0001)
    {
        TIM13_arr_overflow_Irq();
        TIM13->SR &= 0XFFFE;
    }
}

void TIM1_BRK_TIM9_IRQHandler()
{
    if(TIM9_arr_overflow_Irq!=0)
    if((TIM9->SR)&0X0001)
    {
        TIM9_arr_overflow_Irq();
        TIM9->SR &= 0XFFFE;
    }
}

void TIM1_TRG_COM_TIM11_IRQHandler()
{
    if(TIM11_arr_overflow_Irq!=0)
    if((TIM11->SR)&0X0001)
    {
        TIM11_arr_overflow_Irq();
        TIM11->SR &= 0XFFFE;
    }
}

void TIM8_BRK_TIM12_IRQHandler()
{
    if(TIM12_arr_overflow_Irq!=0)
    if((TIM12->SR)&0X0001)
    {
        TIM12_arr_overflow_Irq();
        TIM12->SR &= 0XFFFE;
    }
}

void TIM8_TRG_COM_TIM14_IRQHandler()
{
    if(TIM14_arr_overflow_Irq!=0)
    if((TIM14->SR)&0X0001)
    {
        TIM14_arr_overflow_Irq();
        TIM14->SR &= 0XFFFE;
    }
}

//TIM1_BRK_TIM9_IRQHandler
//TIM1_UP_TIM10_IRQHandler
//TIM1_TRG_COM_TIM11_IRQHandler
//TIM8_BRK_TIM12_IRQHandler 
//TIM8_UP_TIM13_IRQHandler  
//TIM8_TRG_COM_TIM14_IRQHandler
