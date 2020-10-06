/*
 * @Author: your name
 * @Date: 2020-08-16 19:38:10
 * @LastEditTime: 2020-10-04 21:19:49
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\gpio\devices\gpio-zynq.c
 */
#include <thunder/gpio.h>
#include "zynq/zynq.h"
#include "zynq/gpio.h"
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

struct pinDesc  pin_map[] = 
{
    {
        .pin_id = 0,
        .bank   = &GPIO_BANK1,
        .pin    = BANK1_MIO_50
        
    },
    {
        .pin_id = 1,
        .bank   = &GPIO_BANK1,
        .pin    = BANK1_MIO_51
        
    },
    {
        .pin_id = 2,
        .bank   = &GPIO_BANK0,
        .pin    = BANK0_MIO_7
        
    },

};


