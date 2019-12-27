#ifndef __DXP_PROTOTYPE_H__
# define __DXP_PROTOTYPE_H__

# include <stdint.h>
# include <dexpert/dxp_type.h>


typedef void *dxp_prototype;

/*
** list of operators, prototype manipulation
*/

// allocate a new prototype object
dxp_prototype dxp_proto_new(dxp_type return_type);

// append a new type in the argument list
dxp_prototype dxp_proto_add_arg(dxp_prototype p, dxp_type arg_type);

// delete/free a prototype object
void dxp_proto_del(dxp_prototype p);

// return the "return type" of the given prototype
dxp_type dxp_proto_get_ret_type(dxp_prototype p);

// return the number of argument of the given prototype
uint32_t dxp_proto_get_args_count(dxp_prototype p);

// return the argument at the given index
// if the index is negative, it starts from the last argument
dxp_type dxp_proto_get_arg(dxp_prototype p, int idx);

// return the shorty name of the prototype
dxp_string dxp_proto_get_shorty(dxp_prototype p);

// set the shorty name of the given prototype
dxp_prototype dxp_proto_set_shorty(dxp_prototype p, dxp_string s);

// compare 2 prototypes (like strcmp)
int dxp_proto_cmp(dxp_prototype p1, dxp_prototype p2);


/*
** dexfile related primitives
*/

// add a prototype in the given dex file
// return the added item, or the existing one
dxp_prototype dxp_proto_add(dexfile_t app, const char *prototype);
dxp_prototype dxp_proto_add2(dexfile_t app, dxp_prototype new_item);

// search the given prototype in the given dex file
// return NULL if not found
dxp_prototype dxp_proto_find(dexfile_t app, dxp_prototype p);

// size of the prototype array in the given dexfile
uint32_t dxp_proto_count(dexfile_t app);

#endif/*!__DXP_PROTOTYPE_H__*/
