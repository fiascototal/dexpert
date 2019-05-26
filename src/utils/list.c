#include "list.h"
#include "error_codes.h"
#include <stdlib.h>


struct s_list *list_new()
{
    struct s_list *result = NULL;

    result = (struct s_list*)malloc(sizeof (struct s_list));
    if (result == NULL)
        return (NULL);

    result->head = NULL;
    result->tail = NULL;
    result->size = 0;

    return (result);
}

int list_insert(struct s_list *list, void *data)
{
    struct s_list_item *item = NULL;

    if (list == NULL)
        return (ERR_INVALID_ARG);

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