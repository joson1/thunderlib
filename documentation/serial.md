<!--
 * @Author: your name
 * @Date: 2020-08-03 21:05:46
 * @LastEditTime: 2020-08-07 21:54:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\documentation\serial.md
-->

```c
#include <thunder/timer.h>
#include <thunder/serial.h>



int main()
{
    struct serial_dev* usart0;

    usart0 = serial_open(0,115200);
    serial_println(usart0,"this is a serial drv test");


    while (1)
    {
        
    }
    

    return 0;
}
```
### int serial_buf_pop(struct serial_dev* dev)
返回接收到的数据 如果没有数据就会返回 -1