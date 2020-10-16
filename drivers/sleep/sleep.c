/*
 * @Author: your name
 * @Date: 2020-08-27 09:53:17
 * @LastEditTime: 2020-08-27 10:41:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\sleep\sleep.c
 */
#include <thunder/sleep.h>
#include <stdio.h>

extern void __attribute__((weak))  _sleep(uint32_t seconds);
extern void __attribute__((weak))  _usleep(uint32_t us);

void sleep(uint32_t seconds)
{
        _sleep(seconds);
}

void usleep(uint32_t us)
{

        _usleep(us);
}

void __attribute__((weak))  _usleep(uint32_t us)
{

    printf("core ERR:no implementation of %s\r\n",__func__);
}

void __attribute__((weak))  _sleep(uint32_t seconds)
{

    printf("core ERR:no implementation of %s\r\n",__func__);
}




