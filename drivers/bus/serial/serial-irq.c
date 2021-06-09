#include <thunder/irq.h>
#include <thunder/serial.h>



xList_t serial_irq_list;



int serial_irq_request(serial_dev_t* pdev,void* handler)
{
    pdev->irq.handler = handler;
    pdev->irq.setup(pdev,0);
    return pdev->irq.IRQn;
}

