#include <dexpert/dxp_prototype.h>
#include <dexpert/dxp_string.h>
#include <stdlib.h>
#include <string.h>
#include "internal_structures/application.h"
#include "debug.h"


/*
** out internal representation of a prototype
*/
struct s_dxp_prototype
{
    // a short string representation of of the prototype
    dxp_string  shorty;

    // the return type of the method
    dxp_type    return_type;

    // the arguments types
    uint32_t    nb_arg;
    dxp_type   *args;
};


dxp_prototype dxp_proto_new(dxp_type return_type, uint32_t nb_args)
{
    struct s_dxp_prototype *result = NULL;

    result = (struct s_dxp_prototype *)malloc(sizeof (struct s_dxp_prototype));
    memset(result, 0, sizeof (struct s_dxp_prototype));

    result->return_type = return_type;
    result->nb_arg = nb_args;

    result->args = (dxp_type *)malloc(nb_args * sizeof (dxp_type));
    memset(result->args, 0, nb_args * sizeof (dxp_type));

    return ((dxp_prototype)result);
}

// append a new type in the argument list
dxp_prototype dxp_proto_set_arg(dxp_prototype p, uint32_t idx, dxp_type arg_type)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;

    CHECK_ARG(proto, NULL);
    CHECK_ARG(arg_type, NULL);

    if (idx >= proto->nb_arg)
    {
        DXP_DEBUG("[-] invalid prototype argument idx\n");
        return (NULL);
    }

    proto->args[idx] = arg_type;
    return (p);
}

// delete/free a prototype object
void dxp_proto_del(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;

    if (proto)
    {
        if (proto->args)
        {
            free(proto->args);
            proto->args = NULL;
        }
        free(proto);
        proto = NULL;
    }
}

// getters
dxp_type dxp_proto_get_ret_type(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, NULL);
    return (proto->return_type);
}
uint32_t dxp_proto_get_args_number(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, 0);
    return (proto->nb_arg);
}
dxp_type dxp_proto_get_arg(dxp_prototype p, uint32_t idx)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, NULL);
    return (proto->args[idx]);
}

// compare 2 types (like strcmp)
int dxp_proto_cmp(dxp_prototype p1, dxp_prototype p2)
{
    struct s_dxp_prototype *proto1 = (struct s_dxp_prototype *)p1,
                           *proto2 = (struct s_dxp_prototype *)p2;
    int                     ret    = 0;

    CHECK_ARG(proto1, 0);
    CHECK_ARG(proto2, 0);

    ret = dxp_type_cmp(proto1->return_type, proto2->return_type);
    if (ret != 0)
        return (ret);

    for (uint32_t i = 0; i < proto1->nb_arg; i++)
    {
        // if the proto1 has more argument than proto2, we considere proto1 greater
        if (i >= proto2->nb_arg)
            return (1);

        ret = dxp_type_cmp(proto1->args[i], proto2->args[i]);
        if (ret != 0)
            return (ret);
    }

    // maybe the both proto are identic (same arguments)
    if (proto1->nb_arg == proto2->nb_arg)
        return (0);

    // if we are here, proto1 has less argument than proto2, we consider proto2 greater
    return (-1);
}


/*
** dexfile related primitives
*/

// add a prototype in the given dex file
// return the added item, or the existing one
dxp_prototype dxp_proto_add(dexfile_t dex, dxp_prototype new_item)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_prototype         result;

    CHECK_ARG(app, NULL);

    result = dxp_rbtree_insert_unique(app->prototypes, new_item);

    if (result != new_item)
        dxp_proto_del(new_item);

    return (result);
}

// search the given prototype in the given dex file
// return NULL if not found
dxp_prototype dxp_proto_find(dexfile_t dex, dxp_prototype p)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(app, NULL);
    return (dxp_rbtree_find(app->prototypes, p));
}

// count of the prototype table
uint32_t dxp_proto_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(app, 0);
    return (dxp_rbtree_length(app->prototypes));
}
