
#include <thunder/delay.h>



void delay_ms(uint32_t ms)
{

    _delay_ms(ms);


}
void delay_us(uint32_t us)
{
    _delay_us(us);
}



void __attribute__((weak)) _delay_ms(uint32_t ms)
{
    printf("core ERR:no implementation of %s\r\n",__func__);
}


void __attribute__((weak)) _delay_us(uint32_t us)
{
    printf("core ERR:no implementation of %s\r\n",__func__);
}





