

#include <thunder/device.h>
#include <stdio.h>

xList_t devList[DEV_NbrOfMAJOR];

static void* devList_find_by_id(xList_t* pDevList,uint32_t id)
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


void* dev_open(uint32_t major,uint32_t id)
{
    void* p = devList_find_by_id(&devList[major],id);
    if (p==0)
    {
        printf("[ERR]Dev major(%ld),id(%ld) not found!\r\n:",major,id);
    }
    
    return p;
}

