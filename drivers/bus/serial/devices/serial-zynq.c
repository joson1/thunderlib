/*
 * @Author: your name
 * @Date: 2020-08-10 17:15:15
 * @LastEditTime: 2020-10-05 19:32:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\serial\devices\serial-zynq.c
 */
#include <thunder/serial.h>
#include "zynq7000/uart.h"
#include <thunder/irq.h>
#include <zynq7000/xil_exception.h>


#define BUFFER_LEN_USART0  512
#define BUFFER_LEN_USART1  512
#define UART1_IER	*((uint32_t *) 0xE0001008)
#define UART0_IER	*((uint32_t *) 0xE0000008)


/* ----------USART---------------*/
// char BUF_USART0[BUFFER_LEN_USART0]; //接收缓冲.
// char BUF_USART1[BUFFER_LEN_USART1]; //接收缓冲.




static int uart1_interrupt_setup(serial_dev_t* pdev, int type)
{
	
	UART1->Intrp_en = 0x1;
	UART1_IER = 1;
	UART1->Rcvr_FIFO_trigger_level = 1;
	ICDDCR[0] = 0x3;
	ICCICR[0] = 0x07;

	return UART1_IRQ;

}
static int uart0_interrupt_setup(serial_dev_t* pdev, int type)
{
	
	UART0->Intrp_en = 0x1;
	UART0_IER = 1;
	UART0->Rcvr_FIFO_trigger_level = 1;
	ICDDCR[0] = 0x3;
	ICCICR[0] = 0x07;

	return UART0_IRQ;

}
static void uart1_interrupt_clear()
{

	UART1->Chnl_int_sts|=0x1;

}
static void uart0_interrupt_clear()
{

	UART0->Chnl_int_sts|=0x1;

}


static int zynq7000_uart_open(serial_dev_t* pdev,uint32_t bps)
{
	typeof(UART0) uart = (typeof(UART0))(pdev->prv_data);
    uart_init(uart,bps);
	return 0;
}


static void zynq7000_uart_putchar(serial_dev_t* pdev,char ch)
{
	typeof(UART0) uart = (typeof(UART0))(pdev->prv_data);
    uart_send(uart,ch);
}

static int zynq7000_uart_getchar(serial_dev_t* pdev)
{
	typeof(UART0) uart = (typeof(UART0))(pdev->prv_data);
    return uart_get(uart);
}

serial_dev_t dev_usart0 = {

	.id = 0,
	.buffer_length = BUFFER_LEN_USART0,
	.rp = 0,
	.wp = 0,
	.prv_data = UART0,
	.ops = {
			.open=zynq7000_uart_open,
			.putchar=zynq7000_uart_putchar,
			.getchar=zynq7000_uart_getchar
	},
	.irq = {
		.IRQn=UART0_IRQ,
		.is_shared = 0,
		.setup=uart0_interrupt_setup,
		.clear=uart0_interrupt_clear
	}

};
serial_dev_t dev_usart1 = {

	.id = 1,
	.buffer_length = BUFFER_LEN_USART1,
	.rp = 0,
	.wp = 0,
	.prv_data = UART1,
	.ops = {
			.open=zynq7000_uart_open,
			.putchar=zynq7000_uart_putchar,
			.getchar=zynq7000_uart_getchar
	},
	.irq = {
		.IRQn=UART1_IRQ,
		.is_shared = 0,
		.setup=uart1_interrupt_setup,
		.clear=uart1_interrupt_clear
	}

};



void zynq_serial_init()
{
	
    serial_dev_attach(&dev_usart1);
    serial_dev_attach(&dev_usart0);
	

}

DEV_INIT(zynq_serial_init);
