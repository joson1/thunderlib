/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-01 20:32:15
 * @LastEditTime: 2020-08-02 23:43:55
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \ThunderLib\drivers\gpio\gpio.c
 */
#include <thunder/gpio.h>




extern void  (*_gpio_pin_mode)(struct pinDef*,uint32_t);
extern void  (*_gpio_pin_pull)(struct pinDef*,uint32_t);
extern void  (*_gpio_pin_set)(struct pinDef*);
extern void  (*_gpio_pin_reset)(struct pinDef*);
void  (*_gpio_pin_mode)(struct pinDef*,uint32_t) = 0;
void  (*_gpio_pin_pull)(struct pinDef*,uint32_t) = 0;
void  (*_gpio_pin_set)(struct pinDef*) = 0;
void  (*_gpio_pin_reset)(struct pinDef*) = 0;



void gpio_pin_mode(struct pinDef* pin , uint32_t mode)
{
    if (_gpio_pin_mode)
    {
        _gpio_pin_mode(pin,mode);
    }
    
}

void gpio_pin_pull(struct pinDef* pin ,uint32_t mode)
{
    if (_gpio_pin_pull)
    {
        _gpio_pin_pull(pin,mode);
    }
    
}
void gpio_pin_set(struct pinDef* pin)
{
    if (_gpio_pin_set)
    {
        _gpio_pin_set(pin);
    }
    
}

void gpio_pin_reset(struct pinDef* pin)
{
    if (_gpio_pin_reset)
    {
        _gpio_pin_reset(pin);
    }
    
}


