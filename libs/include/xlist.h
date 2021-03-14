/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-15 16:11:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/libs/include/list.h
 */
#pragma once
#include <stdint.h>
#include <stddef.h>


#define portMAX_DELAY 0xffffffffU

struct __xList_t;
typedef struct __ListItem_t
{
    uint32_t xItemValue;
    struct __ListItem_t* pxNext;
    struct __ListItem_t* pxPrevious;
    void* Owner;
    struct __xList_t* Container;
} ListItem_t;


/* mini节点结构体定义，作为双向链表的结尾
   因为双向链表是首尾相连的，头即是尾，尾即是头 */
typedef struct __xMListItem_t
{
    uint32_t xItemValue;
    struct __ListItem_t* pxNext;
    struct __ListItem_t* pxPrevious;
} xMListItem_t;

typedef struct __xList_t
{
    uint32_t NumberOfItems; /* 链表节点计数器 */
    ListItem_t* volatile pxIndex;    /* 链表节点索引指针 */
    xMListItem_t xListEnd;  /* 链表最后一个节点 */
} xList_t;


/* 初始化节点的拥有者 */
#define xlistSET_LIST_ITEM_OWNER( pxListItem, pxOwner )		( ( pxListItem )->Owner = ( void * ) ( pxOwner ) )
/* 获取节点拥有者 */
#define xlistGET_LIST_ITEM_OWNER( pxListItem )	( ( pxListItem )->Owner )

/* 初始化节点排序辅助值 */
#define xlistSET_LIST_ITEM_VALUE( pxListItem, xValue )	( ( pxListItem )->xItemValue = ( xValue ) )

/* 获取节点排序辅助值 */
#define xlistGET_LIST_ITEM_VALUE( pxListItem )	( ( pxListItem )->xItemValue )

/* 获取链表根节点的节点计数器的值 */
#define xlistGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )	( ( ( pxList )->xListEnd ).pxNext->xItemValue )

/* 获取链表的入口节点 */
#define xlistGET_HEAD_ENTRY( pxList )	( ( ( pxList )->xListEnd ).pxNext )

/* 获取链表的第一个节点 */
#define xlistGET_NEXT( pxListItem )	( ( pxListItem )->pxNext )

/* 获取链表的最后一个节点 */
#define xlxistGET_END_MARKER( pxList )	( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )

/* 判断链表是否为空 */
#define xlistLIST_IS_EMPTY( pxList )	( ( uint32_t ) ( ( pxList )->NumberOfItems == ( uint32_t ) 0 ) )

/* 获取链表的节点数 */
#define xlistCURRENT_LIST_LENGTH( pxList )	( ( pxList )->NumberOfItems )

/* 获取链表节点的OWNER，即TCB */
#define xlistGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )										\
{																							\
	xList_t * const pxConstList = ( pxList );											    \
	/* 节点索引指向链表第一个节点调整节点索引指针，指向下一个节点，*/       \
    /*如果当前链表有N个节点，当第N次调用该函数时，pxInedex则指向第N个节点 */\
	( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;							\
	/* 当前链表为空 */                                                                       \
	if( !(( pxConstList )->pxIndex->Owner) )	\
	{																						\
		( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;						\
	}																						\
	/* 获取节点的OWNER，即TCB */                                                             \
	( pxTCB ) = ( pxConstList )->pxIndex->Owner;											 \
}

#define xlistGET_OWNER_OF_HEAD_ENTRY( pxList )  ( (&( ( pxList )->xListEnd ))->pxNext->Owner )
#define xlist_for_rach_entry()

void xList_init( xList_t * const pxList );
void xListItem_init( ListItem_t * const pxItem );
void xListInsertEnd( xList_t * const pxList, ListItem_t * const pxNewListItem );
void xListInsert( xList_t * const pxList, ListItem_t * const pxNewListItem );
uint32_t xListRemove( ListItem_t * const pxItemToRemove );

