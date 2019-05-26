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

int list_delete(struct s_list *list, struct s_list_item *item)
{
    struct s_list_item *current = NULL;

    if (list == NULL || item == NULL)
        return (ERR_INVALID_ARG);

    if (list->size == 0)
        return (ERR_ITEM_NOT_FOUND);

    if (list->size == 1)
    {
        if (list->head != item)
            return (ERR_ITEM_NOT_FOUND);
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
        if (item->data)
            free(item->data);
        free(item);
    }

    current = list->head;
    while (current->next != NULL)
    {
        if (current == item)
        {
            if (current->pred != NULL)
                current->pred->next = current->next;
            if (current->next != NULL)
                current->next->pred = current->next;
            if (current == list->head)
                list->head = current->next;
            if (current == list->tail)
                list->tail = current->pred;
             
            if (item->data)
            {
                free(item->data);
                item->data = NULL;
            }
            item->next = NULL;
            item->pred = NULL;
            free(item);

            list->size -= 1;
            return (ERR_SUCCESS);
        }

        current = current->next;
    }

    return (ERR_ITEM_NOT_FOUND);
}

int list_destroy(struct s_list *list)
{
    struct s_list_item *current = NULL,
                       *tmp = NULL;

    if (list == NULL)
        return (ERR_INVALID_ARG);

    if (list->size > 0)
    {
        current = list->head;
        while (current->next != NULL)
        {
            tmp = current;
            current = current->next;

            if (tmp->data)
            {
                free(tmp->data);
                tmp->data = NULL;
            }
            tmp->next = NULL;
            tmp->pred = NULL;
            free(tmp);
        }
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    free(list);

    return (ERR_SUCCESS);
}

int list_iterate(struct s_list *list, f_list_iterator fct, void *priv_data)
{
    struct s_list_item *current = NULL;
    uint32_t i = 0;

    if (list == NULL || fct == NULL)
        return (ERR_INVALID_ARG);

    current = list->head;
    while (current != NULL)
    {
        if (fct(current, i, priv_data) != 0)
            break;
            
        i += 1;
        current = current->next;
    }

    return (ERR_SUCCESS);
}
