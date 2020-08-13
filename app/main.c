/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-13 12:01:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include "zynq/sleep.h"
#include <thunder/timer.h>
#include <thunder/serial.h>
#include <stdio.h>
#include <thunder/tty/tty.h>

int main()
{
    // struct serial_dev* usart0;

    // usart0 = serial_open(0,115200);
    // serial_println(usart0,"this is a serial drv test");

    volatile unsigned int* p;
    p = (unsigned int*)0x43C00000;
    *p = 0xf;
  cmd_init();

    // volatile uint32_t* g;
    //  g=(unsigned int*)0xF8000154;
    // *g = 0x00001401;
    while (1)
    {
		sleep(1);
		*p = 1;
    printf("OK\r\n");

		sleep(1);
		*p = 0xf;
    }
    

    return 0;
}
