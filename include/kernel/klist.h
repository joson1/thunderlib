#pragma once

#include "kdefs.h"


struct k_list_node
{
    struct k_list_node *next;             
    struct k_list_node *prev;             
};
typedef struct k_list_node k_list_t;                  

#define k_list_entry(node, type, member) \
    k_container_of(node, type, member)
		


void k_list_init(k_list_t *l);
void k_list_insert_after(k_list_t *l, k_list_t *n);
void k_list_insert_before(k_list_t *l, k_list_t *n);
void k_list_remove(k_list_t *n);