#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/gpio.h"
#include <thunder/serial.h>




#define BUFFER_LEN_USART0  512
#define BUFFER_LEN_USART1  512

extern void stm32f429_serial_init();

/* ----------USART---------------*/
char BUF_USART0[BUFFER_LEN_USART0]; //接收缓冲.
char BUF_USART1[BUFFER_LEN_USART1]; //接收缓冲.


struct serial_dev dev_usart1;
struct serial_dev dev_usart2;


void USART1_IRQHandler(void)
{

	if (USART1->SR & (1 << 5)) //接收到数据
	{
        serial_buf_push(&dev_usart1,USART1->DR);

	}

}

void usart1_open(uint32_t boundRate)
{
	
	GPIO_Init(  ((Uart_InitDef *)dev_usart1.dev_init_conf)->GPIOx_RX, 
				((Uart_InitDef *)dev_usart1.dev_init_conf)->PIN_RX, 
				GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 
	GPIO_Init(  ((Uart_InitDef *)dev_usart1.dev_init_conf)->GPIOx_TX, 
				((Uart_InitDef *)dev_usart1.dev_init_conf)->PIN_TX, 
				GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 

	GPIO_AF_Set( ((Uart_InitDef *)dev_usart1.dev_init_conf)->GPIOx_RX,
				 ((Uart_InitDef *)dev_usart1.dev_init_conf)->PIN_RX, 
				 ((Uart_InitDef *)dev_usart1.dev_init_conf)->GPIO_AF );	
				 																   //PA9,AF7
	GPIO_AF_Set( ((Uart_InitDef *)dev_usart1.dev_init_conf)->GPIOx_TX,
				 ((Uart_InitDef *)dev_usart1.dev_init_conf)->PIN_TX, 
				 ((Uart_InitDef *)dev_usart1.dev_init_conf)->GPIO_AF );																	   //PA9,AF7

	
	uart_init(  ((Uart_InitDef *)dev_usart1.dev_init_conf)->pclk2,//90
				boundRate,
				((Uart_InitDef *)dev_usart1.dev_init_conf)->rx_int_en);//1
}

void usart1_putchar(char ch)
{
    while ((USART1->SR & 0X40) == 0)
        ; //循环发送,直到发送完毕
    USART1->DR = (char)ch;

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


void USART2_IRQHandler()
{
	if (USART2->SR & (1 << 5)) //接收到数据
	{
		serial_buf_push(&dev_usart2,USART2->DR);
	}
}

void usart2_open(uint32_t boundRate)
{
	GPIO_Init(  ((Uart_InitDef *)dev_usart2.dev_init_conf)->GPIOx_RX, 
				((Uart_InitDef *)dev_usart2.dev_init_conf)->PIN_RX, 
				GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 
	GPIO_Init(  ((Uart_InitDef *)dev_usart2.dev_init_conf)->GPIOx_TX, 
				((Uart_InitDef *)dev_usart2.dev_init_conf)->PIN_TX, 
				GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); 

	GPIO_AF_Set( ((Uart_InitDef *)dev_usart2.dev_init_conf)->GPIOx_RX,
				 ((Uart_InitDef *)dev_usart2.dev_init_conf)->PIN_RX, 
				 ((Uart_InitDef *)dev_usart2.dev_init_conf)->GPIO_AF );	
				 																
	GPIO_AF_Set( ((Uart_InitDef *)dev_usart2.dev_init_conf)->GPIOx_TX,
				 ((Uart_InitDef *)dev_usart2.dev_init_conf)->PIN_TX, 
				 ((Uart_InitDef *)dev_usart2.dev_init_conf)->GPIO_AF );																	   //PA9,AF7

	
	uart2_init(  ((Uart_InitDef *)dev_usart2.dev_init_conf)->pclk2,//45
				boundRate,
				((Uart_InitDef *)dev_usart2.dev_init_conf)->rx_int_en);//1
}

void usart2_putchar(char ch)
{
    while ((USART2->SR & 0X40) == 0)
        ; //循环发送,直到发送完毕
    USART2->DR = (char)ch;

}

int usart2_getchar()
{
    return serial_buf_pop(&dev_usart2);
}


struct serial_dev dev_usart2 = {

	.id = 1,
	.buffer = BUF_USART1,
	.buffer_length = BUFFER_LEN_USART1,
	.rp = 0,
	.wp = 0,
	.serial_open = &usart2_open,//boundRate
	.putchar     = &usart2_putchar,//boundRate
	.getchar     = &usart2_getchar,//boundRate

};

void stm32f429_serial_init()
{
    serial_dev_attach(&dev_usart1);
    serial_dev_attach(&dev_usart2);
}