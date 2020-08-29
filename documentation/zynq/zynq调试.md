<!--
 * @Author: your name
 * @Date: 2020-08-09 22:24:31
 * @LastEditTime: 2020-08-24 11:39:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\documentation\zynq\zynq调试.md
-->

# zynq 调试

使用xsdb进行调试
1.打开 xsdb

```bash

source E:\\zynqPrj\\TEST_LED_PSPL\\TEST_LED_PSPL.sdk\\system_wrapper_hw_platform_0\\ps7_init.tcl


source F:\\MicroZus01\\Demo\\X_demo\\petalinux_boot2\\petalinux_boot_from_sd\\petalinux_boot_from_sd.sdk\\petalinux_boot_from_sd_wrapper_hw_platform_0\\ps7_init.tcl

connect

target 2

ps7_init

ps7_post_config

rst -processor


stop

dow 二进制文件

con

```


# 测试程序
```c


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



```