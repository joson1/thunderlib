#include <stdint.h>
#include <stddef.h>



struct pwm_dev
{
	uint8_t id;
    uint32_t freq;
    uint8_t duty;
	void (*_setup)(uint8_t duty,uint32_t freq);//
	int (*_set_duty)(uint8_t duty);//
	int (*_set_freq)(uint32_t freq);//

	struct pwm_dev* next;
};

/*for user level*/
struct pwm_dev* pwm_open(uint8_t id);
void pwm_setup(struct pwm_dev* dev,uint8_t duty,uint32_t freq);


int pwm_set_duty(struct pwm_dev* dev,uint8_t duty);
void pwm_freq_set(struct pwm_dev* dev,uint32_t freq);

/*for low level*/
int pwm_dev_attach(struct pwm_dev* dev);


