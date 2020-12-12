#include <thunder/pwm.h>
#include "zynq/zynq.h"
#include "zynq/ttc.h"



static inline void timer_ttc__pwm_init(TTC_TypeDef* ttc,uint8_t n,uint32_t Freq,uint8_t duty)
{
	uint16_t Interval;
	uint8_t Prescaler;
	float duty_f = duty/100;
    
    ttc_reset(ttc,n);

	ttc_CalcIntervalFromFreq(Freq,&Interval, &Prescaler);
    ttc->clock_control[n] |= (Prescaler<<1);
	ttc->interval_counter[n] = Interval;
    // ttc->counter_control[n] |= (1<<1);

    ttc->match_0_counter[0] = 0,5*Interval;
    ttc->match_0_counter[1] = 0.5*Interval;
    ttc->match_0_counter[2] = 0.5*Interval;
    ttc->counter_control[0] = 0x0A;
    ttc->counter_control[1] = 0x0A;
    ttc->counter_control[2] = 0x0A;

}

void pwm_setup(uint8_t id,uint8_t duty,uint32_t freq)
{
    if (id>2)
    {
        id-=3;
        timer_ttc__pwm_init(TTC1,id,freq,duty);
        
        ttc_start(TTC1,id);

    }else
    {
        timer_ttc__pwm_init(TTC0,id,freq,duty);
        
        ttc_start(TTC0,id);
    }
    
    

}
void pwm_duty_set(uint8_t id,uint8_t duty)
{
	uint16_t Interval;
	float duty_f = duty/100;

    if (id>2)
    {
        id-=3;

        Interval = TTC1->interval_counter[id];
        TTC1->interval_counter[id] = Interval*duty_f;

    }else
    {

        Interval = TTC0->interval_counter[id];
        TTC0->interval_counter[id] = Interval*duty_f;

    }
    
    
}
void pwm_freq_set(uint8_t id,uint32_t freq)
{
    if (id>2)
    {
        id-=3;

    }else
    {

    }
    
        
}

