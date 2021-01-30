/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2021-01-15 23:29:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <thunder/irq.h>
#include <thunder/dma.h>
#include <zynq7000/axi-dma.h>
#include <zynq7000/xil_cache.h>
#include "zynq7000/xdmaps.h"

#define MAX_PKT_LEN     127 //һ�β��Եĳ���
int ok = 0;
u8 Tries = 6;
int i;
int Index;
// u8 *TxBufferPtr = (u8 *) TX_BUFFER_BASE;
// u8 *RxBufferPtr = (u8 *) RX_BUFFER_BASE;
u8 Value;
 u8 __aligned(4) TxBufferPtr[MAX_PKT_LEN];
 u8 __aligned(4) RxBufferPtr[MAX_PKT_LEN];



void dma_handler()
{

	ok = 1;
}

int main()
{

	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	// irq_register(46,dma_handler,TRIGGER_EDGE_HIGHLEVEL,0,0);
	// irq_register(XPAR_XDMAPS_0_DONE_INTR_0,dma_handler,1,0,0);
	dmac_dev_t* dma = dmac_open(1);

	for (i = 0; i < Tries; i++) {
		Value = 0x55 + (i & 0xFF);
		for (Index = 0; Index < MAX_PKT_LEN; Index++) {
			TxBufferPtr[Index] = Value;

			Value = (Value + 1) & 0xFF;
		}

		// TxBufferPtr[0] = 'h';
	// zynq_dma_start(0,(uint32_t)RxBufferPtr,(uint32_t)TxBufferPtr,MAX_PKT_LEN);
	dma_start(dma,(uint32_t)RxBufferPtr,(uint32_t)TxBufferPtr,MAX_PKT_LEN,dma_handler);

	while(!ok);
	ok = 0;
	}

	while (1)
	{
		/* code */
	}
	

}
