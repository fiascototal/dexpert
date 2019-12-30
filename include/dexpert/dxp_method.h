#ifndef __DXP_METHOD_H__
# define __DXP_METHOD_H__

# include <dexpert/dexfile.h>
# include <dexpert/dxp_type.h>
# include <dexpert/dxp_string.h>
# include <dexpert/dxp_prototype.h>


typedef void *dxp_method;

/*
** list of operators, method manipulations
*/

// allocate a new method object
dxp_method dxp_method_new(dxp_type cls, dxp_prototype proto, dxp_string name);

// delete/free a method object
void dxp_method_del(dxp_method m);

// getters
dxp_type      dxp_method_get_class_type(dxp_method m);
dxp_prototype dxp_method_get_prototype(dxp_method m);
dxp_string    dxp_method_get_name(dxp_method m);

// compare 2 methods (like strcmp)
int dxp_method_cmp(dxp_method m1, dxp_method m2);


/*
** dexfile related primitives
*/

// add a method in the given dex file
// return the added item, or the existing one
dxp_method dxp_method_add(dexfile_t app, const char *cls, const char *prototype, const char *name);
dxp_method dxp_method_add2(dexfile_t app, dxp_type cls, dxp_prototype prototype,  dxp_string name);
dxp_method dxp_method_add3(dexfile_t app, dxp_method new_item);

// search the given method in the given dex file
// return NULL if not found
dxp_method dxp_method_find(dexfile_t app, dxp_method m);

// count of the method table
uint32_t dxp_method_count(dexfile_t app);

#endif/*!__DXP_METHOD_H__*/
