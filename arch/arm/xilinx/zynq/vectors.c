/******************************************************************************
*
* Copyright (C) 2009 - 2016 Xilinx, Inc.  All rights reserved.
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
/*****************************************************************************/
/**
* @file vectors.c
*
* This file contains the C level vectors for the ARM Cortex A9 core.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 1.00a ecm  10/20/09 Initial version, moved over from bsp area
* 6.0   mus  27/07/16 Consolidated vectors for a53,a9 and r5 processor
*                     and added UndefinedException for a53 32 bit and r5
*                     processor
* </pre>
*
* @note
*
* None.
*
******************************************************************************/
/***************************** Include Files *********************************/

#include "zynq/xil_exception.h"
#include "zynq/vectors.h"
#include "zynq/zynq.h"
#include <thunder/interrput.h>
#include <stdio.h>
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

typedef struct {
	Xil_ExceptionHandler Handler;
	void *Data;
} XExc_VectorTableEntry;

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern XExc_VectorTableEntry XExc_VectorTable[];

/************************** Function Prototypes ******************************/


/*****************************************************************************/
/**
*
* This is the C level wrapper for the FIQ interrupt called from the vectors.s
* file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void FIQInterrupt(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_FIQ_INT].Handler(XExc_VectorTable[
					XIL_EXCEPTION_ID_FIQ_INT].Data);
}

/*****************************************************************************/
/**
*
* This is the C level wrapper for the IRQ interrupt called from the vectors.s
* file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void IRQInterrupt(void)
{
	// int a = 1;
	// while(a);
	u32 IntIDFull;
	u32 InterruptID;
	IntIDFull = *ICCIAR;
	InterruptID = IntIDFull&0x000003FF;
	// printf("INTERFULL:%lu;INTER:%lu\r\n",IntIDFull,InterruptID);
	if (MAX_IRQn <= InterruptID) {
	goto IntrExit;
	}
	if (IRQ_vector_table[InterruptID].Handler)
	{
		/* code */
		IRQ_vector_table[InterruptID].Handler( 0 );
	}

	

IntrExit:
	*ICCEOIR =IntIDFull;
}

#if !defined (__aarch64__)
/*****************************************************************************/
/**
*
* This is the C level wrapper for the Undefined exception called from the
* vectors.s file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void UndefinedException(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_UNDEFINED_INT].Handler(XExc_VectorTable[
					XIL_EXCEPTION_ID_UNDEFINED_INT].Data);
}

/*****************************************************************************/
/**
*
* This is the C level wrapper for the SW Interrupt called from the vectors.s
* file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void SWInterrupt(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_SWI_INT].Handler(XExc_VectorTable[
					XIL_EXCEPTION_ID_SWI_INT].Data);
}

/*****************************************************************************/
/**
*
* This is the C level wrapper for the DataAbort Interrupt called from the
* vectors.s file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void DataAbortInterrupt(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_DATA_ABORT_INT].Handler(
		XExc_VectorTable[XIL_EXCEPTION_ID_DATA_ABORT_INT].Data);
}

/*****************************************************************************/
/**
*
* This is the C level wrapper for the PrefetchAbort Interrupt called from the
* vectors.s file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void PrefetchAbortInterrupt(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_PREFETCH_ABORT_INT].Handler(
		XExc_VectorTable[XIL_EXCEPTION_ID_PREFETCH_ABORT_INT].Data);
}
#else

/*****************************************************************************/
/**
*
* This is the C level wrapper for the Synchronous Interrupt called from the vectors.s
* file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void SynchronousInterrupt(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_SYNC_INT].Handler(XExc_VectorTable[
					XIL_EXCEPTION_ID_SYNC_INT].Data);
}

/*****************************************************************************/
/**
*
* This is the C level wrapper for the SError Interrupt called from the
* vectors.s file.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void SErrorInterrupt(void)
{
	XExc_VectorTable[XIL_EXCEPTION_ID_SERROR_ABORT_INT].Handler(
		XExc_VectorTable[XIL_EXCEPTION_ID_SERROR_ABORT_INT].Data);
}

#endif
