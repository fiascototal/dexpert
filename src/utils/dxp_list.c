#include <stdlib.h>
#include "dxp_list.h"
#include "../debug.h"
#include <dexpert/error_codes.h>


struct s_list_item
{
    struct s_list_item *next;
    struct s_list_item *pred;
    void               *data;
};

struct s_list
{
    f_list_del_item     del_fct;
    struct s_list_item *head;
    struct s_list_item *tail;
    uint32_t            size;
}; 

struct s_list_iterator
{
    struct s_list      *list;
    struct s_list_item *current;
};


//
// General stuff
//

static void _delete_item(struct s_list_item *item)
{
    item->next = NULL;
    item->pred = NULL;
    item->data = NULL;
    free(item);
    item = NULL;
}

void LIST_NO_DEL(void*a){ (void)a; }


// create a new list object
dxp_list dxp_list_new(f_list_del_item del_fct)
{
    struct s_list *result = NULL;

    result = (struct s_list*)malloc(sizeof (struct s_list));
    if (result == NULL)
        return (NULL);

    result->head = NULL;
    result->tail = NULL;
    result->size = 0;
    result->del_fct = del_fct;

    return ((dxp_list)result);
}

// destroy the whole list
int dxp_list_delete(dxp_list l)
{
    struct s_list      *list    = (struct s_list *)l;
    struct s_list_item *current = NULL,
                       *tmp     = NULL;

    CHECK_NULL_FATAL(list);

    if (list->size > 0)
    {
        current = list->head;
        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            list->del_fct(tmp->data);
            _delete_item(tmp);
        }
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    free(list); list = NULL;

    return (ERR_SUCCESS);
}

// add a new item in the list (at the end)
int dxp_list_push(dxp_list l, void *data)
{
    struct s_list      *list = (struct s_list *)l;
    struct s_list_item *item = NULL;

    CHECK_NULL_FATAL(list);

    item = (struct s_list_item *)malloc(sizeof (struct s_list_item));
    if (item == NULL)
        return (ERR_NO_MEMORY);

    item->data = data;
    item->next = NULL;
    item->pred = NULL;

    if (list->size == 0)
    {
        list->head = item;
        list->tail = item;
    }
    else
    {
        list->tail->next = item;
        item->pred = list->tail;
        list->tail = item;
    }
    
    list->size++;

    return (ERR_SUCCESS);
}

// return the last element and remove it from the list
void *dxp_list_pop(dxp_list l)
{
    struct s_list      *list   = (struct s_list *)l;
    struct s_list_item *item   = NULL;
    void               *result = NULL;

    CHECK_NULL_FATAL(list);

    if (list->size == 0 || list->tail == NULL)
        return (NULL);
    
    item = list->tail;

    if (list->size == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {   
        list->tail = item->pred;
        list->tail->next = NULL;
    }
    
    list->size -= 1;
    result = item->data;
    _delete_item(item);

    return (result);
}

// return the size of the list
uint32_t dxp_list_length(dxp_list l)
{
    struct s_list *list = (struct s_list *)l;
    CHECK_NULL_FATAL(list);
    return (list->size);
}

// return the data at the given index.
// if the index is negative, we start from the back
void *dxp_list_get(dxp_list l, int index)
{
    struct s_list      *list     = (struct s_list *)l;
    struct s_list_item *cur_item = NULL;

    CHECK_NULL_FATAL(list);

    if (index > 0)
    {
        if ((uint32_t)index > list->size)
            return (NULL);

        cur_item = list->head;
        while (index > 0)
        {
            cur_item = cur_item->next;
            index--;
        }
        return (cur_item->data);
    }
    else
    {
        index *= -1;
        index -= 1;
        if ((uint32_t)index > list->size)
            return (NULL);

        cur_item = list->tail;
        while (index > 0)
        {
            cur_item = cur_item->pred;
            index--;
        }
        return (cur_item->data);
    }
}


//
// Iterator stuff
//

// return a new iterator
dxp_list_iterator dxp_list_begin(dxp_list l)
{
    struct s_list          *list   = (struct s_list *)l;
    struct s_list_iterator *result = NULL;

    CHECK_NULL_FATAL(list);

    result = (struct s_list_iterator *)malloc(sizeof (struct s_list_iterator));
    result->list = list;
    result->current = list->head;

    return ((dxp_list_iterator)result);
}

// return 1 if the iterator is at the end of the list
int dxp_list_end(dxp_list_iterator it)
{
    struct s_list_iterator *cur_it = (struct s_list_iterator *)it;

    CHECK_NULL_FATAL(cur_it);

    if (cur_it->current == NULL)
    {
        cur_it->current = NULL;
        cur_it->list = NULL;
        free(cur_it); cur_it = NULL;
        return (1);
    }

    return (0);
}

// move the iterator to the next item
int dxp_list_next(dxp_list_iterator it)
{
    struct s_list_iterator *cur_it = (struct s_list_iterator *)it;
    
    CHECK_NULL_FATAL(cur_it);
    
    if (cur_it->current == NULL)
        return (2);
    if (cur_it->current->next == NULL)
        return (ERR_ITEM_NOT_FOUND);
    cur_it->current = cur_it->current->next;

    return (ERR_SUCCESS);
}

// return the element of the current position of the given iterator
void *dxp_list_data(dxp_list_iterator it)
{
    struct s_list_iterator *cur_it = (struct s_list_iterator *)it;
    
    CHECK_NULL_FATAL(cur_it);

    if (cur_it->current == NULL)
        return (NULL);

    return (cur_it->current->data);
}

// destroy an iterator
void dxp_list_destroy_iterator(dxp_list_iterator it)
{
    if (it)
    {
        free(it);
        it = NULL;
    }
}
