/*
 * @Author: your name
 * @Date: 2020-08-10 16:28:42
 * @LastEditTime: 2020-08-10 16:31:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\timer\devices\timer-stm32f429.c
 */
/*-----------------------TIMER-------------------------*/

#include "stm32f429xx.h"
#include "stm32f429/timer.h"
#include <thunder/timer.h>
#include <thunder/device.h>


extern void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)());


void timer_init(uint32_t id,uint32_t ms,
                    uint32_t Priority,void (*event_handler)())
{

    Timer_InitDef timerx = {
        .event_handler = event_handler,
        .ms = ms,
        .Priority = Priority
    };


    switch (id+1)
    {
    case 1:
        timerx.TIMx = TIM1;
        break;
    case 2:
        timerx.TIMx = TIM2;
        break;
    
    case 3:
        timerx.TIMx = TIM3;
        break;
    case 4:
        timerx.TIMx = TIM4;
        break;
    
    case 5:
        timerx.TIMx = TIM5;
        break;
    
    case 6:
        timerx.TIMx = TIM6;
        break;

    case 7:
        timerx.TIMx = TIM7;
        break;
    case 8:
        timerx.TIMx = TIM8;
        break;
    case 9:
        timerx.TIMx = TIM9;
        break;
    case 10:
        timerx.TIMx = TIM10;
        break;
    case 11:
        timerx.TIMx = TIM11;
        break;
    default:
        break;
    }
    timerInit(&timerx);

}





void tim_set_period(timer_dev_t* ptmr,uint32_t ms)
{
    TIM_TypeDef * tim = (TIM_TypeDef *)ptmr->prv_data;
    Timer_InitDef timerx = {
        .event_handler = 0,
        .ms = ms,
        .Priority = ptmr->irq.priority,
        .TIMx = tim
    };
    timerInit(&timerx);

}

void tim_start(timer_dev_t* ptmr)
{
    TIM_TypeDef * tim = (TIM_TypeDef *)ptmr->prv_data;

    tim->CR1  |= 0x01;    //enable
}

void tim_stop(timer_dev_t* ptmr)
{
    TIM_TypeDef * tim = (TIM_TypeDef *)ptmr->prv_data;

    tim->CR1  &= ~(0x01);    //enable
}

void tim_clear_irq(timer_dev_t* ptmr)
{
    return;
}


timer_dev_t tim1 = {
    .id=0,
    .prv_data=TIM1,
    .ops = {
            .set_period=tim_set_period,
            .start=tim_start,
            .stop=tim_stop,
        },
    .irq = {
        .IRQn=TIM1_UP_TIM10_IRQn,
        .priority = 3,
        .is_shared=0,
        .clear_irq=tim_clear_irq
    }
};

timer_dev_t tim2 = {
    .id=1,
    .prv_data=TIM2,
    .ops = {
            .set_period=tim_set_period,
            .start=tim_start,
            .stop=tim_stop,
        },
    .irq = {
        .IRQn=TIM2_IRQn,
        .priority = 3,
        .is_shared=0,
        .clear_irq=tim_clear_irq
    }
};


timer_dev_t tim3 = {
    .id=2,
    .prv_data=TIM3,
    .ops = {
            .set_period=tim_set_period,
            .start=tim_start,
            .stop=tim_stop,
        },
    .irq = {
        .IRQn=TIM3_IRQn,
        .priority = 3,
        .is_shared=0,
        .clear_irq=tim_clear_irq
    }
};


void TIM1_UP_TIM10_IRQHandler()
{

    if((TIM1->SR)&0X0001)
    {
        tim1.handler(&tim1);
		TIM1->SR &= 0XFFFE;
    }

    if((TIM10->SR)&0X0001)
    {
        // TIM10_arr_overflow_Irq();
        TIM10->SR &= 0XFFFE;
    }
}

void TIM2_IRQHandler()
{
    if((TIM2->SR)&0X0001)
    {
        // TIM2_arr_overflow_Irq();
        tim2.handler(&tim2);
        TIM2->SR &= 0XFFFE;
    }
}

void TIM3_IRQHandler()
{
    if(TIM3->SR&0x0001)
    {
        tim3.handler(&tim3);

        // TIM3_arr_overflow_Irq();
        TIM3->SR &= 0XFFFE;
    }

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

// extern void stm32f429_timer_init();
void stm32f429_timer_init()
{

	// _timer_setup = &timer_init;
    timer_dev_attach(&tim1);
    timer_dev_attach(&tim2);
    timer_dev_attach(&tim3);

}


DEV_INIT(stm32f429_timer_init);