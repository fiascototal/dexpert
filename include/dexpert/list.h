#ifndef __LIST_H__
# define __LIST_H__

# include <stdint.h>

struct s_list_item
{
    struct s_list_item *next;
    struct s_list_item *pred;
    void               *data;
};

struct s_list
{
    struct s_list_item *head;
    struct s_list_item *tail;
    uint32_t            size;
}; 

// the function pointer used to iterate over a given list (see below)
// if this function return:
//   0  : continue the iteration
// > 0  : break the loop 
typedef int (*f_list_iterator)(
    struct s_list_item *cur_item,       // the current list item
    uint32_t            cur_position,   // the current position inside the list
    void               *priv_data       // some private data, optional
);

// create a new list object
struct s_list *list_new();

// add a new item in the list
int list_add(struct s_list *list, void *data);

// remove the given item from the list
int list_del(struct s_list *list, struct s_list_item *item);

// destroy the whole list
void list_destroy(struct s_list *list);

// loop on all items of the givne list. Use the fct pointer to do some stuffs on each items
int list_iterate(struct s_list *list, f_list_iterator fct, void *priv_data);

#endif/*!__LIST_H__*/
