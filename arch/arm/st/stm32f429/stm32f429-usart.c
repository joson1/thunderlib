/*
 * @Author: your name
 * @Date: 2020-08-02 23:45:22
 * @LastEditTime: 2020-08-03 00:28:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\stm32f429-usart.c
 */

#include "stm32f429-gpio.h"
#include <thunder/serial.h>

extern void (*_serial_init)(uint32_t);
extern void (*_serial_sendChar)(char);

static void MY_NVIC_Init(uint8_t NVIC_PreemptionPriority,uint8_t NVIC_Channel)	 
{
	uint32_t temp;
	
	temp=NVIC_PreemptionPriority<<(4-4);	  
	temp&=0xf;								//取低四位
	NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;//使能中断位(要清除的话,设置ICER对应位为1即可)
	NVIC->IP[NVIC_Channel]|=temp<<4;				//设置响应优先级和抢断优先级   	    	  				   
}

//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率
void uart_init(uint32_t pclk2, uint32_t bound)
{
	float temp;
	uint16_t mantissa;
	uint16_t fraction;
	temp = (float)(pclk2 * 1000000) / (bound * 16); //得到USARTDIV@OVER8=0
	mantissa = temp;								//得到整数部分
	fraction = (temp - mantissa) * 16;				//得到小数部分@OVER8=0
	mantissa <<= 4;
	mantissa += fraction;
	RCC->AHB1ENR |= 1 << 0;																				   //使能PORTA口时钟
	RCC->APB2ENR |= 1 << 4;																				   //使能串口1时钟
	GPIO_Init(GPIOA,  STM32F429_GPIO_PIN_9 | STM32F429_GPIO_PIN_10,
            STM32F429_GPIO_MODE_AF, STM32F429_GPIO_OTYPE_PP, STM32F429_GPIO_SPEED_50M,
            STM32F429_GPIO_PUPD_PU); //PA9,PA10,复用功能,上拉输出
	GPIO_AF_Set(GPIOA, STM32F429_GPIO_PIN_9, 7);																	   //PA9,AF7
	GPIO_AF_Set(GPIOA, STM32F429_GPIO_PIN_10, 7);																	   //PA10,AF7
																										   //波特率设置
	USART1->BRR = mantissa;																				   //波特率设置
	USART1->CR1 &= ~(1 << 15);																			   //设置OVER8=0
	USART1->CR1 |= 1 << 3;																				   //串口发送使能
																										   //如果使能了接收
	//使能接收中断
	USART1->CR1 |= 1 << 2;		   //串口接收使能
	USART1->CR1 |= 1 << 5;		   //接收缓冲区非空中断使能
	MY_NVIC_Init(3, USART1_IRQn); //组2，最低优先级

	USART1->CR1 |= 1 << 13; //串口使能
}


void stm32f429_serial_init(uint32_t boundRate)
{
    uart_init(90, boundRate);
}

void USART1_IRQHandler(void)
{

	if (USART1->SR & (1 << 5)) //接收到数据
	{
        serial_buf_push(USART1->DR);

	}

}

void SendChar(char ch)
{
	while ((USART1->SR & 0X40) == 0)
		; //循环发送,直到发送完毕
	USART1->DR = (char)ch;

}

void stm32f429_serial()
{
    _serial_init = &stm32f429_serial_init;
    _serial_sendChar = &SendChar;
}