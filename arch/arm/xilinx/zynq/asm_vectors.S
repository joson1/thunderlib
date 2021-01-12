/******************************************************************************
*
* Copyright (C) 2009 - 2018 Xilinx, Inc.  All rights reserved.
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
* @file asm_vectors.s
*
* This file contains the initial vector table for the Cortex A9 processor
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------- -------- ---------------------------------------------------
* 1.00a ecm/sdm 10/20/09 Initial version
* 3.05a sdm	02/02/12 Save lr when profiling is enabled
* 3.10a srt     04/18/13 Implemented ARM Erratas. Please refer to file
*			 'xil_errata.h' for errata description
* 4.00a pkp	22/01/14 Modified return addresses for interrupt
*			 handlers (DataAbortHandler and SVCHandler)
*			 to fix CR#767251
* 5.1	pkp	05/13/15 Saved the addresses of instruction causing data
*			 abort and prefetch abort into DataAbortAddr and
*			 PrefetchAbortAddr for further use to fix CR#854523
* 5.4	pkp	12/03/15 Added handler for undefined exception
* 6.8	mus	04/27/18 Removed __ARM_NEON__ flag definition. Now,
*			 saving/restoring of of HW floating point register
*			 would be done through newly introduced flag
*			 FPU_HARD_FLOAT_ABI_ENABLED. This new flag will be
*			 configured based on the -mfpu-abi option in extra
*			 compiler flags.
* </pre>
*
* @note
*
* None.
*
******************************************************************************/
#include "zynq/xil_errata.h"
#include "zynq/bspconfig.h"

.org 0
.text

.globl _vector_table
.global cpu_thread_switch_interrupt_flag
.global cpu_interrupt_from_thread
.global cpu_interrupt_to_thread
    

.section .vectors
_vector_table:
	B	_boot
	B	Undefined
	B	SVCHandler
	B	PrefetchAbortHandler
	B	DataAbortHandler
	NOP	/* Placeholder for address exception vector*/
	B	IRQHandler
	B	FIQHandler


IRQHandler:					/* IRQ vector handler */

	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code*/
#if FPU_HARD_FLOAT_ABI_ENABLED
	vpush {d0-d7}
	vpush {d16-d31}
	vmrs r1, FPSCR
	push {r1}
	vmrs r1, FPEXC
	push {r1}
#endif

@ #ifdef PROFILING
@ 	ldr	r2, =prof_pc
@ 	subs	r3, lr, #0
@ 	str	r3, [r2]
@ #endif

	bl	IRQInterrupt			/* IRQ vector */

#if FPU_HARD_FLOAT_ABI_ENABLED
	pop 	{r1}
	vmsr    FPEXC, r1
	pop 	{r1}
	vmsr    FPSCR, r1
	vpop    {d16-d31}
	vpop    {d0-d7}
#endif
	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */


	subs	pc, lr, #4			/* adjust return */


FIQHandler:					/* FIQ vector handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */
#if FPU_HARD_FLOAT_ABI_ENABLED
	vpush {d0-d7}
	vpush {d16-d31}
	vmrs r1, FPSCR
	push {r1}
	vmrs r1, FPEXC
	push {r1}
#endif

FIQLoop:
	bl	FIQInterrupt			/* FIQ vector */

#if FPU_HARD_FLOAT_ABI_ENABLED
	pop 	{r1}
	vmsr    FPEXC, r1
	pop 	{r1}
	vmsr    FPSCR, r1
	vpop    {d16-d31}
	vpop    {d0-d7}
#endif
	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */
	subs	pc, lr, #4			/* adjust return */


Undefined:					/* Undefined handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */
	ldr     r0, =UndefinedExceptionAddr
	sub     r1, lr, #4
	str     r1, [r0]            		/* Store address of instruction causing undefined exception */

	bl	UndefinedException		/* UndefinedException: call C function here */
	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */
	movs	pc, lr


