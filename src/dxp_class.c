#include <stdlib.h>
#include <string.h>
#include <dexpert/dxp_class.h>
#include <dexpert/dxp_type.h>
#include <dexpert/dxp_string.h>
#include <dexpert/access_flags.h>
#include "debug.h"
#include "utils/dxp_list.h"
#include "internal_structures/application.h"


struct s_dxp_class
{
    dxp_type   cls_type;
    dxp_type   super_cls_type;
    dxp_string source_file;
    dxp_list   interfaces;
    uint32_t   flags;
};

// allocate a new class object
dxp_class dxp_class_new(dxp_type cls_type)
{
    struct s_dxp_class *result = NULL;

    CHECK_ARG(cls_type, NULL);
    result = (struct s_dxp_class *)malloc(sizeof (struct s_dxp_class));
    CHECK_ALLOCATION(result, NULL);
    memset(result, 0, sizeof (struct s_dxp_class));

    result->cls_type = cls_type;
    result->interfaces = dxp_list_new();

    // default access flags is PUBLIC
    result->flags = ACC_PUBLIC;

    return ((dxp_class)result);
}


// delete/free a field object
void dxp_class_del(dxp_class c)
{
    struct s_dxp_class *cls = NULL;

    if (c)
    {
        cls = (struct s_dxp_class *)c;
        dxp_list_delete(cls->interfaces);
        free(c);
        c = NULL;
    }
}

// get the class type name
dxp_type dxp_class_get_type(dxp_class c)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    return (cls->cls_type);
}

// get the class access flags
uint32_t dxp_class_get_flags(dxp_class c)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    return (cls->flags);
}

// set/update the class access flags
dxp_class dxp_class_set_flags(dxp_class c, uint32_t flags)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    if ((flags & ACC_CLASS_MASK) != flags)
    {
        DXP_DEBUG("[-] invalid class access flags\n");
        return (NULL);
    }
    cls->flags = flags;
    return (c);
}

// get the super class type name
dxp_type dxp_class_get_super_type(dxp_class c)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    return (cls->super_cls_type);
}

// set the super class type name
dxp_class dxp_class_set_super_type(dxp_class c, dxp_type t)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    CHECK_ARG(t, NULL);
    cls->super_cls_type = t;
    return (c);
}

// return the source filename string
dxp_string dxp_class_get_source(dxp_class c)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    return (cls->source_file);
}

// set the source filename string
dxp_class dxp_class_set_source(dxp_class c, dxp_string s)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    CHECK_ARG(s, NULL);
    cls->source_file = s;
    return (c);
}

// add an interface into the given class
dxp_class dxp_class_add_interface(dxp_class c, dxp_type interface)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    CHECK_ARG(interface, NULL);
    dxp_list_push(cls->interfaces, interface);
    return (c);
}

// return the number of interface that this class implement
uint32_t dxp_class_get_interface_count(dxp_class c)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, 0);
    return (dxp_list_length(cls->interfaces));
}

// return the interface at the given position
// if the index is negative, it starts from the end
dxp_type dxp_class_get_interface(dxp_class c, int idx)
{
    struct s_dxp_class *cls = (struct s_dxp_class *)c;
    CHECK_ARG(c, NULL);
    return (dxp_list_get(cls->interfaces, idx));
}


// add a class in the given dex file
// return the added item, or the existing one
dxp_class dxp_class_add(dexfile_t dex, dxp_class new_item)
{
    struct s_application *app = (struct s_application *)dex;

    CHECK_ARG(dex, NULL);
    CHECK_ARG(new_item, NULL);

    if (dxp_class_find(dex, new_item) != NULL)
    {
        DXP_DEBUG("[-] this class already exists\n");
        return (NULL);
    }

    dxp_list_push(app->classes, new_item);
    return (new_item);
}

// search the given class in the given dex file
// return NULL if not found
dxp_class dxp_class_find(dexfile_t dex, dxp_class p)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_list_iterator     it;
    dxp_class             cur_cls;

    CHECK_ARG(dex, NULL);
    CHECK_ARG(p, NULL);

    for (it = dxp_list_begin(app->classes); dxp_list_end(it) != 1; dxp_list_next(it))
    {
        cur_cls = (dxp_class)dxp_list_data(it);
        if (dxp_type_cmp(dxp_class_get_type(p), dxp_class_get_type(cur_cls)) == 0)
        {
            dxp_list_destroy_iterator(it);
            return (cur_cls);
        }
    }

    return (NULL);
}

// count of the prototype table
uint32_t dxp_class_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(dex, 0);
    return (dxp_list_length(app->classes));
}
