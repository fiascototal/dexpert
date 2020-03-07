#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dexpert/dexfile.h>
#include <dexpert/file_utils.h>
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>
#include <dexpert/dxp_prototype.h>
#include <dexpert/dxp_field.h>
#include <dexpert/dxp_method.h>
#include <dexpert/dxp_class.h>
#include "internal_structures/application.h"
#include "parsing/parse_dex.h"
#include "utils/dxp_rbtree.h"
#include "utils/dxp_list.h"
#include "debug.h"


int dexfile_new(dexfile_t *dex)
{
    struct s_application *app = NULL;

    CHECK_ARG(dex, 1);

    // allocate a new application object
    app = (struct s_application *)malloc(sizeof (struct s_application));
    CHECK_ALLOCATION(app, 2);
    memset(app, 0, sizeof (struct s_application));

    // allocate a new strings map list
    app->strings = dxp_rbtree_new(dxp_str_cmp, dxp_str_del);

    // allocate a new types map list
    app->types = dxp_rbtree_new(dxp_type_cmp, dxp_type_del);

    // allocate a new prototype list
    app->prototypes = dxp_rbtree_new(dxp_proto_cmp, dxp_proto_del);

    // allocate a new field list
    app->fields = dxp_rbtree_new(dxp_field_cmp, dxp_field_del);

    // allocate a new method list
    app->methods = dxp_rbtree_new(dxp_method_cmp, dxp_method_del);

    // allocate a new class list
    app->classes = dxp_list_new(dxp_class_del);

    *dex = (dexfile_t)app;
    return (0);
}


void dexfile_close(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;

    if (dex == NULL)
        return;

    // delete the list of strings
    if (app->strings)
    {
        dxp_rbtree_delete(app->strings);
        app->strings = NULL;
    }

    // delete the list of types
    if (app->types)
    {
        dxp_rbtree_delete(app->types);
        app->types = NULL;
    }

    // delete the list of prototypes
    if (app->prototypes)
    {
        dxp_rbtree_delete(app->prototypes);
        app->prototypes = NULL;
    }

    // delete the list of fields
    if (app->fields)
    {
        dxp_rbtree_delete(app->fields);
        app->fields = NULL;
    }

    // delete the list of methods
    if (app->methods)
    {
        dxp_rbtree_delete(app->methods);
        app->methods = NULL;
    }

    // delete the list of classes
    if (app->classes)
    {
        dxp_list_delete(app->classes);
        app->classes = NULL;
    }

    free(app);
    app = NULL;
}


int dexfile_open_file(dexfile_t dex, const char *dex_path)
{
    uint8_t *dex_data      = NULL;
    uint64_t dex_data_size = 0;

    if (read_file(dex_path, &dex_data, &dex_data_size) != 0)
    {
        DXP_DEBUG("[-] read dex file failed %s\n", dex_path);
        return (2);
    }

    if (dexfile_open_data(dex, dex_data, dex_data_size) != 0)
    {
        DXP_DEBUG("[-] failed to parse the given dex\n");
        free(dex_data); dex_data = NULL;
        return (3);
    }

    free(dex_data); dex_data = NULL;
    return (0);
}


int dexfile_open_data(dexfile_t dex, uint8_t *dex_data, uint64_t dex_data_size)
{
    struct s_application *app = (struct s_application *)dex;
    return (parse_dex(app, dex_data, dex_data_size));
}
