/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-02 21:44:48
 * @LastEditTime: 2020-08-03 00:10:11
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\stm32f429-gpio.c
 */

#include <thunder/gpio.h>
#include "stm32f429-gpio.h"

extern void  (*_gpio_pin_mode)(struct pinDef*,uint32_t);
extern void  (*_gpio_pin_pull)(struct pinDef*,uint32_t);
extern void  (*_gpio_pin_set)(struct pinDef*);
extern void  (*_gpio_pin_reset)(struct pinDef*);


void GPIO_AF_Set(GPIO_TypeDef* GPIOx,uint32_t GPIO_PIN,uint8_t GPIO_AF)
{ 
	uint8_t i = 0;
	for ( i = 0; i < 16; i++)
	{
		if((GPIO_PIN>>i)&0x01)
		{
			GPIOx->AFR[i>>3]&=~(0X0F<<((i&0X07)*4));
			GPIOx->AFR[i>>3]|=(uint32_t)GPIO_AF<<((i&0X07)*4);
		}
	}
}   

void GPIO_Init(GPIO_TypeDef* GPIOx,uint32_t GPIO_PIN,uint32_t GPIO_MODE,uint32_t GPIO_OTYPE,uint32_t GPIO_SPEED,uint32_t GPIO_PUPD)
{  

	uint32_t pinpos=0,pos=0,curpin=0;
	RCC->AHB1ENR |= 1<<(((uint32_t)GPIOx-(uint32_t)GPIOA)/1024);//使能GPIOx的时钟
	
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=GPIO_PIN&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->MODER|=GPIO_MODE<<(pinpos*2);	//设置新的模式 
			if((GPIO_MODE==0X01)||(GPIO_MODE==0X02))	//如果是输出模式/复用功能模式
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				GPIOx->OSPEEDR|=(GPIO_SPEED<<(pinpos*2));//设置新的速度值  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				GPIOx->OTYPER|=GPIO_OTYPE<<pinpos;		//设置新的输出模式
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->PUPDR|=GPIO_PUPD<<(pinpos*2);	//设置新的上下拉
		}
	}
} 


//#define PA(n)    (0X00+n)
static inline void GPIO_PIN_Init(uint8_t PIN,uint32_t GPIO_MODE,uint32_t GPIO_OTYPE,uint32_t GPIO_SPEED,uint32_t GPIO_PUPD)
{
	//PA(0)  -->  0x00
	uint8_t GPIO_X   = PIN>>4;   //0 ~ 8   -->   A ~ I
	uint8_t GPIO_PIN = PIN&0x0f; //0 ~ 15

	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)(0x40020000+GPIO_X*1024);
	
	RCC->AHB1ENR |= 1<<GPIO_X;		//使能GPIOx的时钟

	GPIOx->MODER&=~(3<<(GPIO_PIN*2));	//先清除原来的设置
	GPIOx->MODER|=GPIO_MODE<<(GPIO_PIN*2);	//设置新的模式 
	if((GPIO_MODE==0X01)||(GPIO_MODE==0X02))	//如果是输出模式/复用功能模式
	{  
		GPIOx->OSPEEDR&=~(3<<(GPIO_PIN*2));	//清除原来的设置
		GPIOx->OSPEEDR|=(GPIO_SPEED<<(GPIO_PIN*2));//设置新的速度值  
		GPIOx->OTYPER&=~(1<<GPIO_PIN) ;		//清除原来的设置
		GPIOx->OTYPER|=GPIO_OTYPE<<GPIO_PIN;		//设置新的输出模式
	}  
	GPIOx->PUPDR&=~(3<<(GPIO_PIN*2));	//先清除原来的设置
	GPIOx->PUPDR|=GPIO_PUPD<<(GPIO_PIN*2);	//设置新的上下拉
}

void GPIO_PIN_AF_Set(uint8_t PIN, uint8_t GPIO_AF)
{
	uint8_t GPIO_X   = PIN>>4;   //0 ~ 8   -->   A ~ I
	uint8_t GPIO_PIN = PIN&0x0f; //0 ~ 15

	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)(0x40020000+GPIO_X*1024);

	GPIOx->AFR[GPIO_PIN>>3]&=~(0X0F<<((GPIO_PIN&0X07)*4));
	GPIOx->AFR[GPIO_PIN>>3]|=(uint32_t)GPIO_AF<<((GPIO_PIN&0X07)*4);		
}

static inline void GPIO_Set(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
	GPIOx->ODR |= GPIO_PIN;
}

static inline void GPIO_Rset(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
	GPIOx->ODR &= ~GPIO_PIN;
}

static void stm32f429_gpio_pin_mode(struct pinDef* pin , uint32_t mode)
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)pin->bank;
    uint32_t GPIO_PIN = pin->pin;
    uint32_t pmode = (mode==GPIO_MODE_INPUT)?STM32F429_GPIO_MODE_IN:STM32F429_GPIO_MODE_OUT; 
	RCC->AHB1ENR |= 1<<(((uint32_t)GPIOx-(uint32_t)GPIOA)/1024);//使能GPIOx的时钟
    
    GPIO_Init(GPIOx,GPIO_PIN,pmode,
                STM32F429_GPIO_OTYPE_PP,
                STM32F429_GPIO_SPEED_50M,
                STM32F429_GPIO_PUPD_PU);
}

static void stm32f429_gpio_pin_pull(struct pinDef* pin ,uint32_t pull)
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)pin->bank;
    uint32_t GPIO_PIN = pin->pin;

    GPIOx->PUPDR&=~(3<<(GPIO_PIN*2));	//先清除原来的设置
	GPIOx->PUPDR|=pull<<(GPIO_PIN*2);	//设置新的上下拉
}
static void stm32f429_gpio_pin_set(struct pinDef* pin)
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)pin->bank;
    GPIOx->ODR |= pin->pin;
}

static void stm32f429_gpio_pin_reset(struct pinDef* pin)
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)pin->bank;
    uint32_t GPIO_PIN = pin->pin;
    GPIOx->ODR &= ~pin->pin;
}


void stm32f429_gpio()
{
    _gpio_pin_mode = &stm32f429_gpio_pin_mode;
    _gpio_pin_pull = &stm32f429_gpio_pin_pull;
    _gpio_pin_set  = &stm32f429_gpio_pin_set;
    _gpio_pin_reset  = &stm32f429_gpio_pin_reset;
}
