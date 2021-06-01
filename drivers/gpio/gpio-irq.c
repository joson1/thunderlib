#include <thunder/gpio.h>
#include <thunder/irq.h>


xList_t gpio_irq_list;



void gpio_irq_handler()
{
    struct pinDesc* pPin=0;
    int pin_id;
    pPin = __gpio_irq_lowlevel_match(&gpio_irq_list);
    
    if(pPin){
        pPin->irq_handler();
        __gpio_irq_lowlevel_clear(pPin);

    }
    
}



int gpio_irq_request(int pin_id, int edge, void* handler)
{
    struct pinDesc* pPin=&pin_map[pin_id];
    if(gpio_irq_list.xListEnd.pxNext==0){
        xList_init(&gpio_irq_list);
    }

    pPin->irqitem.xItemValue = 0;  //should be pri 
    pPin->irq_handler = handler;
    __gpio_irq_lowlevel_enable(&pin_map[pin_id],edge);
    
    xlistSET_LIST_ITEM_OWNER(&(pPin->irqitem),pPin);
    xListInsert(&gpio_irq_list,&(pPin->irqitem));

    IRQ_vector_table[ pin_map[pin_id].IRQn ].Handler = gpio_irq_handler;
    // IRQ_vector_table[ pin_map[pin_id].IRQn ].data = &pin_map[pin_id];
    return pin_map[pin_id].IRQn;
}

