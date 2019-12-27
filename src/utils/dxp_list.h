#ifndef __DXP_LIST_H__
# define __DXP_LIST_H__

# include <stdint.h>

typedef void *dxp_list;
typedef void *dxp_list_iterator;

//
// General stuff
//

// create a new list object
dxp_list dxp_list_new();

// destroy the whole list
int dxp_list_delete(dxp_list l);

// add a new item in the list (at the end)
int dxp_list_push(dxp_list l, void *data);

// return the last element and remove it from the list
void *dxp_list_pop(dxp_list l);

// return the size of the list
uint32_t dxp_list_length(dxp_list l);

// return the data at the given index.
// if the index is negative, we start from the back
void *dxp_list_get(dxp_list l, int index);

//
// Iterator stuff
//

// return a new iterator
dxp_list_iterator dxp_list_begin(dxp_list l);

// return 1 if the iterator is at the end of the list
int dxp_list_end(dxp_list_iterator it);

// move the iterator to the next item
int dxp_list_next(dxp_list_iterator it);

// return the element of the current position of the given iterator
void *dxp_list_data(dxp_list_iterator it);

#endif/*!__DXP_LIST_H__*/
