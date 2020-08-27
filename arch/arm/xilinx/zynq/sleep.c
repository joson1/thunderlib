/*
 * @Author: your name
 * @Date: 2020-08-10 09:02:16
 * @LastEditTime: 2020-08-27 10:08:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\sleep.c
 */

/******************************************************************************
*
* Copyright (C) 2009 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************
*
* @file sleep.c
*
* This function provides a second delay using the Global Timer register in
* the ARM Cortex A9 MP core.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------- -------- -----------------------------------------------
* 1.00a ecm/sdm  11/11/09 First release
* 3.07a sgd      07/05/12 Updated sleep function to make use Global Timer
* </pre>
*
******************************************************************************/
/***************************** Include Files *********************************/

#include "zynq/sleep.h"
#include "zynq/xtime_l.h"
#include "zynq/xparameters.h"

#define COUNTS_PER_USECOND  (XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ / (2U*1000000U))
extern void  _sleep(uint32_t seconds);


/*****************************************************************************/
/*
*
* This API is used to provide delays in seconds
*
* @param	seconds requested
*
* @return	0 always
*
* @note		None.
*
****************************************************************************/
void _sleep(u32 seconds)
{
  XTime tEnd, tCur;

  XTime_GetTime(&tCur);
  tEnd  = tCur + (((XTime) seconds) * COUNTS_PER_SECOND);
  do
  {
    XTime_GetTime(&tCur);
  } while (tCur < tEnd);

}
