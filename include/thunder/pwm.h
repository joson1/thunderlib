#include <stdint.h>
#include <stddef.h>


void pwm_setup(uint8_t id,uint8_t duty,uint32_t freq);
void pwm_duty_set(uint8_t id,uint8_t duty);
void pwm_freq_set(uint8_t id,uint32_t freq);

