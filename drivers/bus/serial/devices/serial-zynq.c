/*
 * @Author: your name
 * @Date: 2020-08-10 17:15:15
 * @LastEditTime: 2020-10-04 21:17:28
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

extern void zynq_serial_init();

/* ----------USART---------------*/
char BUF_USART0[BUFFER_LEN_USART0]; //接收缓冲.
char BUF_USART1[BUFFER_LEN_USART1]; //接收缓冲.


struct serial_dev dev_usart1;
struct serial_dev dev_usart2;


void usart1_open(uint32_t boundRate)
{
    uart_init(UART1,boundRate);
}

void usart1_putchar(char ch)
{
    uart_send(UART1,ch);
}

int usart1_getchar()
{
    return serial_buf_pop(&dev_usart1);
}


void uart1_handler(void* Data)
{
	char ch;
	// while( !(UART1->Channel_sts&&(1<<1)) )
	// {
		ch = uart_get(UART1);
		usart1_putchar(ch);
		serial_buf_push(&dev_usart1,ch);
	// }
	
	UART1->Chnl_int_sts|=0x1;
}

struct serial_dev dev_usart1 = {

	.id = 0,
	.buffer = BUF_USART0,
	.buffer_length = BUFFER_LEN_USART0,
	.rp = 0,
	.wp = 0,
	.serial_open = &usart1_open,//boundRate
	.putchar     = &usart1_putchar,//boundRate
	.getchar     = &usart1_getchar,//boundRate

};
#define UART1_IER	*((uint32_t *) 0xE0001008)

void zynq_serial_init()
{
	
    serial_dev_attach(&dev_usart1);
	
	UART1->Intrp_en = 0x1;
	UART1_IER = 1;
	UART1->Rcvr_FIFO_trigger_level = 1;
	irq_register(UART1_IRQ,&uart1_handler,TRIGGER_EDGE_HIGHLEVEL);
	ICDDCR[0] = 0x3;
	ICCICR[0] = 0x07;

}
