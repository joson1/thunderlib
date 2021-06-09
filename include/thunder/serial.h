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
#include <thunder/device.h>

#define SERIAL_REC_LEN  			512  	// 2^9 定义最大接收字节数 512

typedef struct 
{
	int (*setup)(int type);  //parameter:interrput type return IRQn
	void (*clear)(void);	 //clear interrupt status

}serial_intdef;

typedef struct __serial_dev serial_dev_t;
struct __serial_dev
{
	uint32_t id;
	char buffer[SERIAL_REC_LEN];
	uint32_t buffer_length;
	uint32_t rp;
	uint32_t wp;

	void* prv_data;

	struct serial_ops
	{
		int (*open)(serial_dev_t* pdev,uint32_t bps);//boundRate
		void (*putchar)(serial_dev_t* pdev,char ch);//
		int (*getchar)(serial_dev_t* pdev);//
	}ops;
	
	struct serial_irq
	{
        uint32_t IRQn;
        uint32_t is_shared;
		int (*setup)(serial_dev_t* pdev, int type); 
        void (*clear)(serial_dev_t* pdev);

    	void (*handler)(serial_dev_t* pdev);

        ListItem_t devItem;
		
	}irq;
	

	ListItem_t devItem;
};

serial_dev_t* serial_open(uint8_t id,uint32_t boundRate);
int serial_buf_pop(serial_dev_t* dev);
int serial_buf_push(serial_dev_t* dev,char ch);
char serial_sendChar(serial_dev_t* dev, char ch);
char serial_getChar(serial_dev_t* dev);
void serial_println(serial_dev_t* dev, char* str);

int serial_dev_attach(serial_dev_t* dev);

int serial_info_register(uint8_t id,void* info);
uint32_t serial_input_length(serial_dev_t* dev);


int serial_irq_request(serial_dev_t* pdev,void* handler);