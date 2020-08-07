<!--
 * @Author: your name
 * @Date: 2020-08-03 21:04:09
 * @LastEditTime: 2020-08-07 23:36:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\documentation\timer.md
-->

# timer

```c


#include <thunder/timer.h>
#include <thunder/serial.h>
struct serial_dev* usart0;


void timer1_handler()
{
    serial_println(usart0,"timer1_handler");
}

int main()
{

    usart0 = serial_open(0,115200);
    serial_println(usart0,"this is a serial drv test");
    usart0->putchar('O');
    usart0->putchar('K');

    timer_setup(1,200,5,&timer1_handler);

    while (1)
    {
        
    }
    

    return 0;
}




```