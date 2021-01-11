#include <thunder/pwm.h>
#include <stdio.h>
#include <assert.h>

static struct pwm_dev* pwm_dev_dev_table = NULL;





/*for user level*/
struct pwm_dev* pwm_open(uint8_t id)
{
	struct pwm_dev* p = pwm_dev_dev_table ;
	if (p==NULL)
	{
        
		//no devices;
		return NULL;
	}
	
	while (p->id!=id)
	{
		p = p->next;
		if (p==NULL)
			return NULL;
	}

    return p;

}
void inline pwm_setup(struct pwm_dev* dev,uint8_t duty,uint32_t freq)
{
    dev->freq = freq;
    dev->duty = duty;
    dev->_setup(duty,freq);
}


int inline pwm_set_duty(struct pwm_dev* dev,uint8_t duty)
{
    dev->duty = duty;
    dev->_set_duty(duty);
}
void inline pwm_freq_set(struct pwm_dev* dev,uint32_t freq)
{
    dev->freq = freq;
    dev->_set_freq(freq);
}
/*for low level*/
int pwm_dev_attach(struct pwm_dev* dev)
{
    struct pwm_dev* p;
	if (pwm_dev_dev_table==NULL)
	{
		pwm_dev_dev_table = dev;
		return 0;
	}else
	{
		p = pwm_dev_dev_table;
		while (p->next!=NULL)
		{
			p = p->next;
		}
		p->next = dev;
		
	}
	return 0;
}



