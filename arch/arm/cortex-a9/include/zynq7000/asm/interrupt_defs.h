/*
 * @Author: your name
 * @Date: 2020-08-20 19:42:50
 * @LastEditTime: 2020-09-01 21:28:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\include\zynq\asm\interrupt_defs.h
 */

#include "zynq7000/xparameters_ps.h"
#define MAX_IRQn 92

#define TIMER0_IRQ  XPS_TTC0_0_INT_ID
#define TIMER1_IRQ  XPS_TTC0_1_INT_ID
#define TIMER2_IRQ  XPS_TTC0_2_INT_ID
#define TIMER3_IRQ  XPS_TTC1_0_INT_ID
#define TIMER4_IRQ  XPS_TTC1_1_INT_ID
#define TIMER5_IRQ  XPS_TTC1_2_INT_ID

#define UART0_IRQ 59
#define UART1_IRQ 82


#define TRIGGER_EDGE_HIGHLEVEL      1
#define TRIGGER_EDGE_RISING         3


