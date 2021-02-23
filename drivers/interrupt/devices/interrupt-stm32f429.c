#include <thunder/irq.h>
#include "stm32f429/sys.h"
#include "stm32f429/usart.h"





extern InterruptTableEntry uart_handler[3];



int irq_register(uint32_t Irq_id, InterruptHandler handler, uint32_t Trigger_edge, void *Message, void(*CallBack))
{
    switch (Irq_id)
    {
    case USART1_IRQn:
    case USART2_IRQn:
    case USART3_IRQn:
        uart_handler[Irq_id-Irq_id].Handler = handler;
        uart_handler[Irq_id-Irq_id].data    = Message;
        break;

    default:
        break;
    }
}
