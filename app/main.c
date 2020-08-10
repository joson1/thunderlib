/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-10 16:58:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

// #include "zynq/sleep.h"
#include <thunder/timer.h>
#include <thunder/serial.h>



int main()
{
    struct serial_dev* usart0;

    usart0 = serial_open(1,115200);
    serial_println(usart0,"this is a serial drv test");
    usart0->putchar('O');
    usart0->putchar('K');

    while (1)
    {
        
    }
    

    return 0;
}
