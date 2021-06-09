#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/gpio.h"
#include <thunder/serial.h>
#include <thunder/irq.h>
#include <thunder/device.h>



serial_dev_t dev_usart1;
serial_dev_t dev_usart2;


InterruptTableEntry uart_handler[3];
extern InterruptTableEntry uart_handler[3];
void USART1_IRQHandler(void)
{


	if (USART1->SR & (1 << 5)) //接收到数据
	{
		if (dev_usart1.irq.handler)
		{
			dev_usart1.irq.handler(&dev_usart1);
		}
		USART1->SR &= ~(1 << 5);
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




void usart_interrupt_clear(serial_dev_t* pdev)
{

}





int usart_open(serial_dev_t* pdev,uint32_t bps)
{
	uint32_t pclk;

	USART_TypeDef* USART = (USART_TypeDef*)(pdev->prv_data);
	if(USART==USART1)
	{
		pclk = 90;
	}else{
		pclk = 45;
	}
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float)(pclk * 1000000) / (bps * 16); //得到USARTDIV@OVER8=0
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
	USART->BRR = mantissa;																				   //波特率设置
	USART->CR1 &= ~(1 << 15);																			   //设置OVER8=0
	USART->CR1 |= 1 << 3;																				   //串口发送使能
																										   //如果使能了接收
	//使能接收中断
	USART->CR1 |= 1 << 2;		   //串口接收使能

	USART->CR1 |= 1 << 13; //串口使能

	// uart_init2(90,115200);

}

void usart_putchr(serial_dev_t* pdev,char ch)
{
	USART_TypeDef* USART = (USART_TypeDef*)(pdev->prv_data);
    while ((USART->SR & 0X40) == 0)
        ; //循环发送,直到发送完毕
    USART->DR = (char)ch;
}

int usart_getchr(serial_dev_t* pdev,char ch)
{
	USART_TypeDef* USART = (USART_TypeDef*)(pdev->prv_data);
    return (char)USART->DR;

}

int usart_irq_setup(serial_dev_t* pdev, int type)
{
	USART_TypeDef* USART = (USART_TypeDef*)(pdev->prv_data);
	USART->CR1 |= 1 << 5;		   //接收缓冲区非空中断使能

	MY_NVIC_Init(
				3,
				(pdev->irq.IRQn)); //组2，最低优先级

	USART->CR1 |= 1 << 13; //串口使能0

	return pdev->irq.IRQn;
}

serial_dev_t dev_usart1 = {

	.id = 0,
	.rp = 0,
	.wp = 0,
	.buffer_length = SERIAL_REC_LEN,
	.prv_data = USART1,
	.ops ={
			.open=usart_open,
			.putchar=usart_putchr,
			.getchar=usart_getchr
		}, 
	.irq = {
		.IRQn = USART1_IRQn,
		.is_shared = 0,
		.setup = usart_irq_setup,
		.clear = usart_interrupt_clear,
	}

};


void USART2_IRQHandler()
{
	if (USART2->SR & (1 << 5)) //接收到数据
	{

		if (dev_usart2.irq.handler)
		{
			dev_usart2.irq.handler(&dev_usart2);
		}
		// if(uart_handler[1].Handler)
		// 	uart_handler[1].Handler( uart_handler[1].data  );

	}

}



serial_dev_t dev_usart2 = {


	.id = 1,
	.buffer_length = SERIAL_REC_LEN,
	.prv_data = USART2,
	.rp = 0,
	.wp = 0,
	.ops ={
			.open=usart_open,
			.putchar=usart_putchr,
			.getchar=usart_getchr
		}, 
	.irq = {
		.IRQn = USART1_IRQn,
		.is_shared = 0,
		.setup = usart_irq_setup,
		.clear = usart_interrupt_clear,
	}

};

void stm32f429_serial_init()
{
    serial_dev_attach(&dev_usart1);
    serial_dev_attach(&dev_usart2);
}


DEV_INIT(stm32f429_serial_init);
