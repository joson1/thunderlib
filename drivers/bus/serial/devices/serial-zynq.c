/*
 * @Author: your name
 * @Date: 2020-08-10 17:15:15
 * @LastEditTime: 2020-10-05 19:32:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\serial\devices\serial-zynq.c
 */
#include <thunder/serial.h>
#include "zynq/uart.h"
#include <thunder/interrput.h>
#include <zynq/xil_exception.h>


#define BUFFER_LEN_USART0  512
#define BUFFER_LEN_USART1  512
#define UART1_IER	*((uint32_t *) 0xE0001008)

extern void zynq_serial_init();

/* ----------USART---------------*/
char BUF_USART0[BUFFER_LEN_USART0]; //接收缓冲.
char BUF_USART1[BUFFER_LEN_USART1]; //接收缓冲.


struct serial_dev dev_usart1;
struct serial_dev dev_usart0;


void usart1_open(uint32_t boundRate)
{
    uart_init(UART1,boundRate);
}
void usart0_open(uint32_t boundRate)
{
    uart_init(UART0,boundRate);
}

void usart1_putchar(char ch)
{
    uart_send(UART1,ch);
}
void usart0_putchar(char ch)
{
    uart_send(UART0,ch);
}

int usart1_getchar()
{
    return uart_get(UART1);
}
int usart0_getchar()
{
    return uart_get(UART1);
}


int uart1_interrupt_setup(int type)
{
	
	UART1->Intrp_en = 0x1;
	UART1_IER = 1;
	UART1->Rcvr_FIFO_trigger_level = 1;
	ICDDCR[0] = 0x3;
	ICCICR[0] = 0x07;

	return UART1_IRQ;

}
int uart0_interrupt_setup(int type)
{
	
	UART0->Intrp_en = 0x1;
	// UART1_IER = 1;
	UART0->Intrp_en = 1;
	UART0->Rcvr_FIFO_trigger_level = 1;
	ICDDCR[0] = 0x3;
	ICCICR[0] = 0x07;

	return UART0_IRQ;

}
void uart1_interrupt_clear()
{

	UART1->Chnl_int_sts|=0x1;

}
void uart0_interrupt_clear()
{

	UART0->Chnl_int_sts|=0x1;

}

struct serial_dev dev_usart0 = {

	.id = 0,
	.buffer = BUF_USART0,
	.buffer_length = BUFFER_LEN_USART0,
	.rp = 0,
	.wp = 0,
	.serial_open = &usart0_open,//boundRate
	.putchar     = &usart0_putchar,//boundRate
	.getchar     = &usart0_getchar,//boundRate
	.interrput.setup = &uart0_interrupt_setup,
	.interrput.clear = &uart0_interrupt_clear,


};


struct serial_dev dev_usart1 = {

	.id = 1,
	.buffer = BUF_USART1,
	.buffer_length = BUFFER_LEN_USART1,
	.rp = 0,
	.wp = 0,
	.serial_open = &usart1_open,//boundRate
	.putchar     = &usart1_putchar,//boundRate
	.getchar     = &usart1_getchar,//boundRate
	.interrput.setup = &uart1_interrupt_setup,
	.interrput.clear = &uart1_interrupt_clear,


};


void zynq_serial_init()
{
	
    serial_dev_attach(&dev_usart1);
    serial_dev_attach(&dev_usart0);
	

}
