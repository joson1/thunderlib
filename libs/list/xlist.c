/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-09 22:28:49
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/libs/list/list.c
 */

#include <xlist.h>


/* 链表初始化 */
void xList_init( xList_t * const pxList )
{
	/* 将链表索引指针指向最后一个节点 */
	pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );

	/* 将链表最后一个节点的辅助排序的值设置为最大，确保该节点就是链表的最后节点 */
	pxList->xListEnd.xItemValue = portMAX_DELAY;

    /* 将最后一个节点的pxNext和pxPrevious指针均指向节点自身，表示链表为空 */
	pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );
	pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );

	/* 初始化链表节点计数器的值为0，表示链表为空 */
	pxList->NumberOfItems = 0U;
}

/* 节点初始化 */
void xListItem_init( ListItem_t * const pxItem )
{
	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItem->Container = NULL;
}



/* 将节点插入到链表的尾部 */
void xListInsertEnd( xList_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t * const pxIndex = pxList->pxIndex;//end

	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	pxIndex->pxPrevious->pxNext = pxNewListItem;
	pxIndex->pxPrevious = pxNewListItem;

	/* 记住该节点所在的链表 */
	pxNewListItem->Container = ( void * ) pxList;

	/* 链表节点计数器++ */
	( pxList->NumberOfItems )++;
}


/* 将节点按照升序排列插入到链表 */
void xListInsert( xList_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	/* 获取节点的排序辅助值 */
	const uint32_t xValueOfInsertion = pxNewListItem->xItemValue;

	/* 节点要插入到链表的尾部 */
	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd );
		     pxIterator->pxNext->xItemValue <= xValueOfInsertion; 
			 pxIterator = pxIterator->pxNext )
		{
			/* 没有事情可做，不断迭代只为了找到节点要插入的位置 */			
		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;

	/* 记住该节点所在的链表 */
	pxNewListItem->Container = ( void * ) pxList;

	/* 链表节点计数器++ */
	( pxList->NumberOfItems )++;
}

/* 将节点从链表中删除 */
uint32_t xListRemove( ListItem_t * const pxItemToRemove )
{
	/* 获取节点所在的链表 */
	xList_t * const pxList = ( xList_t * ) pxItemToRemove->Container;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}

	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItemToRemove->Container = NULL;
	
	/* 链表节点计数器-- */
	( pxList->NumberOfItems )--;

	/* 返回链表中剩余节点的个数 */
	return pxList->NumberOfItems;
}


