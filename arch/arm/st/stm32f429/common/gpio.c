#include "stm32f429/gpio.h"


void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u32 GPIO_PIN,u8 GPIO_AF)
{ 
	u8 i = 0;
	for ( i = 0; i < 16; i++)
	{
		if((GPIO_PIN>>i)&0x01)
		{
			GPIOx->AFR[i>>3]&=~(0X0F<<((i&0X07)*4));
			GPIOx->AFR[i>>3]|=(u32)GPIO_AF<<((i&0X07)*4);
		}
	}
}   

void GPIO_Init(GPIO_TypeDef* GPIOx,u32 GPIO_PIN,u32 GPIO_MODE,u32 GPIO_OTYPE,u32 GPIO_SPEED,u32 GPIO_PUPD)
{  

	u32 pinpos=0,pos=0,curpin=0;
	RCC->AHB1ENR |= 1<<(((uint32_t)GPIOx-(uint32_t)GPIOA)/1024);//ʹ��GPIOx��ʱ��
	
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//һ����λ��� 
		curpin=GPIO_PIN&pos;//��������Ƿ�Ҫ����
		if(curpin==pos)	//��Ҫ����
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->MODER|=GPIO_MODE<<(pinpos*2);	//�����µ�ģʽ 
			if((GPIO_MODE==0X01)||(GPIO_MODE==0X02))	//��������ģʽ/���ù���ģʽ
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//���ԭ��������
				GPIOx->OSPEEDR|=(GPIO_SPEED<<(pinpos*2));//�����µ��ٶ�ֵ  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//���ԭ��������
				GPIOx->OTYPER|=GPIO_OTYPE<<pinpos;		//�����µ����ģʽ
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->PUPDR|=GPIO_PUPD<<(pinpos*2);	//�����µ�������
		}
	}
} 


//#define PA(n)    (0X00+n)
void GPIO_PIN_Init(u8 PIN,u32 GPIO_MODE,u32 GPIO_OTYPE,u32 GPIO_SPEED,u32 GPIO_PUPD)
{
	//PA(0)  -->  0x00
	u8 GPIO_X   = PIN>>4;   //0 ~ 8   -->   A ~ I
	u8 GPIO_PIN = PIN&0x0f; //0 ~ 15

	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)(0x40020000+GPIO_X*1024);
	
	RCC->AHB1ENR |= 1<<GPIO_X;		//ʹ��GPIOx��ʱ��

	GPIOx->MODER&=~(3<<(GPIO_PIN*2));	//�����ԭ��������
	GPIOx->MODER|=GPIO_MODE<<(GPIO_PIN*2);	//�����µ�ģʽ 
	if((GPIO_MODE==0X01)||(GPIO_MODE==0X02))	//��������ģʽ/���ù���ģʽ
	{  
		GPIOx->OSPEEDR&=~(3<<(GPIO_PIN*2));	//���ԭ��������
		GPIOx->OSPEEDR|=(GPIO_SPEED<<(GPIO_PIN*2));//�����µ��ٶ�ֵ  
		GPIOx->OTYPER&=~(1<<GPIO_PIN) ;		//���ԭ��������
		GPIOx->OTYPER|=GPIO_OTYPE<<GPIO_PIN;		//�����µ����ģʽ
	}  
	GPIOx->PUPDR&=~(3<<(GPIO_PIN*2));	//�����ԭ��������
	GPIOx->PUPDR|=GPIO_PUPD<<(GPIO_PIN*2);	//�����µ�������
}

void GPIO_PIN_AF_Set(u8 PIN, u8 GPIO_AF)
{
	u8 GPIO_X   = PIN>>4;   //0 ~ 8   -->   A ~ I
	u8 GPIO_PIN = PIN&0x0f; //0 ~ 15

	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)(0x40020000+GPIO_X*1024);

	GPIOx->AFR[GPIO_PIN>>3]&=~(0X0F<<((GPIO_PIN&0X07)*4));
	GPIOx->AFR[GPIO_PIN>>3]|=(u32)GPIO_AF<<((GPIO_PIN&0X07)*4);		
}

void GPIO_Set(GPIO_TypeDef *GPIOx, u16 GPIO_PIN)
{
	GPIOx->ODR |= GPIO_PIN;
}

void GPIO_Rset(GPIO_TypeDef *GPIOx, u16 GPIO_PIN)
{
	GPIOx->ODR &= ~GPIO_PIN;
}
