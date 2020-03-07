#include <dexpert/dxp_prototype.h>
#include <dexpert/dxp_string.h>
#include <stdlib.h>
#include <string.h>
#include "utils/dxp_list.h"
#include "internal_structures/application.h"
#include "debug.h"


/*
** out internal representation of a prototype
*/
struct s_dxp_prototype
{
    // a short string representation of of the prototype
    dxp_string shorty;

    // the return type of the method
    dxp_type   return_type;

    // the arguments
    dxp_list   args;
};


dxp_prototype dxp_proto_new(dxp_type return_type)
{
    struct s_dxp_prototype *result = NULL;

    result = (struct s_dxp_prototype *)malloc(sizeof (struct s_dxp_prototype));
    memset(result, 0, sizeof (struct s_dxp_prototype));

    result->args = dxp_list_new(LIST_NO_DEL);
    result->return_type = return_type;

    return ((dxp_prototype)result);
}

// append a new type in the argument list
dxp_prototype dxp_proto_add_arg(dxp_prototype p, dxp_type arg_type)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;

    CHECK_ARG(proto, NULL);
    CHECK_ARG(arg_type, NULL);

    dxp_list_push(proto->args, arg_type);

    return (p);
}

// delete/free a prototype object
void dxp_proto_del(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;

    if (proto)
    {
        dxp_list_delete(proto->args);
        free(proto);
        proto = NULL;
    }
}


// return the "return type" of the given prototype
dxp_type dxp_proto_get_ret_type(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, NULL);
    return (proto->return_type);
}

// return the number of argument of the given prototype
uint32_t dxp_proto_get_args_count(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, 0);
    return (dxp_list_length(proto->args));
}

// return the argument at the given index
// if the index is negative, it starts from the last argument
dxp_type dxp_proto_get_arg(dxp_prototype p, int idx)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, NULL);
    return (dxp_list_get(proto->args, idx));
}

// return the shorty name of the prototype
dxp_string dxp_proto_get_shorty(dxp_prototype p)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, NULL);
    return (proto->shorty);
}

// set the shorty name of the given prototype
dxp_prototype dxp_proto_set_shorty(dxp_prototype p, dxp_string s)
{
    struct s_dxp_prototype *proto = (struct s_dxp_prototype *)p;
    CHECK_ARG(proto, NULL);
    CHECK_ARG(s, NULL);
    proto->shorty = s;
    return (p);
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

    for (uint32_t i = 0; i < dxp_list_length(proto1->args); i++)
    {
        // if the proto1 has more argument than proto2, we considere proto1 greater
        if (i >= dxp_list_length(proto2->args))
            return (1);

        ret = dxp_type_cmp(dxp_list_get(proto1->args, i), dxp_list_get(proto2->args, i));
        if (ret != 0)
            return (ret);
    }

    // maybe the both proto are identic (same arguments)
    if (dxp_list_length(proto1->args) == dxp_list_length(proto2->args))
        return (0);

    // if we are here, proto1 has less argument than proto2, we consider proto2 greater
    return (-1);
}


/*
** dexfile related primitives
*/

// add a prototype in the given dex file
// return the added item, or the existing one

dxp_prototype dxp_proto_add(dexfile_t dex, const char *s)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_prototype         result;
    dxp_type              cur_type;
    char    *pattern_found = NULL,
            *tmp           = NULL,
            *arg           = NULL;

    CHECK_ARG(app, NULL);

    //
    // 1) search the return type
    //

    pattern_found = strstr(s, ":");
    if (pattern_found == NULL)
    {
        DXP_DEBUG("[-] invalid prototype str format, no return type\n");
        return (NULL);
    }

    tmp = (char *)malloc((unsigned int)(pattern_found - s) + 1);
    memcpy(tmp, s, (unsigned int)(pattern_found - s));
    tmp[(unsigned int)(pattern_found - s)] = 0;
    cur_type = dxp_type_add(app, tmp);
    free(tmp); tmp = NULL;

    // skip the ':'
    pattern_found += 1;

    result = dxp_proto_new(cur_type);

    if (strlen(pattern_found) > 0)
    {
        // loop of args
        arg = pattern_found;
        while ((pattern_found = strstr(arg, ",")) != NULL)
        {
            // extract the arg type
            tmp = (char *)malloc((uint32_t)(pattern_found - arg));
            memcpy(tmp, arg, (uint32_t)(pattern_found - arg));
            tmp[(uint32_t)(pattern_found - arg)] = 0;
            cur_type = dxp_type_add(app, tmp);
            free(tmp); tmp = NULL;

            // add the argument in the prototype
            dxp_proto_add_arg(result, cur_type);

            // skip the ','
            arg = pattern_found + 1;
        }

        // manage the last type
        cur_type = dxp_type_add(app, arg);
        dxp_proto_add_arg(result, cur_type);
    }

    return (dxp_proto_add2(dex, result));
}


dxp_prototype dxp_proto_add2(dexfile_t dex, dxp_prototype new_item)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_prototype         result;

    CHECK_ARG(app, NULL);
    CHECK_ARG(new_item, NULL);

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
    CHECK_ARG(p, NULL);
    return (dxp_rbtree_find(app->prototypes, p));
}

// count of the prototype table
uint32_t dxp_proto_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    CHECK_ARG(app, 0);
    return (dxp_rbtree_length(app->prototypes));
}
