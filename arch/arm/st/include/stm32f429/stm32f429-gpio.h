/*
 * @Author: alanwake@ThunderIndustry
 * @Date: 2020-08-02 21:03:41
 * @LastEditTime: 2020-08-03 00:10:20
 * @LastEditors: Please set LastEditors
 * @Description: gpio definenation for stm32f429
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\stm32f429-gpio.h
 */


#include "stm32f429xx.h"

//GPIO引脚编号定义
#define STM32F429_GPIO_PIN_0				1<<0
#define STM32F429_GPIO_PIN_1				1<<1
#define STM32F429_GPIO_PIN_2				1<<2
#define STM32F429_GPIO_PIN_3				1<<3
#define STM32F429_GPIO_PIN_4				1<<4
#define STM32F429_GPIO_PIN_5				1<<5
#define STM32F429_GPIO_PIN_6				1<<6
#define STM32F429_GPIO_PIN_7				1<<7
#define STM32F429_GPIO_PIN_8				1<<8
#define STM32F429_GPIO_PIN_9				1<<9
#define STM32F429_GPIO_PIN_10				1<<10
#define STM32F429_GPIO_PIN_11				1<<11
#define STM32F429_GPIO_PIN_12				1<<12
#define STM32F429_GPIO_PIN_13				1<<13
#define STM32F429_GPIO_PIN_14				1<<14
#define STM32F429_GPIO_PIN_15				1<<15 
#define STM32F429_GPIO_PIN_LSB             0x00ff
#define STM32F429_GPIO_PIN_MSB             0xff00
#define STM32F429_GPIO_PIN_ALL             0xffff


//GPIO设置专用宏定义
#define STM32F429_GPIO_MODE_IN    	    0		//普通输入模式
#define STM32F429_GPIO_MODE_OUT		    1		//普通输出模式
#define STM32F429_GPIO_MODE_AF		    2		//AF功能模式
#define STM32F429_GPIO_MODE_AIN		    3		//模拟输入模式

#define STM32F429_GPIO_SPEED_2M		    0		//GPIO速度2Mhz
#define STM32F429_GPIO_SPEED_25M		1		//GPIO速度25Mhz
#define STM32F429_GPIO_SPEED_50M		2		//GPIO速度50Mhz
#define STM32F429_GPIO_SPEED_100M		3		//GPIO速度100Mhz

#define STM32F429_GPIO_PUPD_NONE		0		//不带上下拉
#define STM32F429_GPIO_PUPD_PU		    1		//上拉
#define STM32F429_GPIO_PUPD_PD		    2		//下拉
#define STM32F429_GPIO_PUPD_RES		    3		//保留 

#define STM32F429_GPIO_OTYPE_PP		    0		//推挽输出
#define STM32F429_GPIO_OTYPE_OD		    1		//开漏输出 

void stm32f429_gpio();
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,uint32_t GPIO_PIN,uint8_t GPIO_AF);
void GPIO_Init(GPIO_TypeDef* GPIOx,uint32_t GPIO_PIN,uint32_t GPIO_MODE,
                        uint32_t GPIO_OTYPE,uint32_t GPIO_SPEED,uint32_t GPIO_PUPD);
void GPIO_PIN_AF_Set(uint8_t PIN, uint8_t GPIO_AF);


