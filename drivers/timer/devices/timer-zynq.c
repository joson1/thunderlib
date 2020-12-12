/*
 * @Author: your name
 * @Date: 2020-08-27 09:50:49
 * @LastEditTime: 2020-10-05 19:56:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\timer\devices\timer-zynq.c
 */
#include "zynq/ttc.h"
#include <thunder/interrput.h>
#include <thunder/timer.h>
#include <zynq/xil_exception.h>


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
    
	TTC0->counter_control[0]&=(~(1<<5));

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
        irq_register(TIMER3_IRQ+id,event_handler,TRIGGER_EDGE_HIGHLEVEL,&TTC1->ISR[id],ttc_clear_interrupt);
        
        ttc_start(TTC1,id);

    }else
    {
        timer_ttc_init(TTC0,id,ms);
        irq_register(TIMER0_IRQ+id,event_handler,TRIGGER_EDGE_HIGHLEVEL,&TTC0->ISR[id],ttc_clear_interrupt);
        
        
        ttc_start(TTC0,id);
    }
    
    
}

extern void zynq_timer_init();
void zynq_timer_init()
{

	_timer_setup = &timer_init;
}
