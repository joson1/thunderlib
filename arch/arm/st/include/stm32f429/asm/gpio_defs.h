/*
 * @Author: your name
 * @Date: 2020-08-16 17:58:17
 * @LastEditTime: 2020-08-16 18:50:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\asm\gpio_defs.h
 */
#include "stm32f429/gpio.h"

//GPIO设置专用宏定义
// #define GPIO_MODE_IN    	0		//普通输入模式
// #define GPIO_MODE_OUT		1		//普通输出模式
// #define GPIO_MODE_AF		2		//AF功能模式
// #define GPIO_MODE_AIN		3		//模拟输入模式

// #define GPIO_SPEED_2M		0		//GPIO速度2Mhz
// #define GPIO_SPEED_25M		1		//GPIO速度25Mhz
// #define GPIO_SPEED_50M		2		//GPIO速度50Mhz
// #define GPIO_SPEED_100M		3		//GPIO速度100Mhz

// #define GPIO_PUPD_NONE		0		//不带上下拉
// #define GPIO_PUPD_PU		1		//上拉
// #define GPIO_PUPD_PD		2		//下拉
// #define GPIO_PUPD_RES		3		//保留 

// #define GPIO_OTYPE_PP		0		//推挽输出
// #define GPIO_OTYPE_OD		1		//开漏输出 


// GPIO_MODE,u32 GPIO_OTYPE,u32 GPIO_SPEED,u32 GPIO_PUPD)
  
#define MAX_PINS 50

#define GPIO_MODE_INPUT         ((GPIO_PUPD_PU<<12)|(GPIO_SPEED_100M<<8)|(GPIO_OTYPE_PP<<4)|GPIO_MODE_IN)
#define GPIO_MODE_OUTPUT        ((GPIO_PUPD_PU<<12)|(GPIO_SPEED_100M<<8)|(GPIO_OTYPE_PP<<4)|GPIO_MODE_OUT)
#define GPIO_MODE_ALTERFUN      ((GPIO_PUPD_PU<<12)|(GPIO_SPEED_100M<<8)|(GPIO_OTYPE_PP<<4)|GPIO_MODE_AF)



