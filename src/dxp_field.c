#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dexpert/dxp_field.h>
#include "debug.h"
#include "internal_structures/application.h"


struct s_dxp_field
{
    dxp_string name;
    dxp_type   cls_typ;
    dxp_type   typ;
};


// allocate a new field object
dxp_field dxp_field_new(dxp_type cls, dxp_type typ, dxp_string name)
{
    struct s_dxp_field *result = NULL;

    CHECK_ARG(cls, NULL);
    CHECK_ARG(typ, NULL);
    CHECK_ARG(name, NULL);

    result = (struct s_dxp_field *)malloc(sizeof (struct s_dxp_field));
    CHECK_ALLOCATION(result, NULL);
    memset(result, 0, sizeof (struct s_dxp_field));

    result->name = name;
    result->cls_typ = cls;
    result->typ = typ;

    return ((dxp_field)result);
}


// delete/free a field object
void dxp_field_del(dxp_field f)
{
    if (f)
    {
        free(f);
        f = NULL;
    }
}


// getters

dxp_type dxp_field_get_class_type(dxp_field f)
{
    struct s_dxp_field *fld = (struct s_dxp_field *)f;
    CHECK_ARG(f, NULL);
    return (fld->cls_typ);
}

dxp_type dxp_field_get_type(dxp_field f)
{
    struct s_dxp_field *fld = (struct s_dxp_field *)f;
    CHECK_ARG(f, NULL);
    return (fld->typ);
}

dxp_string dxp_field_get_name(dxp_field f)
{
    struct s_dxp_field *fld = (struct s_dxp_field *)f;
    CHECK_ARG(f, NULL);
    return (fld->name);
}

// compare 2 fields (like strcmp)
/*
This list must be sorted, where the defining type (by type_id index) is the 
major order, field name (by string_id index) is the intermediate order, and 
type (by type_id index) is the minor order. The list must not contain any 
duplicate entries. 
*/
int dxp_field_cmp(dxp_field f1, dxp_field f2)
{
    struct s_dxp_field *fld1 = (struct s_dxp_field *)f1;
    struct s_dxp_field *fld2 = (struct s_dxp_field *)f2;
    int                 ret  = 0;
    
    CHECK_ARG(f1, 0);
    CHECK_ARG(f2, 0);

    ret = dxp_type_cmp(fld1->cls_typ, fld2->cls_typ);
    if (ret != 0)
        return (ret);
    ret = dxp_str_cmp(fld1->name, fld2->name);
    if (ret != 0)
        return (ret);
    return (dxp_type_cmp(fld1->typ, fld2->typ));
}


/*
** dexfile related primitives
*/

// add a field in the given dex file
// return the added item, or the existing one
dxp_field dxp_field_add(dexfile_t app, const char *cls, const char *typ, const char *name)
{
    dxp_string name2;
    dxp_type   typ2, cls2;
    dxp_field  new_item;

    CHECK_ARG(app, NULL);

    name2 = dxp_str_add(app, name);
    typ2 = dxp_type_add(app, typ);
    cls2 = dxp_type_add(app, cls);

    new_item = dxp_field_new(cls2, typ2, name2);
    return (dxp_field_add2(app, new_item));
}

dxp_field dxp_field_add2(dexfile_t dex, dxp_field new_item)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_field             result;

    CHECK_ARG(app, NULL);
    CHECK_ARG(new_item, NULL);

    result = dxp_rbtree_insert_unique(app->fields, new_item);

    if (result != new_item)
        dxp_field_del(new_item);

    return (result);
}

// search the given field in the given dex file
// return NULL if not found
dxp_field dxp_field_find(dexfile_t dex, dxp_field f)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(app, NULL);
    CHECK_ARG(f, NULL);
    return (dxp_rbtree_find(app->fields, f));
}

// count of the prototype table
uint32_t dxp_field_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(app, 0);
    return (dxp_rbtree_length(app->fields));
}
