/*
 * @Author: your name
 * @Date: 2020-08-07 22:16:21
 * @LastEditTime: 2020-08-16 22:19:45
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
    serial_println(stty,"stty ok");
}


uint32_t kbhit()
{

    return serial_input_length(stty);
    
}




// void _exit(int x)
// {
//     x=x;
// }

// void _sbrk()
// {

    
// }
// void _write()
// {

    
// }
// void _close()
// {

    
// }

// void _fstat()
// {

    
// }
// void _isatty()
// {

    
// }
// void _lseek()
// {
    
// }

// void _read()
// {
    
// }


/*重定向Printf函数*/
// int fputc(int ch, FILE *f)
// {
//     return serial_sendChar(stty,ch);
// }
// int fgetc(FILE *f)
// {
// 	return serial_buf_pop(stty);
// }

int _write(int file, char *ptr, int len) 
{
    unsigned int i;
//initialize_Uart(de);// NOT REQUIRED as UBOOT has already done the job.

    /* Transmitting a char from UART */
    for (i = 0; i < len; ++i, ptr++)
    {
        serial_sendChar(stty,*ptr);
    }
return len;
}