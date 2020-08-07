/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-02 23:17:45
 * @LastEditTime: 2020-08-07 23:14:02
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\drivers\serial\serial.c
 */
#include <thunder/serial.h>
#include <stddef.h>

char INPUT_BUF[SERIAL_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
unsigned int input_rx_rp = 0;
unsigned int input_rx_wp = 0;
char input_state = 0;

extern void (*_serial_init)(uint32_t);
extern void (*_serial_sendChar)(char);
void (*_serial_init)(uint32_t) = 0;
void (*_serial_sendChar)(char) = 0;


static struct serial_dev* serial_dev_table = NULL;



int serial_dev_attach(struct serial_dev* dev)
{
	struct serial_dev* p;
	if (serial_dev_table==NULL)
	{
		serial_dev_table = dev;
		return 0;
	}else
	{
		p = serial_dev_table;
		while (p->next!=NULL)
		{
			p = p->next;
		}
		p->next = dev;
		
	}
	return 0;
}

/**
 * @description: 
 * @param serial_dev*
 * @return the char that poped out the buf
 */
int serial_buf_pop(struct serial_dev* dev)
{
	char ch;
	// unsigned int t = 0;
	if (dev->rp == dev->wp)
	{
		return 0xffff;
	}
	if (dev->buffer ==0 )
	{
		return 0;
	}
	

	ch = dev->buffer[dev->rp & (dev->buffer_length - 1)];
	dev->rp++;
	return 0x00ff&ch;
}


/**
 * @description: 
 * @param 
 * 	struct serial_dev*
 * 	ch: the char that will be pushed into buffer 
 * @return 
 * 	-1:buffer_full  
 *   0:successfully pushed 
 */
int serial_buf_push(struct serial_dev* dev,char ch)
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

uint32_t serial_input_length(struct serial_dev* dev)
{
	return (dev->wp - dev->rp);
}

/**
 * @description: 
 * @param  uint8_t id
 * @param  uint32_t boundRate
 * @return serial_dev* 
 */
struct serial_dev* serial_open(uint8_t id,uint32_t boundRate)
{
	struct serial_dev* p = serial_dev_table ;
	if (p==NULL)
	{
		//no serial devices;
		return NULL;
	}
	
	while (p->id!=id)
	{
		p = p->next;
		if (p==NULL)
			return NULL;
	}
	if (p->serial_open)
	{
		p->serial_open(boundRate);

		return p;
	}
	//no method to open the device
	return NULL;
}



char serial_sendChar(struct serial_dev* dev, char ch)
{
	dev->putchar(ch);
    return ch;
}
void serial_println(struct serial_dev* dev, char* str)
{

    while (*str)
    {
        dev->putchar(*str);
        str++;
    }
    dev->putchar('\r');
    dev->putchar('\n');
}
char serial_getChar(struct serial_dev* dev)
{
	
    return dev->getchar();
}