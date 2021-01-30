/*
 * @Author: your name
 * @Date: 2020-08-28 13:45:25
 * @LastEditTime: 2020-08-29 21:55:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\at24cxx\at24cxx.c
 */
#include <thunder/i2c.h>
#include "mtd/at24cxx.h"
#include <stdio.h>
#define AT24C04_ADDRESS 0x50  //7bit


i2c_dev_t* at24;

void at24cxx_init()
{

    at24 = i2c_open(0);

}

void at24cxx_write(uint8_t addr,uint8_t dat)
{
    int res;
    uint8_t buf[2];
    buf[0] = addr;
    buf[1] = dat;
    res =  at24->i2c_wirte(AT24C04_ADDRESS,buf,2);
    if (res!=0)
    {
        printf("ERR:%d\r\n",res);
    }
    
}

uint8_t at24cxx_read(uint8_t addr)
{
    uint8_t buf[1];
    buf[0] = addr;
    at24->i2c_wirte(AT24C04_ADDRESS,buf,1);
    at24->i2c_read(AT24C04_ADDRESS,buf,1);
    return buf[0];
}