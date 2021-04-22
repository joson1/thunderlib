/*
 * @Author: your name
 * @Date: 2020-08-07 22:16:21
 * @LastEditTime: 2020-10-14 14:36:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\tty\retarget.c
 */
#include <thunder/tty/ttyio.h>
#include <thunder/serial.h>
#include <thunder/irq.h>
#include <stdio.h>


serial_dev_t* stty;
#define UART1_IER	*((uint32_t *) 0xE0001008)

void uart_handler(void* Data)
{
	char ch;


		ch = stty->getchar();
		stty->putchar(ch);
		serial_buf_push(stty,ch);
        if (ch=='\r')
        {
            stty->putchar('\n');
		    serial_buf_push(stty,'\n');
        }
        
		stty->interrput.clear();

}

void ttyio_init(uint8_t s_id)
{
    
    stty = serial_open(s_id,115200);
    if(stty)
    {
	irq_register(stty->interrput.setup(0),&uart_handler,TRIGGER_EDGE_HIGHLEVEL,0,0);

    serial_println(stty,"stty ok");

    }

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
    if (stty)
    {
        for (i = 0; i < len; ++i, ptr++)
        {
            serial_sendChar(stty,*ptr);
        }
    }
    
    /* Transmitting a char from UART */

return len;
}

int _read (int fd, const void *buf, size_t count)
{
    int tmp;
    char* buffer = (char*)buf;

    tmp = serial_buf_pop(stty);
    while (tmp==-1)
    {
        tmp = serial_buf_pop(stty);

    }
    buffer[0] = tmp;
  return 1;


}

 
