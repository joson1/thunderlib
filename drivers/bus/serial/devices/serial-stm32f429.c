#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/gpio.h"
#include <thunder/serial.h>
#include <thunder/irq.h>
#include <thunder/device.h>

#define BUFFER_LEN_USART0  512
#define BUFFER_LEN_USART1  512

extern void stm32f429_serial_init();

/* ----------USART---------------*/
char BUF_USART0[BUFFER_LEN_USART0]; //接收缓冲.
char BUF_USART1[BUFFER_LEN_USART1]; //接收缓冲.


serial_dev_t dev_usart1;
serial_dev_t dev_usart2;


InterruptTableEntry uart_handler[3];
extern InterruptTableEntry uart_handler[3];
void USART1_IRQHandler(void)
{


	if (USART1->SR & (1 << 5)) //接收到数据
	{
		if(uart_handler[0].Handler)
			uart_handler[0].Handler( uart_handler[0].data  );

	}

}

void USART3_IRQHandler(void)
{

	if (USART3->SR & (1 << 5)) //接收到数据
	{
		if(uart_handler[2].Handler)
			uart_handler[2].Handler( uart_handler[2].data  );

	}

}

void usart1_open(uint32_t boundRate)
{
	
	// GPIO_Init(  ((Uart_InitDef *)dev_usart1.serial_init_info)->GPIOx_RX, 
	// 			((Uart_InitDef *)dev_usart1.serial_init_info)->PIN_RX, 
	// 			GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 
	// GPIO_Init(  ((Uart_InitDef *)dev_usart1.serial_init_info)->GPIOx_TX, 
	// 			((Uart_InitDef *)dev_usart1.serial_init_info)->PIN_TX, 
	// 			GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 

	// GPIO_AF_Set( ((Uart_InitDef *)dev_usart1.serial_init_info)->GPIOx_RX,
	// 			 ((Uart_InitDef *)dev_usart1.serial_init_info)->PIN_RX, 
	// 			 ((Uart_InitDef *)dev_usart1.serial_init_info)->GPIO_AF );	
	// 			 																   //PA9,AF7
	// GPIO_AF_Set( ((Uart_InitDef *)dev_usart1.serial_init_info)->GPIOx_TX,
	// 			 ((Uart_InitDef *)dev_usart1.serial_init_info)->PIN_TX, 
	// 			 ((Uart_InitDef *)dev_usart1.serial_init_info)->GPIO_AF );																	   //PA9,AF7

	
	uart_init(  90,//90
				boundRate,
				1);//1
}

void usart1_putchar(char ch)
{
    while ((USART1->SR & 0X40) == 0)
        ; //循环发送,直到发送完毕
    USART1->DR = (char)ch;

}

int usart1_getchar()
{
    return (char)USART1->DR;
}


uint32_t usart1_interrupt_setup()
{
	USART1->CR1 |= 1 << 13; //串口使能
	MY_NVIC_Init(
				((Uart_InitDef *)dev_usart1.serial_init_info)->Priority,
				USART1_IRQn); //组2，最低优先级

	return USART1_IRQn;
}

void usart1_interrupt_clear()
{

}

serial_dev_t dev_usart1 = {

	.id = 0,
	.buffer = BUF_USART0,
	.buffer_length = BUFFER_LEN_USART0,
	.rp = 0,
	.wp = 0,
	.serial_open = &usart1_open,//boundRate
	.putchar     = &usart1_putchar,//boundRate
	.getchar     = &usart1_getchar,//boundRate
	.interrput.setup = &usart1_interrupt_setup,
	.interrput.clear = &usart1_interrupt_clear,

};


void USART2_IRQHandler()
{
	if (USART2->SR & (1 << 5)) //接收到数据
	{
		if(uart_handler[1].Handler)
			uart_handler[1].Handler( uart_handler[1].data  );

	}

}

void usart2_open(uint32_t boundRate)
{
	// GPIO_Init(  ((Uart_InitDef *)dev_usart2.serial_init_info)->GPIOx_RX, 
	// 			((Uart_InitDef *)dev_usart2.serial_init_info)->PIN_RX, 
	// 			GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 
	// GPIO_Init(  ((Uart_InitDef *)dev_usart2.serial_init_info)->GPIOx_TX, 
	// 			((Uart_InitDef *)dev_usart2.serial_init_info)->PIN_TX, 
	// 			GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 

	// GPIO_AF_Set( ((Uart_InitDef *)dev_usart2.serial_init_info)->GPIOx_RX,
	// 			 ((Uart_InitDef *)dev_usart2.serial_init_info)->PIN_RX, 
	// 			 ((Uart_InitDef *)dev_usart2.serial_init_info)->GPIO_AF );	
				 																
	// GPIO_AF_Set( ((Uart_InitDef *)dev_usart2.serial_init_info)->GPIOx_TX,
	// 			 ((Uart_InitDef *)dev_usart2.serial_init_info)->PIN_TX, 
	// 			 ((Uart_InitDef *)dev_usart2.serial_init_info)->GPIO_AF );																	   //PA9,AF7

	
	uart2_init(  ((Uart_InitDef *)dev_usart2.serial_init_info)->pclk2,//45
				boundRate,
				((Uart_InitDef *)dev_usart2.serial_init_info)->rx_int_en);//1
}

void usart2_putchar(char ch)
{
    while ((USART2->SR & 0X40) == 0)
        ; //循环发送,直到发送完毕
    USART2->DR = (char)ch;

}

int usart2_getchar()
{
    return (char)USART2->DR;
}

uint32_t usart2_interrupt_setup()
{
	USART2->CR1 |= 1 << 13; //串口使能
	MY_NVIC_Init(
		((Uart_InitDef *)dev_usart2.serial_init_info)->Priority,
		 USART2_IRQn); //组2，最低优先级

	return USART2_IRQn;
}

void usart2_interrupt_clear()
{
	
}
serial_dev_t dev_usart2 = {

	.id = 1,
	.buffer = BUF_USART1,
	.buffer_length = BUFFER_LEN_USART1,
	.rp = 0,
	.wp = 0,
	.serial_open = &usart2_open,//boundRate
	.putchar     = &usart2_putchar,//boundRate
	.getchar     = &usart2_getchar,//boundRate
	.interrput.setup = &usart2_interrupt_setup,
	.interrput.clear = &usart2_interrupt_clear,

};

void stm32f429_serial_init()
{
    serial_dev_attach(&dev_usart1,0);
    serial_dev_attach(&dev_usart2,0);
}


DEV_INIT(stm32f429_serial_init);
