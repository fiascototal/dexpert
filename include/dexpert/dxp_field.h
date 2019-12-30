#ifndef __DXP_FIELD_H__
# define __DXP_FIELD_H__

# include <dexpert/dexfile.h>
# include <dexpert/dxp_type.h>
# include <dexpert/dxp_string.h>


typedef void *dxp_field;

/*
** list of operators, field manipulations
*/

// allocate a new field object
dxp_field dxp_field_new(dxp_type cls, dxp_type typ, dxp_string name);

// delete/free a field object
void dxp_field_del(dxp_field f);

// getters
dxp_type   dxp_field_get_class_type(dxp_field f);
dxp_type   dxp_field_get_type(dxp_field f);
dxp_string dxp_field_get_name(dxp_field f);

// compare 2 fields (like strcmp)
int dxp_field_cmp(dxp_field f1, dxp_field f2);


/*
** dexfile related primitives
*/

// add a field in the given dex file
// return the added item, or the existing one
dxp_field dxp_field_add(dexfile_t app, const char *cls, const char *typ, const char *name);
dxp_field dxp_field_add2(dexfile_t app, dxp_field new_item);

// search the given field in the given dex file
// return NULL if not found
dxp_field dxp_field_find(dexfile_t app, dxp_field p);

// count of the prototype table
uint32_t dxp_field_count(dexfile_t app);

#endif/*!__DXP_FIELD_H__*/