SVCHandler:					/* SWI handler */

	@ msr cpsr_c,0x13|0x80
	@ msr cpsr_c,0x10
	mov lr, r0
    mrs r0, cpsr
    and r1,r0,#0x3f
    msr cpsr_c, r1
    //获取中断标志位，看看是否为0
    LDR     r0, =cpu_thread_switch_interrupt_flag     //加载cpu_thread_switch_interrupt_flag的地址到r0
    LDR     r1, [r0]                                 //加载cpu_thread_switch_interrupt_flag的值到r1
	CMP 	r1,#0
    beq     SVC_exit                          //判断r1是否为0，为0则跳转到pendsv_exit

    //r1不为0则清0
    MOV     r1, #0x00
    STR     r1, [r0]                                 //将r1的值存储到cpu_thread_switch_interrupt_flag，即清0

    //判断cpu_interrupt_from_thread的值是否为0
    LDR     r0, =cpu_interrupt_from_thread            //加载cpu_interrupt_from_thread的地址到r0
    LDR     r1, [r0]                                 //加载cpu_interrupt_from_thread的值到r1
	cmp 	r1,#0
    beq     switch_to_thread                     //判断r1是否为0，为0则跳转到switch_to_thread
                                                     //第一次线程切换时cpu_interrupt_from_thread肯定为0，则跳转到switch_to_thread

@ //========================== 上文保存 ==============================
@     //当进入PendSVC Handler时，上一个线程运行的环境即：
@  	//xPSR，PC（线程入口地址），R14，R12，R3，R2，R1，R0（线程的形参）
@  	//这些CPU寄存器的值会自动保存到线程的栈中，剩下的r4~r11需要手动保存
	stmfd   sp!, {lr}
 	stmdb	sp!,{r0-r3,r12,lr}
    MOV     r1, sp                                  //获取线程栈指针到r1
    STMFD   r1!, {r4 - r11}                          //将CPU寄存器r4~r11的值存储到r1指向的地址(每操作一次地址将递减一次)
    LDR     r0, [r0]                                 //加载r0指向值到r0，即r0=rt_interrupt_from_thread
    STR     r1, [r0]                                 //将r1的值存储到r0，即更新线程栈sp
	

	@ stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	@ tst	r0, #0x20			/* check the T bit */
	@ ldrneh	r0, [lr,#-2]			/* Thumb mode */
	@ bicne	r0, r0, #0xff00			/* Thumb mode */
	@ ldreq	r0, [lr,#-4]			/* ARM mode */
	@ biceq	r0, r0, #0xff000000		/* ARM mode */

switch_to_thread:
	LDR     r1, =cpu_interrupt_to_thread        @//获取线程栈指针到r1
	@//cpu_interrupt_to_thread是一个全局变量，里面存的是线程栈指针SP的指针
	LDR     r1, [r1]         @//加载cpu_interrupt_to_thread的值到r1，即sp指针的指针
	LDR     r1, [r1]          @加载cpu_interrupt_to_thread的值到r1，即sp
	@ LDMFD   r1!, {r4 - r11}   @将线程栈指针r1(操作之前先递减)指向的内容加载到CPU寄存器r4~r11
	ldmia   r1!, {r4 - r11}   @将线程栈指针r1(操作之前先递减)指向的内容加载到CPU寄存器r4~r11

	movs     sp, r1       				@ //将线程栈指针更新到PSP
	@ ldmfd sp!, {r0-r12, lr, pc}^ 

SVC_exit:

	ldmia	sp!,{r0-r3,r12,lr,pc}
    @ ORR     lr, lr, #0x04                             //确保异常返回使用的堆栈指针是PSP，即LR寄存器的位2要为1
    @ BX      lr                                        //异常返回，这个时候任务堆栈中的剩下内容将会自动加载到xPSR，PC（任务入口地址），R14，R12，R3，R2，R1，R0（任务的形参）
	@ movs	pc, lr

	@ ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	@ movs	pc, lr		/*return to the next instruction after the SWI instruction */


DataAbortHandler:				/* Data Abort handler */
#ifdef CONFIG_ARM_ERRATA_775420
	dsb
#endif
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */
	ldr     r0, =DataAbortAddr
	sub     r1, lr, #8
	str     r1, [r0]            		/* Stores instruction causing data abort */

	bl	DataAbortInterrupt		/*DataAbortInterrupt :call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #8			/* points to the instruction that caused the Data Abort exception */

PrefetchAbortHandler:				/* Prefetch Abort handler */
#ifdef CONFIG_ARM_ERRATA_775420
	dsb
#endif
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */
	ldr     r0, =PrefetchAbortAddr
	sub     r1, lr, #4
	str     r1, [r0]            		/* Stores instruction causing prefetch abort */

	bl	PrefetchAbortInterrupt		/* PrefetchAbortInterrupt: call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #4			/* points to the instruction that caused the Prefetch Abort exception */

.end
