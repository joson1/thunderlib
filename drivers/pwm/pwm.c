#include <thunder/pwm.h>
#include <stdio.h>
#include <assert.h>



void __attribute__((weak)) pwm_setup(uint8_t id,uint8_t duty,uint32_t freq)
{
    printf("ERR:no device supporting for %s\r\n",__FUNCTION__);
    assert(0);
}
void __attribute__((weak)) pwm_duty_set(uint8_t id,uint8_t duty)
{
    printf("ERR:no device supporting for %s\r\n",__FUNCTION__);
    assert(0);
}
void __attribute__((weak)) pwm_freq_set(uint8_t id,uint32_t freq)
{
    printf("ERR:no device supporting for %s\r\n",__FUNCTION__);
    assert(0);
}

