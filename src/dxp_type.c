#include <stdlib.h>
#include <string.h>
#include <dexpert/dxp_type.h>
#include "internal_structures/application.h"


/*
** out internal representation of a type
*/
struct s_dxp_type
{
    dxp_string s;
};


// allocate a new DXP_TYPE object
dxp_type dxp_type_new(dxp_string s)
{
    struct s_dxp_type *result = NULL;

    result = (struct s_dxp_type *)malloc(sizeof (struct s_dxp_type));
    memset(result, 0, sizeof (struct s_dxp_type));
    result->s = s;

    return ((dxp_type)result);
}

// delete an allocated type object
void dxp_type_del(dxp_type t)
{
    struct s_dxp_type *typ = (struct s_dxp_type *)t;
    if (typ)
    {
        free(typ);
        typ = NULL;
    }
}

// return the string behind the type
dxp_string dxp_type_data(dxp_type t)
{
    struct s_dxp_type *typ = (struct s_dxp_type *)t;
    return (typ->s);
}

// compare 2 types (like strcmp)
int dxp_type_cmp(dxp_type t1, dxp_type t2)
{
    struct s_dxp_type *typ1 = (struct s_dxp_type *)t1,
                      *typ2 = (struct s_dxp_type *)t2;
    return (dxp_str_cmp(typ1->s, typ2->s));
}


/*
** dexfile related primitives
*/

// add a type in the given dex file
// return the added type, or the existing one
dxp_type dxp_type_add(dexfile_t dex, const char *s)
{
    dxp_string new_item = dxp_str_new((uint8_t *)s, strlen(s), strlen(s));
    return (dxp_type_add2(dex, new_item));
}

dxp_type dxp_type_add2(dexfile_t dex, dxp_string s)
{
    dxp_type t;

    s = dxp_str_add2(dex, s);
    t = dxp_type_new(s);
    return (dxp_type_add3(dex, t));
}

dxp_type dxp_type_add3(dexfile_t dex, dxp_type new_item)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_type              result;

    result = dxp_rbtree_insert_unique(app->types, new_item);

    if (result != new_item)
        dxp_type_del(new_item);

    return (result);
}

// search the given type in the given dex file
// return NULL if not found
dxp_type dxp_type_find(dexfile_t app, const char *t)
{
    dxp_string tmp_s = dxp_str_new((uint8_t *)t, strlen(t), strlen(t));
    dxp_string dex_s   = dxp_str_find2(app, tmp_s);
    dxp_type tmp_t, result;

    dxp_str_del(tmp_s);

    if (dex_s == NULL)
        return (NULL);

    tmp_t = dxp_type_new(dex_s);
    result = dxp_type_find2(app, tmp_t);
    dxp_type_del(tmp_t);

    return (result);
}

dxp_type dxp_type_find2(dexfile_t dex, dxp_type t)
{
    struct s_application *app = (struct s_application *)dex;
    return (dxp_rbtree_find(app->types, t));
}

// list iterator
dxp_type_iterator dxp_type_begin(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    return (dxp_rbtree_begin(app->types));
}

int dxp_type_next(dxp_type_iterator it)
{
    return (dxp_rbtree_next(it));
}

int dxp_type_end(dxp_type_iterator it)
{
    return (dxp_rbtree_end(it));
}

dxp_type dxp_type_current(dxp_type_iterator it)
{
    return (dxp_rbtree_data(it));
}

void dxp_type_destroy_iterator(dxp_type_iterator it)
{
    free(it);
    it = NULL;
}

// count of the string table
uint32_t dxp_type_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    return (dxp_rbtree_length(app->types));
}
