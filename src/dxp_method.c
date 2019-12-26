#include <stdlib.h>
#include <string.h>
#include <dexpert/dxp_method.h>
#include "internal_structures/application.h"
#include "debug.h"


struct s_dxp_method
{
    dxp_type        cls_type;
    dxp_prototype   prototype;
    dxp_string      name;
};


// allocate a new method object
dxp_method dxp_method_new(dxp_type cls, dxp_prototype proto, dxp_string name)
{
    struct s_dxp_method *result = NULL;

    CHECK_ARG(cls, NULL);
    CHECK_ARG(proto, NULL);
    CHECK_ARG(name, NULL);

    result = (struct s_dxp_method *)malloc(sizeof (struct s_dxp_method));
    memset(result, 0, sizeof (struct s_dxp_method));
    result->cls_type = cls;
    result->name = name;
    result->prototype = proto;

    return ((dxp_method)result);
}


// delete/free a method object
void dxp_method_del(dxp_method m)
{
    if (m)
    {
        free(m);
        m = NULL;
    }
}


// getters

dxp_type dxp_method_get_class_type(dxp_method m)
{
    struct s_dxp_method *mm = (struct s_dxp_method *)m;
    CHECK_ARG(m, NULL);
    return (mm->cls_type);
}

dxp_prototype dxp_method_get_prototype(dxp_method m)
{
    struct s_dxp_method *mm = (struct s_dxp_method *)m;
    CHECK_ARG(m, NULL);
    return (mm->prototype);
}

dxp_string dxp_method_get_name(dxp_method m)
{
    struct s_dxp_method *mm = (struct s_dxp_method *)m;
    CHECK_ARG(m, NULL);
    return (mm->name);
}

// compare 2 methods (like strcmp)
int dxp_method_cmp(dxp_method m1, dxp_method m2)
{
    int ret = 0;

    ret = dxp_type_cmp(dxp_method_get_class_type(m1), dxp_method_get_class_type(m2));
    if (ret != 0)
        return (ret);
    
    ret = dxp_str_cmp(dxp_method_get_name(m1), dxp_method_get_name(m2));
    if (ret != 0)
        return (ret);

    return (dxp_proto_cmp(dxp_method_get_prototype(m1), dxp_method_get_prototype(m2)));
}


/*
** dexfile related primitives
*/

// add a method in the given dex file
// return the added item, or the existing one
dxp_method dxp_method_add(dexfile_t app, const char *cls, const char *prototype, const char *name)
{
    dxp_type cls2;
    dxp_prototype proto2;
    dxp_string name2;

    cls2 = dxp_type_add(app, cls);
    proto2 = dxp_proto_add(app, prototype);
    name2 = dxp_str_add(app, name);

    return (dxp_method_add2(app, cls2, proto2, name2));
}

dxp_method dxp_method_add2(dexfile_t app, dxp_type cls, dxp_prototype prototype,  dxp_string name)
{
    return (dxp_method_add3(app, dxp_method_new(cls, prototype, name)));
}

dxp_method dxp_method_add3(dexfile_t dex, dxp_method new_item)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_method            result;

    CHECK_ARG(app, NULL);
    CHECK_ARG(new_item, NULL);

    result = dxp_rbtree_insert_unique(app->methods, new_item);

    if (result != new_item)
        dxp_proto_del(new_item);

    return (result);
}

// search the given method in the given dex file
// return NULL if not found
dxp_method dxp_method_find(dexfile_t dex, dxp_method m)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(dex, NULL);
    CHECK_ARG(m, NULL);
    return (dxp_rbtree_find(app->methods, m));
}

// count of the method table
uint32_t dxp_method_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(dex, 0);
    return (dxp_rbtree_length(app->methods));
}
