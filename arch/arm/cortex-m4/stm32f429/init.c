/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-01 19:57:06
 * @LastEditTime: 2020-08-07 00:01:32
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\init.c
 */


#include "stm32f429xx.h" 
#include "stm32f429/sys.h"
#include "stm32f429/gpio.h"
#include <stddef.h>


 
void SystemInit()
{
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));   /* 开启FPUset CP10 and CP11 Full Access*/
	Stm32_Clock_Init(360,25,2,8);//设置时钟,180Mhz
	SysTick->CTRL&=~(1<<2);	
	MY_NVIC_PriorityGroupConfig(4);//设置分组
	GPIO_Init(GPIOA, GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); //PA9,PA10,复用功能,上拉输出

}
