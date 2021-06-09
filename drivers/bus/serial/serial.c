/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-02 23:17:45
 * @LastEditTime: 2020-10-14 14:37:12
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\drivers\serial\serial.c
 */
#include <thunder/serial.h>
#include <stddef.h>
#include <stdio.h>

extern char INPUT_BUF[SERIAL_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
unsigned int input_rx_rp = 0;
unsigned int input_rx_wp = 0;
char input_state = 0;

extern void (*_serial_init)(uint32_t);
extern void (*_serial_sendChar)(char);
void (*_serial_init)(uint32_t) = 0;
void (*_serial_sendChar)(char) = 0;


// static serial_dev_t* serial_dev_table = NULL;


int serial_dev_attach(serial_dev_t* dev)
{

	dev_register(dev,DEV_MAJOR_SERIAL,dev->id);

}
int serial_info_register(uint8_t id,void* info)
{
	return -1;
}
/**
 * @description: 
 * @param serial_dev*
 * @return the char that poped out the buf
 */
int serial_buf_pop(serial_dev_t* dev)
{
	char ch;
	// unsigned int t = 0;
	// while (dev->rp == dev->wp);
	if (dev->rp == dev->wp)
	{
		return -1;
	}
	

	ch = dev->buffer[dev->rp & (dev->buffer_length - 1)];
	dev->rp++;
	return 0x00ff&ch;
}




int serial_buf_push(serial_dev_t* dev,char ch)
{
	if ((dev->wp - dev->rp) == dev->buffer_length)
	{
		//buffer full
		return -1;
	}
	else
	{
		dev->buffer[dev->wp & (dev->buffer_length - 1)] = ch;
		dev->wp++;
	}
    return 0;
}

uint32_t serial_input_length(serial_dev_t* dev)
{
	return (dev->wp - dev->rp);
}



serial_dev_t* serial_open(uint8_t id,uint32_t boundRate)
{
	serial_dev_t* dev = dev_open(DEV_MAJOR_SERIAL,id);
	// dev->serial_open(boundRate);
	dev->ops.open(dev,boundRate);
	return dev;
}



char serial_sendChar(serial_dev_t* dev, char ch)
{
	// dev->putchar(ch);
	dev->ops.putchar(dev,ch);
    return ch;
}
void serial_println(serial_dev_t* dev, char* str)
{

    while (*str)
    {
        // dev->putchar(*str);
		dev->ops.putchar(dev,*str);

        str++;
    }
    dev->ops.putchar(dev,'\r');
    dev->ops.putchar(dev,'\n');
}
char serial_getChar(serial_dev_t* dev)
{
	
    return dev->ops.getchar(dev);
}