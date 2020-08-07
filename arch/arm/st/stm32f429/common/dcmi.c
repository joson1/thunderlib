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

    
	GPIO_Init(GPIOA,GPIO_PIN_6,GPIO_MODE_AF,GPIO_OTYPE_OD,GPIO_SPEED_100M,GPIO_PUPD_PD);			//PA6���ù������
	GPIO_Init(GPIOB,GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9,GPIO_MODE_AF,GPIO_OTYPE_OD,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB7/8/9���ù������
	GPIO_Init(GPIOC,GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PC6/7/8/9/11 ���ù������
	GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PD3���ù������
	GPIO_Init(GPIOH,GPIO_PIN_8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PH8���ù������ 
		
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
	//���ԭ�������� 
	DCMI->IER=0x0;
	DCMI->ICR=0x1F;
	DCMI->ESCR=0x0;
	DCMI->ESUR=0x0;
	DCMI->CWSTRTR=0x0;
	DCMI->CWSIZER=0x0; 
	tempreg|=0<<0;		//����ģʽ
	tempreg|=0<<2;		//ȫ֡����
	tempreg|=0<<4;		//Ӳ��ͬ��HSYNC,VSYNC
	tempreg|=1<<5;		//PCLK ��������Ч
	tempreg|=0<<6;		//HSYNC �ߵ�ƽ��Ч һ������
	tempreg|=1<<7;		//VSYNC �͵�ƽ��Ч  һ֡����
	tempreg|=0<<8;		//�������е�֡
	tempreg|=0<<10; 	//8λ���ݸ�ʽ  


	DCMI->IER|=1<<0; 	//����֡�ж�
	tempreg|=1<<14; 	//DCMIʹ��
	DCMI->CR=tempreg;	//����CR�Ĵ���
	MY_NVIC_Init(3,DCMI_IRQn);	//��ռ5
}

void DCMI_StartCampture()
{
    DMA2_Stream1->CR|=1<<0;		//����DMA2,Stream1 
	while (!(DCMI->CR&0x01))
	{
		DCMI->CR|=0x01;
	}
	
	
}

//DCMI,�رմ���
void DCMI_Stop(void)
{
	DCMI->CR&=~(1<<0); 			//DCMI����ر� 
	while(DCMI->CR&0X01);		//�ȴ�������� 
	DMA2_Stream1->CR&=~(1<<0);	//�ر�DMA2,Stream1  	
} 


