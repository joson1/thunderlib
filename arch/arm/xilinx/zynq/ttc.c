/*
 * @Author: Alanwake
 * @Date: 2020-08-31 19:50:15
 * @LastEditTime: 2020-10-03 20:59:21
 * @LastEditors: Please set LastEditors
 * @Description: The timer module is using TTC0 & TTC1
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\ttc.c
 */

#include "zynq/ttc.h"

#define XPAR_PS7_TTC_0_TTC_CLK_FREQ_HZ 111111115U
#define XPAR_PS7_TTC_1_TTC_CLK_FREQ_HZ 111111115U
#define XPAR_PS7_TTC_2_TTC_CLK_FREQ_HZ 111111115U


void ttc_set_clockSource(TTC_TypeDef* ttc,uint8_t n,uint8_t clocksrc)
{
    if (clocksrc)
	{
		ttc->clock_control[n] |= (1<<6);
	}else
	{
		ttc->clock_control[n] &= ~(1<<6);
		
	}
	
	
}

inline void ttc_set_mode(TTC_TypeDef* ttc,uint8_t n,uint8_t mode)
{
	
}


inline void ttc_CalcIntervalFromFreq(uint32_t Freq,uint16_t *Interval, uint8_t *Prescaler)
{
	uint8_t TmpPrescaler;
	uint32_t TempValue;
	uint32_t InputClock;

	InputClock = XPAR_PS7_TTC_0_TTC_CLK_FREQ_HZ;
	/*
	 * Find the smallest prescaler that will work for a given frequency. The
	 * smaller the prescaler, the larger the count and the more accurate the
	 *  PWM setting.
	 */
	TempValue = InputClock/ Freq;

	if (TempValue < 4U) {
		/*
		 * The frequency is too high, it is too close to the input
		 * clock value. Use maximum values to signal caller.
		 */
		*Interval = 0xFFFFU;
		*Prescaler = 0xFFU;
		return;
	}

	/*
	 * First, do we need a prescaler or not?
	 */
	if (((uint32_t)0xFFFFU) > TempValue) {
		/*
		 * We do not need a prescaler, so set the values appropriately
		 */
		*Interval = (uint16_t)TempValue;
		*Prescaler = 16U;
		return;
	}


	for (TmpPrescaler = 0U; TmpPrescaler < 16U;
	     TmpPrescaler++) {
		TempValue =	InputClock/ (Freq * (1U << (TmpPrescaler + 1U)));

		/*
		 * The first value less than 2^16 is the best bet
		 */
		if (((uint32_t)0xFFFFU) > TempValue) {
			/*
			 * Set the values appropriately
			 */
			*Interval = (uint16_t)TempValue;
			*Prescaler = TmpPrescaler;
			return;
		}
	}

	/* Can not find interval values that work for the given frequency.
	 * Return maximum values to signal caller.
	 */
	*Interval = 0xFFFFU;
	*Prescaler = 0XFFU;
	return;
}

inline void ttc_reset(TTC_TypeDef* ttc,uint8_t n)
{

	/*
	* stop the timer before configuring
	*/
	ttc->counter_control[n] |= 1;

	/*
	* Reset the count control register to it's default value.
	*/
	ttc->counter_control[n] = 0x21;	
	ttc->clock_control[n] = 0;

	ttc->interval_counter[n] = 0;

	ttc->match_0_counter[n] = 0;

	ttc->match_1_counter[n] = 0;

	ttc->match_2_counter[n] = 0;

	ttc->IER[n] = 0;
	// ttc->ISR[n] = 0x0000001FU;


	/*
	* Reset the counter value
	*/
	ttc->counter_control[n] = 0x00000010U;

	ttc->clock_control[n] = 0x01;

}


inline void ttc_stop(TTC_TypeDef* ttc,uint8_t n)
{
	ttc->counter_control[n] |= 1;

}


inline void ttc_start(TTC_TypeDef* ttc,uint8_t n)
{
	ttc->counter_control[n] &= ~0x00000001U;
	
}