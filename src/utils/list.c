#include "list.h"
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
