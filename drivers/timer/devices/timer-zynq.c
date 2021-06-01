/*
 * @Author: your name
 * @Date: 2020-08-27 09:50:49
 * @LastEditTime: 2020-10-05 19:56:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\timer\devices\timer-zynq.c
 */
#include "zynq7000/ttc.h"
#include <thunder/irq.h>
#include <thunder/timer.h>
#include <zynq7000/xil_exception.h>
#include <thunder/device.h>

extern void (*_timer_setup)(uint32_t id,uint32_t ms,uint32_t Priority,void (*event_handler)());

static void timer_ttc_init(TTC_TypeDef* ttc,uint8_t n,uint32_t ms)
{
	uint16_t Interval;
	uint8_t Prescaler;
	uint32_t Freq;
    
    ttc_reset(ttc,n);

	Freq = 1000/ms;
	ttc_CalcIntervalFromFreq(Freq,&Interval, &Prescaler);
    ttc->clock_control[n] |= (Prescaler<<1);
	ttc->interval_counter[n] = Interval;
    ttc->counter_control[n] |= (1<<1);
    ttc->IER[n] = 0x01;
	ttc->counter_control[n] |= 1;
    

    volatile int b =  ttc->ISR[n];
}
void ttc_clear_interrupt(void* ISR)
{
    volatile int a = *(uint32_t*)ISR;
}

void timer_init(uint32_t id,uint32_t ms,uint32_t Priority,void (*event_handler)())
{
    if (id>2)
    {
        id-=3;
        timer_ttc_init(TTC1,id,ms);
        irq_register(TIMER3_IRQ+id,event_handler,&TTC1->ISR[id],ttc_clear_interrupt);
        
        ttc_start(TTC1,id);

    }else
    {
        timer_ttc_init(TTC0,id,ms);
        irq_register(TIMER0_IRQ+id,event_handler,&TTC0->ISR[id],ttc_clear_interrupt);
        
        
        ttc_start(TTC0,id);
    }
    
    
}



// typedef struct __tmr_dev
// {
//     uint8_t id;
//     uint32_t period_ms;
//     void* handler;
//     void* prv_data;
//     struct timer_ops ops;
//     struct timer_irq irq;
// 	ListItem_t devItem;

// }timer_dev_t;


// struct timer_ops
// {
//     void (*set_period)(uint32_t ms);
//     void (*start)(timer_dev_t* ptmr);
//     void (*stop)(timer_dev_t* ptmr);
// };

// struct timer_irq
// {
//     uint32_t IRQn;
//     uint32_t is_shared;
//     void (*clear_irq)(timer_dev_t* ptmr);
// };

void tmr_clear_irq(timer_dev_t* ptmr)
{
    uint32_t* ISR = ((typeof(TTC0))(ptmr->prv_data))->ISR;
    volatile int a = *ISR;
}

void tmr_set_period(timer_dev_t* ptmr,uint32_t ms)
{
    ptmr->period_ms = ms;
    int id = ptmr->id;
    if (id>2)
    {
        id-=3;
        timer_ttc_init(((typeof(TTC0))(ptmr->prv_data)),id,ms);


    }else
    {
        timer_ttc_init(((typeof(TTC0))(ptmr->prv_data)),id,ms);

    }
    
}

void tmr_start(timer_dev_t* ptmr)
{
    int id = ptmr->id;
    if (id>2)
    {
        id-=3;

        ttc_start(((typeof(TTC0))(ptmr->prv_data)),id);

    }else
    {
        ttc_start(((typeof(TTC0))(ptmr->prv_data)),id);

    }
}

void tmr_stop(timer_dev_t* ptmr)
{
    int id = ptmr->id;
    if (id>2)
    {
        id-=3;

        ttc_start(((typeof(TTC0))(ptmr->prv_data)),id);

    }else
    {
        ttc_start(((typeof(TTC0))(ptmr->prv_data)),id);

    }
}

timer_dev_t tmr0 = {
    .id=0,
    .prv_data=TTC0,
    .ops = {
            .set_period=tmr_set_period,
            .start=tmr_start,
            .stop=tmr_stop,
        },
    .irq = {
        .IRQn=TIMER0_IRQ,
        .is_shared=0,
        .clear_irq=tmr_clear_irq
    }
};

timer_dev_t tmr1 = {
    .id=1,
    .prv_data=TTC0,
    .ops = {
            .set_period=tmr_set_period,
            .start=tmr_start,
            .stop=tmr_stop,
        },
    .irq = {
        .IRQn=TIMER1_IRQ,
        .is_shared=0,
        .clear_irq=tmr_clear_irq
    }
};

timer_dev_t tmr2 = {
    .id=2,
    .prv_data=TTC0,
    .ops = {
            .set_period=tmr_set_period,
            .start=tmr_start,
            .stop=tmr_stop,
        },
    .irq = {
        .IRQn=TIMER2_IRQ,
        .is_shared=0,
        .clear_irq=tmr_clear_irq
    }
};

timer_dev_t tmr3 = {
    .id=3,
    .prv_data=TTC1,
    .ops = {
            .set_period=tmr_set_period,
            .start=tmr_start,
            .stop=tmr_stop,
        },
    .irq = {
        .IRQn=TIMER3_IRQ,
        .is_shared=0,
        .clear_irq=tmr_clear_irq
    }
};

timer_dev_t tmr4 = {
    .id=4,
    .prv_data=TTC1,
    .ops = {
            .set_period=tmr_set_period,
            .start=tmr_start,
            .stop=tmr_stop,
        },
    .irq = {
        .IRQn=TIMER4_IRQ,
        .is_shared=0,
        .clear_irq=tmr_clear_irq
    }
};

timer_dev_t tmr5 = {
    .id=5,
    .prv_data=TTC1,
    .ops = {
            .set_period=tmr_set_period,
            .start=tmr_start,
            .stop=tmr_stop,
        },
    .irq = {
        .IRQn=TIMER5_IRQ,
        .is_shared=0,
        .clear_irq=tmr_clear_irq
    }
};

extern void zynq_timer_init();
void zynq_timer_init()
{
	_timer_setup = &timer_init;

    timer_dev_attach(&tmr0);
    timer_dev_attach(&tmr1);
    timer_dev_attach(&tmr2);
    timer_dev_attach(&tmr3);
    timer_dev_attach(&tmr4);
    timer_dev_attach(&tmr5);



}

DEV_INIT(zynq_timer_init);
