/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-01 20:41:35
 * @LastEditTime: 2021-01-06 13:47:15
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \ThunderLib\include\thunder\gpio\gpio.h
 */

#pragma once

#include <stdint.h>
#include <asm/gpio_defs.h>



struct pinDesc
{
    uint8_t             pin_id;
    volatile void*      bank;
    uint32_t            pin;
    uint32_t            IRQn;
    void (*irq_handler)(void);

};

struct gpio_dev
{
    uint32_t id;
    void* dev_init_conf; 
    struct gpio_dev* next;
};
extern struct pinDesc  pin_map[];
void gpio_pin_init (uint8_t pin_id);
void gpio_pin_mode (uint8_t pin_id, uint32_t mode);
void gpio_pin_pull (uint8_t pin_id , uint32_t pull);
void gpio_pin_set  (uint8_t pin_id);
void gpio_pin_reset(uint8_t pin_id);
uint8_t gpio_pin_read(uint8_t pin_id);
void gpio_pin_write(uint8_t pin_id,uint8_t value);
uint32_t gpio_interrupt_request(uint8_t pin_id, uint8_t edge);
