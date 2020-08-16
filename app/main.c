/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-16 18:57:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */


#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>

int main()
{
  gpio_pin_mode(0,GPIO_MODE_OUTPUT);
  gpio_pin_set(0);
  gpio_pin_reset(0);
  cmd_init();
  
  return 0;
}
