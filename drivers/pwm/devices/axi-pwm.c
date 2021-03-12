#include <thunder/pwm.h>
#include "zynq7000/zynq.h"
#include "zynq7000/axi-timer.h"
#include <thunder/device.h>

#define XTC_ROUND_DIV(a, b)		((a + (b / 2)) / b)
#define XTC_HZ_TO_NS(Hz)		XTC_ROUND_DIV(1000000000, Hz)

struct pwm_dev pwm0;
struct pwm_dev pwm1;
struct pwm_dev pwm2;


uint32_t axi_clock_period = XTC_HZ_TO_NS(XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ);

// struct pwm_dev
// {
// 	uint8_t id;
//     uint32_t freq;
//     uint8_t duty;
// 	void (*_setup)(uint8_t duty,uint32_t freq);//
// 	int (*_set_duty)(uint8_t duty);//
// 	int (*_set_freq)(uint32_t freq);//

// 	struct pwm_dev* next;
// };

static inline void axi_timer_pwm_init(AXI_TIMER_TypeDef* timer,uint8_t n,uint32_t Freq,uint8_t duty)
{
   uint32_t pwm_period  = XTC_HZ_TO_NS(Freq);
   uint32_t pwm_high_time = (pwm_period*duty)/100;


    timer->TLR0 = 0;
    timer->TLR1 = 0;
    timer->TCR0 = 0;
    timer->TCR1 = 0;

    //The mode for both Timer 0 and Timer 1 must be set to Generate mode (bit MDT in the TCSR set to 0).
   timer->TCSR0  = 0;
   timer->TCSR1  = 0;

    //The PWMA0 bit in TCSR0 and PWMB0 bit in TCSR1 must be set to 1 to enable PWM mode.
    timer->TCSR0 |= 1<<9;
    timer->TCSR1 |= 1<<9;
    
    //he GenerateOut signals must be enabled in the TCSR (bit GENT set to 1).
    //The PWM0signal is generated from the GenerateOut signals of Timer 0 and Timer 1, so these signals must be enabled in both timer/counters.
    
    timer->TCSR0 |= 1<<2;
    timer->TCSR1 |= 1<<2;
    timer->TCSR0 |= 1<<7;
    timer->TCSR0 |= 1<<10;

    timer->TCSR1 |= 1<<7;
    timer->TCSR1 |= 1<<10;

    // The assertion level of the GenerateOut signals for both timers in the pair must be set to Active High.
    //The counter can be set to count up or down.
    /*Setting the PWM Period and Duty Factor*/
    // The PWM period is determined by the generate value in the Timer 0 load register (TLR0). 
    // The PWM high time is determined by the generate value in the Timer 1 load register (TLR1).
    //  The period and duty factor are calculated as follows:
    /*
    *When counters are configured to count up (UDT = 0):

    PWM_PERIOD/AXI_CLOCK_PERIOD


TLR0=MAX_COUNT-(PWM_PERIOD/AXI_CLOCK_PERIOD-2)
    *PWM_PERIOD = (MAX_COUNT - TLR0 + 2) * AXI_CLOCK_PERIOD


TLR1=MAX_COUNT-PWM_HIGH_TIME/AXI_CLOCK_PER+2
    *PWM_HIGH_TIME = (MAX_COUNT - TLR1 + 2) * AXI_CLOCK_PER

    *When counters are configured to count down (UDT = 1):
    *PWM_PERIOD = (TLR0 + 2) * AXI_CLOCK_PERIOD
    *PWM_HIGH_TIME = (TLR1 + 2) * AXI_CLOCK_PERIOD
    *where MAX_COUNT is the maximum count value for the counter, such as 0xFFFFFFFFfor a 32-bit counter
    */

   timer->TLR0 = MAX_COUNT - pwm_period/axi_clock_period + 2;

   timer->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;

    // timer->TCR0 = timer->TLR0;
    // timer->TCR1 = timer->TLR1;

    timer->TCSR1 |= 1<<5;
    timer->TCSR0 |= 1<<5;
    timer->TCSR1 &= ~(1<<5);
    timer->TCSR0 &= ~(1<<5);
}



static void pwm0_setup(uint8_t duty,uint32_t freq)
{
    axi_timer_pwm_init(ATIMER0,0,freq,duty);

}
static void pwm0_duty_set(uint8_t duty)
{
    uint32_t pwm_period  = XTC_HZ_TO_NS(pwm0.freq);
    uint32_t pwm_high_time = (pwm_period*duty)/100;
    ATIMER0->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;

}
static void pwm0_freq_set(uint32_t freq)
{
    uint32_t pwm_period  = XTC_HZ_TO_NS(pwm0.freq);
    uint32_t pwm_high_time = (pwm_period*(pwm0.duty))/100;


   ATIMER0->TLR0 = MAX_COUNT - pwm_period/axi_clock_period + 2;
   ATIMER0->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;
    
        
}

struct pwm_dev pwm0=
{
	.id=0,
	._setup = pwm0_setup,
	._set_duty=pwm0_duty_set,
	._set_freq=pwm0_freq_set

};



static void pwm1_setup(uint8_t duty,uint32_t freq)
{
    axi_timer_pwm_init(ATIMER1,0,freq,duty);

}
static void pwm1_duty_set(uint8_t duty)
{
    uint32_t pwm_period  = XTC_HZ_TO_NS(pwm1.freq);
    uint32_t pwm_high_time = (pwm_period*duty)/100;
    ATIMER1->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;

}
static void pwm1_freq_set(uint32_t freq)
{
    uint32_t pwm_period  = XTC_HZ_TO_NS(pwm1.freq);
    uint32_t pwm_high_time = (pwm_period*(pwm1.duty))/100;


   ATIMER1->TLR0 = MAX_COUNT - pwm_period/axi_clock_period + 2;
   ATIMER1->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;
    
        
}

struct pwm_dev pwm1=
{
	.id=1,
	._setup = pwm1_setup,
	._set_duty=pwm1_duty_set,
	._set_freq=pwm1_freq_set

};



static void pwm2_setup(uint8_t duty,uint32_t freq)
{
    axi_timer_pwm_init(ATIMER2,0,freq,duty);

}
static void pwm2_duty_set(uint8_t duty)
{
    uint32_t pwm_period  = XTC_HZ_TO_NS(pwm2.freq);
    uint32_t pwm_high_time = (pwm_period*duty)/100;
    ATIMER2->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;

}
static void pwm2_freq_set(uint32_t freq)
{
    uint32_t pwm_period  = XTC_HZ_TO_NS(pwm2.freq);
    uint32_t pwm_high_time = (pwm_period*(pwm2.duty))/100;


   ATIMER2->TLR0 = MAX_COUNT - pwm_period/axi_clock_period + 2;
   ATIMER2->TLR1 = MAX_COUNT - pwm_high_time/axi_clock_period + 2;
    
        
}


struct pwm_dev pwm2=
{
	.id=2,
	._setup = pwm2_setup,
	._set_duty=pwm2_duty_set,
	._set_freq=pwm2_freq_set

};
void zynq_axi_pwm_init()
{
    pwm_dev_attach(&pwm0);
    pwm_dev_attach(&pwm1);
    pwm_dev_attach(&pwm2);

}

DEV_INIT(zynq_axi_pwm_init);
extern void zynq_axi_pwm_init();
