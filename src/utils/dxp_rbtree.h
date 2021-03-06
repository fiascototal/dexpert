#ifndef __DXP_RBTREE_H__
# define __DXP_RBTREE_H__

# include <stdint.h>

typedef void *dxp_rbtree;
typedef void *dxp_rbtree_iterator;

//
// General stuff
//

// the primitive used to compare 2 nodes (mandatory for the red-black tree)
// if a == b => return 0
// if a < b  => return neg val
// if a > b  => return pos val
typedef int (*f_rbtree_cmp)(void *a, void *b);

// the primitive to delete a node
// can be NULL
typedef void (*f_rbtree_del_node)(void *);


// create a new RBTREE object. Don't forget to add the fct to compare 2 nodes
dxp_rbtree dxp_rbtree_new(f_rbtree_cmp cmp_fct, f_rbtree_del_node del_fct);

// delete the given rbtree (and all nodes)
int dxp_rbtree_delete(dxp_rbtree t);

// add a new element
int dxp_rbtree_insert(dxp_rbtree t, void *data);

// add a new element (same as above) but we don't want duplicate
// we return the already existing one if found
void *dxp_rbtree_insert_unique(dxp_rbtree t, void *data);

// return the size of the rbtree
uint32_t dxp_rbtree_length(dxp_rbtree t);

// find the given data in the rbtree.
// return the data if found, NULL if not
void *dxp_rbtree_find(dxp_rbtree t, void *data);

//
// Iterator stuff
//

// return a new iterator
dxp_rbtree_iterator dxp_rbtree_begin(dxp_rbtree t);

// return 1 if the iterator is at the end of the rbtree
int dxp_rbtree_end(dxp_rbtree_iterator it);

// move the iterator to the next item
int dxp_rbtree_next(dxp_rbtree_iterator it);

// return the element of the current position of the given iterator
void *dxp_rbtree_data(dxp_rbtree_iterator it);

// for debug purpose only
// @{

// print the tree (in DOT format)
// (use the given fct pointer to print the correct data format)
typedef void (*f_rbtree_print_node)(void *node_data);
void dxp_rbtree_print(dxp_rbtree t, f_rbtree_print_node printer, const char *tree_name);

// @}

#endif/*!__DXP_RBTREE_H__*/
