/*
 * @Author: your name
 * @Date: 2020-08-16 11:37:49
 * @LastEditTime: 2020-08-16 19:38:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * 
 * @FilePath: \ThunderLib\drivers\gpio\devices\gpio-stm32f429.c
 */
#include <thunder/gpio.h>
#include "stm32f429/gpio.h"



void gpio_pin_mode (uint8_t pin_id, uint32_t mode)
{
    
    GPIO_Init(
            (GPIO_TypeDef*)(pin_map[pin_id].bank),
            pin_map[pin_id].pin,
            (mode&0x000f),
            (mode&0x00f0)>>4,
            (mode&0x0f00)>>8,
            (mode&0xf000)>>12
    );
}
void gpio_pin_dir (uint8_t pin_id, uint32_t mode)
{
	u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=(pin_map[pin_id].pin)&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->MODER|=(mode&0x000f)<<(pinpos*2);	//设置新的模式 
			if(((mode&0x000f)==0X01)||((mode&0x000f)==0X02))	//如果是输出模式/复用功能模式
			{  
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OSPEEDR|=(((mode&0x0f00)>>8)<<(pinpos*2));//设置新的速度值  
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OTYPER|=((mode&0x00f0)>>4)<<pinpos;		//设置新的输出模式
			}  

		}
	}
}
void gpio_pin_pull (uint8_t pin_id, uint32_t pull)
{
	u32 pinpos=0,pos=0,curpin=0;

	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=(pin_map[pin_id].pin)&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->PUPDR|=pull<<(pinpos*2);	//设置新的上下拉
		}
	}

}

void gpio_pin_set  (uint8_t pin_id)
{
    GPIO_Set( (GPIO_TypeDef*)(pin_map[pin_id].bank),
              pin_map[pin_id].pin);
}

void gpio_pin_reset(uint8_t pin_id)
{
    GPIO_Rset( (GPIO_TypeDef*)(pin_map[pin_id].bank),
               pin_map[pin_id].pin);
}

struct pinDesc  pin_map[] = 
{
    {
        .pin_id = 0,
        .bank   = GPIOA,
        .pin    =GPIO_PIN_0
        
    },
    {
        .pin_id = 1,
        .bank   = GPIOA,
        .pin    =GPIO_PIN_1
        
    },
    {
        .pin_id = 2,
        .bank   = GPIOA,
        .pin    =GPIO_PIN_2
        
    },
};

