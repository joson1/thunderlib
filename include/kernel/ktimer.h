#include <stdint.h>

#define TIMER_SKIP_LIST_LEVEL 1



typedef struct 
{
    k_list_t list;
    k_list_t row[TIMER_SKIP_LIST_LEVEL];
    void (*timeout_handler)(void *parameter);           /* 超时函数 */
    void            *parameter;                      /* 超时函数形参 */
    uint32_t        init_tick;                      /* 定时器实际需要延时的时间 */
    uint32_t        timeout_tick;                   /* 定时器实际超时时的系统节拍数 */

} ktimer_t;




