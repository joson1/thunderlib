/*
 * @Author: your name
 * @Date: 2019-12-23 14:27:17
 * @LastEditTime: 2020-11-01 12:38:18
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \stm32f429-ac6\HARDWARE\oled\SSD1306.c
 */
#include "ssd1306.h"
#include <stdbool.h>
#include <stdint.h>
#include <thunder/i2c.h>

i2c_dev_t* OLED;

void SSD1306_init()
{
    OLED=i2c_open(0);
}


void SSD1306_writeData(unsigned char _data)
{
    // IIC_start(&OLED);
    // IIC_write(&OLED,SSD1306_SLAVEADDRESS);
    // IIC_wait_ack(&OLED);
    // IIC_write(&OLED,0x40);
    // IIC_wait_ack(&OLED);
    // IIC_write(&OLED,_data);
    // IIC_wait_ack(&OLED);
    // IIC_stop(&OLED);
    uint8_t buf[2];
    buf[0] = 0x40;
    buf[1] = _data;
    OLED->i2c_wirte(OLED,SSD1306_SLAVEADDRESS>>1,buf,2);

}
void SSD1306_writeConnand(unsigned char _cmd)
{

    // IIC_start(&OLED);
    // IIC_write(&OLED,SSD1306_SLAVEADDRESS);
    // IIC_wait_ack(&OLED);
    // IIC_write(&OLED,0x00);
    // IIC_wait_ack(&OLED);
    // IIC_write(&OLED,_cmd);
    // IIC_wait_ack(&OLED);
    // IIC_stop(&OLED);
    uint8_t buf[2];
    buf[0] = 0x00;
    buf[1] = _cmd;
    OLED->i2c_wirte(OLED,SSD1306_SLAVEADDRESS>>1,buf,2);

}

