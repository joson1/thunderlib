/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-03 19:50:11
 * @LastEditTime: 2020-08-07 22:52:03
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\drivers\timer\timer.c
 */
#include <thunder/timer.h>
#include <stddef.h>

extern void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)());
void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)())=NULL;



void timer_setup(uint32_t id,uint32_t ms,
                    uint32_t Priority,void (*event_handler)())
{
    if(_timer_setup)
    {
        _timer_setup(id,ms,Priority,event_handler);
    }
}
