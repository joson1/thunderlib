/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-01 20:32:15
 * @LastEditTime: 2020-08-16 18:25:30
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \ThunderLib\drivers\gpio\gpio.c
 */
#include <thunder/gpio.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>



struct gpio_dev* gpio_dev_table = NULL;

int  gpio_dev_attach(struct gpio_dev* dev)
{
	struct gpio_dev* p;
	if (gpio_dev_table==NULL)
	{
		gpio_dev_table = dev;
		return 0;
	}else
	{
		p = gpio_dev_table;
		while (p->next!=NULL)
		{
			p = p->next;
		}
		p->next = dev;
		
	}
	return 0;
}

struct gpio_dev* gpio_open(uint8_t id);

int  gpio_dev_register(uint8_t id,void* conf);

void __attribute__((weak)) gpio_pin_init(uint8_t pin_id)
{
    printf("ERR:no device supporting for gpio_pin_init\r\n");
    assert(0);
}