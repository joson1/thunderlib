/*
 * @Author: your name
 * @Date: 2020-10-09 09:23:48
 * @LastEditTime: 2020-10-09 10:10:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\sensors\ads1292\ads1292.h
 */
#pragma once


#define ADS1292_REG_ID          0
#define ADS1292_REG_CONFIG1     0x01
#define ADS1292_REG_CONFIG2     0x02
#define ADS1292_REG_LOFF        0x03
#define ADS1292_REG_CH1SET      0x04
#define ADS1292_REG_CH2SET      0x05
#define ADS1292_REG_RLD_SENS    0x06
#define ADS1292_REG_LOFF_SENS   0x07
#define ADS1292_REG_LOFF_STAT   0x08
#define ADS1292_REG_RESP1       0x09
#define ADS1292_REG_RESP2       0x0a
#define ADS1292_REG_GPIO        0x0b

void ads1292_init();
int ads1292_get_id();

