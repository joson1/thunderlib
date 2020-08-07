/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:11
 * @LastEditTime: 2020-08-06 23:20:21
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\common\dcmi.c
 */
#include "stm32f429/dcmi.h"
#include "stm32f429/gpio.h"
// OV_D0~D7  ------------  PB8/PB9/PD3/PC11/PC9/PC8/PC7/PC6
// OV_SCL    ------------  PB4
// OV_SDA    ------------  PB3
// OV_VSYNC  ------------  PB7
// OV_HREF   ------------  PH8
// OV_RESET  ------------  PA15
// OV_PCLK   ------------  PA6
void DCMI_Init()
{
    u32 tempreg = 0;

    
	GPIO_Init(GPIOA,GPIO_PIN_6,GPIO_MODE_AF,GPIO_OTYPE_OD,GPIO_SPEED_100M,GPIO_PUPD_PD);			//PA6复用功能输出
	GPIO_Init(GPIOB,GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9,GPIO_MODE_AF,GPIO_OTYPE_OD,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB7/8/9复用功能输出
	GPIO_Init(GPIOC,GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PC6/7/8/9/11 复用功能输出
	GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PD3复用功能输出
	GPIO_Init(GPIOH,GPIO_PIN_8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PH8复用功能输出 
		
	GPIO_AF_Set(GPIOH,GPIO_PIN_8,13);	//PH8,AF13  DCMI_HSYNC
	GPIO_AF_Set(GPIOA,GPIO_PIN_6,13);	//PA6,AF13  DCMI_PCLK  
	GPIO_AF_Set(GPIOB,GPIO_PIN_7,13);	//PB7,AF13  DCMI_VSYNC  
 	GPIO_AF_Set(GPIOC,GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11,13);	//PC6,AF13  DCMI_D0
                                                                                    //PC7,AF13  DCMI_D1
                                                                                    //PC8,AF13  DCMI_D2
                                                                                    //PC9,AF13  DCMI_D3
                                                                                    //PC11,AF13 DCMI_D4 
	GPIO_AF_Set(GPIOD,GPIO_PIN_3,13);	//PD3,AF13  DCMI_D5
	GPIO_AF_Set(GPIOB,GPIO_PIN_8,13);	//PB8,AF13  DCMI_D6
	GPIO_AF_Set(GPIOB,GPIO_PIN_9,13);	//PB9,AF13  DCMI_D

	RCC->AHB2ENR |= 0x01;
	//清除原来的设置 
	DCMI->IER=0x0;
	DCMI->ICR=0x1F;
	DCMI->ESCR=0x0;
	DCMI->ESUR=0x0;
	DCMI->CWSTRTR=0x0;
	DCMI->CWSIZER=0x0; 
	tempreg|=0<<0;		//连续模式
	tempreg|=0<<2;		//全帧捕获
	tempreg|=0<<4;		//硬件同步HSYNC,VSYNC
	tempreg|=1<<5;		//PCLK 上升沿有效
	tempreg|=0<<6;		//HSYNC 高电平有效 一行像素
	tempreg|=1<<7;		//VSYNC 低电平有效  一帧像素
	tempreg|=0<<8;		//捕获所有的帧
	tempreg|=0<<10; 	//8位数据格式  


	DCMI->IER|=1<<0; 	//开启帧中断
	tempreg|=1<<14; 	//DCMI使能
	DCMI->CR=tempreg;	//设置CR寄存器
	MY_NVIC_Init(3,DCMI_IRQn);	//抢占5
}

void DCMI_StartCampture()
{
    DMA2_Stream1->CR|=1<<0;		//开启DMA2,Stream1 
	while (!(DCMI->CR&0x01))
	{
		DCMI->CR|=0x01;
	}
	
	
}

//DCMI,关闭传输
void DCMI_Stop(void)
{
	DCMI->CR&=~(1<<0); 			//DCMI捕获关闭 
	while(DCMI->CR&0X01);		//等待传输结束 
	DMA2_Stream1->CR&=~(1<<0);	//关闭DMA2,Stream1  	
} 


