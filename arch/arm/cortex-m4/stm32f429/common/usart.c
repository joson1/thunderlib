#include "stm32f429/sys.h"
#include "stm32f429/usart.h"
#include "stm32f429/gpio.h"

//////////////////////////////////////////////////////////////////////////////////
//如果使用ucos,则包括下面的头文件即可.
char INPUT_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.


int GetKey(void)
{

	while (((USART1->SR & 0X20) == 0))
		;
	// tmp = USART1->DR;
	return USART1->DR;
}


int SendChar(int ch)
{
	while ((USART1->SR & 0X40) == 0)
		; //循环发送,直到发送完毕
	USART1->DR = (u8)ch;
	return ch;
}



//////////////////////////////////////////////////////////////////

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
// char USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA = 0; //接收状态标记

//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率
void uart_init(u32 pclk2, u32 bound,uint8_t int_en)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float)(pclk2 * 1000000) / (bound * 16); //得到USARTDIV@OVER8=0
	mantissa = temp;								//得到整数部分
	fraction = (temp - mantissa) * 16;				//得到小数部分@OVER8=0
	mantissa <<= 4;
	mantissa += fraction;
	RCC->AHB1ENR |= 1 << 0;																				   //使能PORTA口时钟
	RCC->APB2ENR |= 1 << 4;																				   //使能串口1时钟
	// GPIO_Init(GPIOA, GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); //PA9,PA10,复用功能,上拉输出
	// GPIO_AF_Set(GPIOA, GPIO_PIN_9, 7);																	   //PA9,AF7
	// GPIO_AF_Set(GPIOA, GPIO_PIN_10, 7);																	   //PA10,AF7
																										   //波特率设置
	USART1->BRR = mantissa;																				   //波特率设置
	USART1->CR1 &= ~(1 << 15);																			   //设置OVER8=0
	USART1->CR1 |= 1 << 3;																				   //串口发送使能
																										   //如果使能了接收
	//使能接收中断
	USART1->CR1 |= 1 << 2;		   //串口接收使能
	USART1->CR1 |= 1 << 5;		   //接收缓冲区非空中断使能

	// if(int_en)
	// 	USART1->CR1 |= 1 << 13; //串口使能
}

char USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
unsigned int uart_rx_rp = 0;
unsigned int uart_rx_wp = 0;


//初始化IO 串口2
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率
void uart2_init(u32 pclk2, u32 bound ,uint8_t int_en)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float)(pclk2 * 1000000) / (bound * 16); //得到USARTDIV@OVER8=0
	mantissa = temp;								//得到整数部分
	fraction = (temp - mantissa) * 16;				//得到小数部分@OVER8=0
	mantissa <<= 4;
	mantissa += fraction;

	RCC->APB1ENR |= 1 << 17;																			  //使能串口1时钟
	GPIO_Init(GPIOA, GPIO_PIN_3 | GPIO_PIN_2, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); //PA9,PA10,复用功能,上拉输出
	GPIO_AF_Set(GPIOA, GPIO_PIN_3, 7);																	  //PA9,AF7
	GPIO_AF_Set(GPIOA, GPIO_PIN_2, 7);																	  //PA10,AF7
																										  //波特率设置
	USART2->BRR = mantissa;																				  //波特率设置
	USART2->CR1 &= ~(1 << 15);																			  //设置OVER8=0
	USART2->CR1 |= 1 << 3;																				  //串口发送使能

	//使能接收中断
	USART2->CR1 |= 1 << 2;		   //串口接收使能
	USART2->CR1 |= 1 << 5;		   //接收缓冲区非空中断使能
	MY_NVIC_Init(15, USART2_IRQn); //组2，最低优先级
	if(int_en)
		USART2->CR1 |= 1 << 13; //串口使能
}

char uart2_getKey()
{
	// unsigned int t = 0;
	if (uart_rx_rp == uart_rx_wp)
	{
		return 0;
	}

	char ch = USART2_RX_BUF[uart_rx_rp & (USART_REC_LEN - 1)];
	uart_rx_rp++;
	return ch;
}

int uart2_putchar(int ch)
{
	while ((USART2->SR & 0X40) == 0)
		; //循环发送,直到发送完毕
	USART2->DR = (u8)ch;
	return ch;
}

void uart2_send(char *pch)
{
	while (*pch)
	{
		uart2_putchar(*pch);
		pch++;
	}
}
//如果缓冲区为空 返回0 如果不空 返回数据量
unsigned int uart2_NumberOfData()
{
	return uart_rx_rp - uart_rx_wp;
}