/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-02 23:21:05
 * @LastEditTime: 2020-08-24 13:57:24
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\include\thunder\serial.h
 */
#pragma once

#include <stdint.h>

#define SERIAL_REC_LEN  			512  	// 2^9 定义最大接收字节数 512

typedef struct 
{
	int (*setup)(int type);  //parameter:interrput type return IRQn
	void (*clear)(void);	 //clear interrupt status

}serial_intdef;


struct serial_dev
{
	uint8_t id;
	char* buffer;
	uint32_t buffer_length;
	uint32_t rp;
	uint32_t wp;
	void (*serial_open)(uint32_t);//boundRate
	void (*putchar)(char);//
	int (*getchar)(void);//
	void* dev_init_conf ; 
	serial_intdef interrput;
	struct serial_dev* next;
};

struct serial_dev* serial_open(uint8_t id,uint32_t boundRate);
int serial_buf_pop(struct serial_dev* dev);
int serial_buf_push(struct serial_dev* dev,char ch);
char serial_sendChar(struct serial_dev* dev, char ch);
char serial_getChar(struct serial_dev* dev);
void serial_println(struct serial_dev* dev, char* str);

int serial_dev_attach(struct serial_dev* dev);
int serial_dev_register(uint8_t id,void* conf);
uint32_t serial_input_length(struct serial_dev* dev);
