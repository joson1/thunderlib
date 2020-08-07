/*
 * @Author: your name
 * @Date: 2020-08-03 22:11:32
 * @LastEditTime: 2020-08-07 22:52:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\boards\thunderboards32.c
 */
#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/timer.h"
#include <thunder/serial.h>



#define BUFFER_LEN_USART0  512
#define BUFFER_LEN_USART1  512



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
    uart_init(90, boundRate,1);
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
    uart2_init(45, boundRate,1);
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



void serial_init()
{
    serial_dev_attach(&dev_usart1);
    serial_dev_attach(&dev_usart2);
}

/*-----------------------TIMER-------------------------*/
extern void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)());


void timer_init(uint32_t id,uint32_t ms,
                    uint32_t Priority,void (*event_handler)())
{

    Timer_InitDef timerx = {
        .event_handler = event_handler,
        .ms = ms,
        .Priority = Priority
    };


    switch (id)
    {
    case 1:
        timerx.TIMx = TIM1;
        break;
    case 2:
        timerx.TIMx = TIM2;
        break;
    
    case 3:
        timerx.TIMx = TIM3;
        break;
    case 4:
        timerx.TIMx = TIM4;
        break;
    
    case 5:
        timerx.TIMx = TIM5;
        break;
    
    case 6:
        timerx.TIMx = TIM6;
        break;

    case 7:
        timerx.TIMx = TIM7;
        break;
    case 8:
        timerx.TIMx = TIM8;
        break;
    case 9:
        timerx.TIMx = TIM9;
        break;
    case 10:
        timerx.TIMx = TIM10;
        break;
    case 11:
        timerx.TIMx = TIM11;
        break;
    default:
        break;
    }
    timerInit(&timerx);

}


/*-----------------------  -------------------------*/
void board_init()
{
    serial_init();
	_timer_setup = &timer_init;
}










