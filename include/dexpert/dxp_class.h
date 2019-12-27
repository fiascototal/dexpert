#ifndef __DXP_CLASS_H__
# define __DXP_CLASS_H__

# include <dexpert/dxp_type.h>
# include <dexpert/dxp_string.h>
# include <stdint.h>

typedef void *dxp_class;

/*
** list of operators, field manipulations
*/

// allocate a new class object
dxp_class dxp_class_new(dxp_type cls_type);

// delete/free a field object
void dxp_class_del(dxp_class c);

// get the class type name
dxp_type dxp_class_get_type(dxp_class c);

// get the class access flags
uint32_t dxp_class_get_flags(dxp_class c);

// set/update the class access flags
dxp_class dxp_class_set_flags(dxp_class c, uint32_t flags);

// get the super class type name
dxp_type dxp_class_get_super_type(dxp_class c);

// set the super class type name
dxp_class dxp_class_set_super_type(dxp_class c, dxp_type t);

// return the source filename string
dxp_string dxp_class_get_source(dxp_class c);

// set the source filename string
dxp_class dxp_class_set_source(dxp_class c, dxp_string s);

// add an interface into the given class
dxp_class dxp_class_add_interface(dxp_class c, dxp_type interface);

// return the number of interface that this class implement
uint32_t dxp_class_get_interface_count(dxp_class c);

// return the interface at the given position
// if the index is negative, it starts from the end
dxp_type dxp_class_get_interface(dxp_class c, int idx);

#endif/*!__DXP_CLASS_H__*/
