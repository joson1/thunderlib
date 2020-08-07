/*
 * @Author: your name
 * @Date: 2020-08-07 22:16:21
 * @LastEditTime: 2020-08-07 23:18:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\tty\retarget.c
 */
#include <thunder/tty/ttyio.h>
#include <thunder/serial.h>
#include <stdio.h>


struct serial_dev* stty;

void ttyio_init()
{
    
    stty = serial_open(0,115200);
}


uint32_t kbhit()
{

    return serial_input_length(stty);
    
}

/*重定向Printf函数*/
int fputc(int ch, FILE *f)
{
    return serial_sendChar(stty,ch);
}
int fgetc(FILE *f)
{
	return serial_buf_pop(stty);
}

