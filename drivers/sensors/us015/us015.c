#include <thunder/gpio.h>
#include <thunder/sleep.h>
#include "zynq7000/xtime_l.h"
#include <sensors/us015.h>

#include <stdio.h>


unsigned int EchoPin = 2;
unsigned int TrigPin = 3;
unsigned long Time_Echo_us = 0;
unsigned long Len_mm_X100  = 0; //Len_mm_X100 = length*100
unsigned long Len_Integer = 0; //
unsigned int Len_Fraction = 0;
void us015_setup()
{
    
    gpio_pin_mode(EchoPin, GPIO_MODE_INPUT);
    gpio_pin_mode(TrigPin, GPIO_MODE_OUTPUT);
}
#define COUNTS_PER_USECOND  (XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ / (2U*1000000U))


static uint32_t pulseIn(uint8_t pin,uint8_t value)
{
    XTime tStr, tCur;
    gpio_pin_write(pin,value);
    XTime_GetTime(&tStr);

  do
  {
   
  } while (gpio_pin_read(pin)==(value));
    XTime_GetTime(&tCur);
    return (tCur-tStr)/COUNTS_PER_USECOND;
}

//unit: mm
float us015_getDistance()
{
    float tmp;
    gpio_pin_write(TrigPin, HIGH);
    // delayMicroseconds(50);
    usleep(50*1000);
    gpio_pin_write(TrigPin, LOW);
    
    Time_Echo_us = pulseIn(EchoPin, HIGH);
    if((Time_Echo_us < 60000) && (Time_Echo_us > 1))
    {
      Len_mm_X100 = (Time_Echo_us*34)/2;
      return Len_mm_X100/100;
    }
    return 0;
}
void us015_test()
{
    us015_setup();
    while (1)
    {
        sleep(1);
        printf("Distance:%.2f\r\n",us015_getDistance());
    }
    
}
