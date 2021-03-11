#include<thunder/input.h>

input_drv_t input_drv;

int input_dev_register(input_dev_t* dev)
{
	if(input_drv.inputDevList[dev->event_type].xListEnd.pxNext==0)
	{
		xList_init(&(input_drv.inputDevList[dev->event_type]));
	}
	dev->devItem.xItemValue = 0;
	xlistSET_LIST_ITEM_OWNER(&((dev)->devItem),dev); 
	xListInsert(&(input_drv.inputDevList[dev->event_type]),&((dev)->devItem));
	return 0;
}
static void* List_find_by_id(xList_t* pDevList,uint32_t id)
{

    ListItem_t* pxIterator;
    uint32_t i = 0;
		for( pxIterator = ( ListItem_t * ) &( pDevList->xListEnd );
		     i<=pDevList->NumberOfItems; 
			 pxIterator = pxIterator->pxNext )
		{
            if (pxIterator->xItemValue == id)
            {
                return pxIterator->Owner;
            }
            i++;
		}
        return 0;
}

input_dev_t* input_dev_open(uint8_t event_type)
{
	input_drv_t* pdrv = dev_open(DEV_MAJOR_INPUT,0);
	xList_t plist = pdrv->inputDevList[event_type];
	input_dev_t* pdev = List_find_by_id(&plist,0);
	return pdev;
}

input_handler_t* input_open(uint8_t event_type)
{
	input_dev_t* pdev = input_dev_open(event_type);

	return pdev->input_handler;
}
extern void input_drv_attach();

void input_drv_attach()
{
	dev_register(&input_drv,DEV_MAJOR_INPUT,0);
}


