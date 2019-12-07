#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dexpert/dexfile.h>
#include <dexpert/debug.h>
#include <dexpert/file_utils.h>
#include <dexpert/dxp_string.h>
#include "internal_structures/application.h"
#include "parsing/parsers.h"
#include "utils/dxp_rbtree.h"


int dexfile_new(dexfile_t *dex)
{
    struct s_application *app = NULL;

    if (dex == NULL)
    {
        DEBUG("[-] invalid arg\n");
        return (1);
    }

    // allocate a new application object
    app = (struct s_application *)malloc(sizeof (struct s_application));
    if (app == NULL)
    {
        DEBUG("[-] failed to allocate the dex object (%s)\n", ERR_MSG);
        return (2);
    }
    memset(app, 0, sizeof (struct s_application));

    // allocate a new strings map list
    app->strings = dxp_rbtree_new(dxp_str_cmp, dxp_str_del);

    *dex = (dexfile_t)app;
    return (0);
}


void dexfile_close(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;

    if (app == NULL)
        return;

    // delete all temporary items
    if (app->tmp.strings)
    {
        free(app->tmp.strings);
        app->tmp.strings = NULL;
    }

    // delete the list of strings
    if (app->strings)
    {
        dxp_rbtree_delete(app->strings);
        app->strings = NULL;
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
        DEBUG("[-] read dex file failed %s\n", dex_path);
        return (2);
    }

    if (dexfile_open_data(dex, dex_data, dex_data_size) != 0)
    {
        DEBUG("[-] failed to parse the given dex\n");
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

dxp_rbtree dexfile_get_strings(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    return (app->strings);
}
