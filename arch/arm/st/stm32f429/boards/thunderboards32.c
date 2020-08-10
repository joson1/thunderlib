/*
 * @Author: your name
 * @Date: 2020-08-03 22:11:32
 * @LastEditTime: 2020-08-10 16:32:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\boards\thunderboards32.c
 */
#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/timer.h"
#include <thunder/serial.h>




extern void stm32f429_serial_init();
extern void stm32f429_timer_init();


Uart_InitDef uart1_conf = 
{
    .GPIOx_RX  = GPIOA,
    .GPIOx_TX  = GPIOA,
    .PIN_RX    = GPIO_PIN_10,
    .PIN_TX    = GPIO_PIN_9,
    .GPIO_AF   = 7,
    .pclk2     = 90,
    .rx_int_en = 1,
};
Uart_InitDef uart2_conf = 
{
    .GPIOx_RX  = GPIOA,
    .GPIOx_TX  = GPIOA,
    .PIN_RX    = GPIO_PIN_3,
    .PIN_TX    = GPIO_PIN_2,
    .GPIO_AF   = 7,
    .pclk2     = 45,
    .rx_int_en = 1,
};




void board_init()
{
    stm32f429_serial_init();
    serial_dev_register(0,&uart1_conf);
    serial_dev_register(1,&uart2_conf);
	
    
    stm32f429_timer_init();
}










