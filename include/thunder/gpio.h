/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-01 20:41:35
 * @LastEditTime: 2020-08-02 23:00:07
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \ThunderLib\include\thunder\gpio\gpio.h
 */

#include <stdint.h>

#define GPIO_MODE_OUTPUT    0
#define GPIO_MODE_INPUT     1

#define GPIO_PUPD_NODE      0
#define GPIO_PUPD_PU        1
#define GPIO_PUPD_PD        2


struct pinDef
{
    volatile void*      bank;
    volatile uint32_t   pin;
};


extern void gpio_pin_mode(struct pinDef* pin , uint32_t mode);
extern void gpio_pin_pull(struct pinDef* pin ,uint32_t mode);
extern void gpio_pin_set(struct pinDef* pin);
extern void gpio_pin_reset(struct pinDef* pin);



