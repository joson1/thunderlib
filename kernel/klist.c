#include <kernel/klist.h>



inline void k_list_init(k_list_t *l)
{
    l->next = l->prev = l;
}


inline void k_list_insert_after(k_list_t *l, k_list_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

inline void k_list_insert_before(k_list_t *l, k_list_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}
inline void k_list_remove(k_list_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}
