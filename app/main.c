/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2021-01-15 23:29:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <thunder/irq.h>
#include <thunder/dma.h>
#include <malloc.h>
#include <thunder/fb.h>
#include <kernel/kernel.h>

#include "drivers/iio/ad9361/AD9361/ad9361.h"
#include "adconf.h"


#define BUF ((uint16_t*)0XC0000000)

struct ad9361_rf_phy *ad9361_phy;

 


int main()
{
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	ad9361_init(&ad9361_phy, &default_init_param);

	while (1)
	{
		/* code */
	}
	
}
