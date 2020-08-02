/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-02 23:17:45
 * @LastEditTime: 2020-08-02 23:59:59
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\drivers\serial\serial.c
 */
#include <thunder/serial.h>

char INPUT_BUF[SERIAL_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
unsigned int input_rx_rp = 0;
unsigned int input_rx_wp = 0;
char input_state = 0;

extern void (*_serial_init)(uint32_t);
void (*_serial_init)(uint32_t) = 0;

char serial_buf_pop()
{
	unsigned int t = 0;
	if (input_rx_rp == input_rx_wp)
	{
		return 0;
	}

	char ch = INPUT_BUF[input_rx_rp & (SERIAL_REC_LEN - 1)];
	input_rx_rp++;
	return ch;
}

int serial_buf_push(char ch)
{
	if ((input_rx_wp - input_rx_rp) == SERIAL_REC_LEN)
	{
		//buffer full
		return -1;
	}
	else
	{
		INPUT_BUF[input_rx_wp & (SERIAL_REC_LEN - 1)] = ch;
		input_rx_wp++;
	}
    return 0;
}

void serial_init(uint32_t boundRate)
{
    if (_serial_init)
    {
        _serial_init(boundRate);
    }
    
}


