#include <thunder/pwm.h>
#include "zynq/zynq.h"
#include "zynq/axi-timer.h"


#define XTC_ROUND_DIV(a, b)		((a + (b / 2)) / b)
#define XTC_HZ_TO_NS(Hz)		XTC_ROUND_DIV(1000000000, Hz)


static inline void axi_timer_pwm_init(AXI_TIMER_TypeDef* timer,uint8_t n,uint32_t Freq,uint8_t duty)
{
   uint32_t axi_clock_period = XTC_HZ_TO_NS(XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ);
   uint32_t pwm_period  = XTC_HZ_TO_NS(Freq);
   uint32_t pwm_high_time = (pwm_period*duty)/100;
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

}

void pwm_setup(uint8_t id,uint8_t duty,uint32_t freq)
{
    axi_timer_pwm_init(ATIMER1,0,freq,duty);

}
void pwm_duty_set(uint8_t id,uint8_t duty)
{


}
void pwm_freq_set(uint8_t id,uint32_t freq)
{

    
        
}

