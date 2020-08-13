/*
 * @Author: your name
 * @Date: 2020-08-10 17:15:15
 * @LastEditTime: 2020-08-10 21:55:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\serial\devices\serial-zynq.c
 */
#include <thunder/serial.h>
#include "zynq/uart.h"



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

void zynq_serial_init()
{
    serial_dev_attach(&dev_usart1);
}
