
#include "zynq7000/sleep.h"
#include "zynq7000/xtime_l.h"
#include "zynq7000/xparameters.h"
#include "zynq7000/xil_types.h"
#include "zynq7000/xpseudo_asm.h"
#include "zynq7000/xreg_cortexa9.h"

#include <thunder/delay.h>

/* Global Timer is always clocked at half of the CPU frequency */
#define COUNTS_PER_USECOND  (XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ / (2U*1000000U))

/*****************************************************************************/
/**
*
* This API gives a delay in microseconds
*
* @param	useconds requested
*
* @return	0 if the delay can be achieved, -1 if the requested delay
*		is out of range
*
* @note		None.
*
****************************************************************************/

// _delay_ms
// _delay_us


void _delay_us(u32 useconds)
{
	XTime tEnd, tCur;

	XTime_GetTime(&tCur);
	tEnd = tCur + (((XTime) useconds) * COUNTS_PER_USECOND);
	do
	{
		XTime_GetTime(&tCur);
	} while (tCur < tEnd);
}

void _delay_ms(u32 ms)
{
    _delay_us(ms*1000);
}
