/*
 * @Author: your name
 * @Date: 2020-08-16 19:38:10
 * @LastEditTime: 2021-01-06 13:37:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\gpio\devices\gpio-zynq.c
 */
#include <thunder/gpio.h>
#include "zynq7000/zynq.h"
#include "zynq7000/gpio.h"
#include <stdio.h>

void gpio_pin_mode (uint8_t pin_id, uint32_t mode)
{	volatile uint32_t* oen;
	volatile uint32_t* con;
    if (mode)
    {
        ((GPIO_TypeDef*)(pin_map[pin_id].bank))->controller->DIRM |=(pin_map[pin_id].pin);
        ((GPIO_TypeDef*)(pin_map[pin_id].bank))->controller->OEN  |=(pin_map[pin_id].pin);
    }else
    {
        ((GPIO_TypeDef*)(pin_map[pin_id].bank))->controller->DIRM &= ~(pin_map[pin_id].pin);
        ((GPIO_TypeDef*)(pin_map[pin_id].bank))->controller->OEN  &= ~(pin_map[pin_id].pin);
    }
    
}
void gpio_pin_dir (uint8_t pin_id, uint32_t mode)
{
    gpio_pin_mode(pin_id,mode);

}
void gpio_pin_pull (uint8_t pin_id, uint32_t pull)
{

}

void gpio_pin_set  (uint8_t pin_id)
{

    (*((GPIO_TypeDef*)(pin_map[pin_id].bank))->DATA) |= pin_map[pin_id].pin ;
}

void gpio_pin_reset(uint8_t pin_id)
{
    (*((GPIO_TypeDef*)(pin_map[pin_id].bank))->DATA) &= ~(pin_map[pin_id].pin) ;
}


uint8_t gpio_pin_read(uint8_t pin_id)
{
    // (*((GPIO_TypeDef*)(pin_map[pin_id].bank))->DATA) &= ~(pin_map[pin_id].pin) ;
    if((*((GPIO_TypeDef*)(pin_map[pin_id].bank))->DATA_RO)&&(pin_map[pin_id].pin))
    {    
        return 1;
    }else
    {
        return 0;
    }
    
}


struct pinDesc  pin_map[] = 
{
    {
        .pin_id = 0,
        .bank   = &GPIO_BANK0,
        .pin    = BANK0_MIO_0
        
    },
    {
        .pin_id = 1,
        .bank   = &GPIO_BANK0,
        .pin    = BANK0_MIO_1
        
    },
    {
        .pin_id = 2,
        .bank   = &GPIO_BANK0,
        .pin    = BANK0_MIO_2
        
    },
    {
        .pin_id = 3,
        .bank   = &GPIO_BANK0,
        .pin    = BANK0_MIO_3
        
    },

};


