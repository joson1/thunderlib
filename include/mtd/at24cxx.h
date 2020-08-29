/*
 * @Author: your name
 * @Date: 2020-08-29 12:46:02
 * @LastEditTime: 2020-08-29 12:46:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\at24cxx.h
 */


#include <stdint.h>

void at24cxx_init();
void at24cxx_write(uint8_t addr,uint8_t dat);
uint8_t at24cxx_read(uint8_t addr);