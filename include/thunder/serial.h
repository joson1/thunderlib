/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-02 23:21:05
 * @LastEditTime: 2020-08-02 23:43:19
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\include\thunder\serial.h
 */
#include <stdint.h>

#define SERIAL_REC_LEN  			512  	// 2^9 定义最大接收字节数 512

void serial_init(uint32_t boundRate);
char serial_buf_pop();
int serial_buf_push(char ch);
