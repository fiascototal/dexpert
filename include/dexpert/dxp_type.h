#ifndef __DXP_TYPE_H__
# define __DXP_TYPE_H__

# include <stdint.h>
# include <dexpert/dexfile.h>
# include <dexpert/dxp_string.h>


typedef void *dxp_type;

/*
** list of operators, type manipulations
*/

// allocate a new DXP_TYPE object
dxp_type dxp_type_new(dxp_string s);

// delete an allocated type object
void dxp_type_del(dxp_type t);

// return the string behind the type
dxp_string dxp_type_data(dxp_type t);

// compare 2 types (like strcmp)
int dxp_type_cmp(dxp_type t1, dxp_type t2);


/*
** dexfile related primitives
*/

// add a type in the given dex file
// return the added type, or the existing one
dxp_type dxp_type_add(dexfile_t app, const char *new_item);
dxp_type dxp_type_add2(dexfile_t app, dxp_string new_item);
dxp_type dxp_type_add3(dexfile_t app, dxp_type new_item);

// search the given type in the given dex file
// return NULL if not found
dxp_type dxp_type_find(dexfile_t app, const char *t);
dxp_type dxp_type_find2(dexfile_t app, dxp_type t);

// list iterator
typedef void *dxp_type_iterator;
dxp_type_iterator dxp_type_begin(dexfile_t app);
int               dxp_type_next(dxp_type_iterator it);
int               dxp_type_end(dxp_type_iterator it);
dxp_type          dxp_type_current(dxp_type_iterator it);
void              dxp_type_destroy_iterator(dxp_type_iterator it);

// count of the string table
uint32_t dxp_type_count(dexfile_t app);

#endif/*!__DXP_TYPE_H__*/
