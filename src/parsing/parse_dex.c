#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"


static void _allocate_tmp(struct s_tmp_dexfile *tmp)
{
    uint32_t count = 0;

    count = tmp->hdr->stringIdsSize;
    tmp->strings = (dxp_string *)malloc(sizeof (dxp_string) * count);
    memset(tmp->strings, 0, sizeof (dxp_string) * count);

    count = tmp->hdr->typeIdsSize;
    tmp->types = (dxp_type *)malloc(sizeof (dxp_type) * count);
    memset(tmp->types, 0, sizeof (dxp_type) * count);

    count = tmp->hdr->protoIdsSize;
    tmp->prototypes = (dxp_prototype *)malloc(sizeof (dxp_prototype) * count);
    memset(tmp->prototypes, 0, sizeof (dxp_prototype) * count);

    count = tmp->hdr->fieldIdsSize;
    tmp->fields = (dxp_field *)malloc(sizeof (dxp_field) * count);
    memset(tmp->fields, 0, sizeof (dxp_field) * count);
}


static void _free_tmp(struct s_tmp_dexfile *tmp)
{
    if (tmp->strings)
    {
        free(tmp->strings);
        tmp->strings = NULL;
    }

    if (tmp->types)
    {
        free(tmp->types);
        tmp->types = NULL;
    }

    if (tmp->prototypes)
    {
        free(tmp->prototypes);
        tmp->prototypes = NULL;
    }

    if (tmp->fields)
    {
        free(tmp->fields);
        tmp->fields = NULL;
    }

    free(tmp);
    tmp= NULL;
}


int parse_dex(struct s_application *app, uint8_t *data, uint64_t data_size)
{
    int ret = 0;

    CHECK_ARG(app, 1);
    CHECK_ARG(data, 1);

    if (app->tmp)
    {
        DXP_DEBUG("[-] the app is not clean, the tmp struct is still there\n");
        _free_tmp(app->tmp);
        app->tmp = NULL;
    }

    app->tmp = (struct s_tmp_dexfile *)malloc(sizeof (struct s_tmp_dexfile));
    memset(app->tmp, 0, sizeof (struct s_tmp_dexfile));

    app->tmp->data = data;
    app->tmp->size = (data_size & 0xFFFFFFFF);

    if ((ret = parse_header(app)) != 0)
    {
        DXP_DEBUG("[-] parse dex header failed (%d)\n", ret);
        return (1);
    }

    _allocate_tmp(app->tmp);

    if ((ret = parse_map(app)) != 0)
    {
        DXP_DEBUG("[-] parse dex map failed (%d)\n", ret);
        return (2);
    }

    if ((ret = parse_strings(app)) != 0)
    {
        DXP_DEBUG("[-] parse dex strings failed (%d)\n", ret);
        return (3);
    }

    if ((ret = parse_types(app)) != 0)
    {
        DXP_DEBUG("[-] parse dex types failed (%d)\n", ret);
        return (4);
    }

    if ((ret = parse_prototypes(app)) != 0)
    {
        DXP_DEBUG("[-] parse dex prototypes failed (%d)\n", ret);
        return (5);
    }

    if ((ret = parse_fields(app)) != 0)
    {
        DXP_DEBUG("[-] parse dex fields failed (%d)\n", ret);
        return (6);
    }

    // once we have finish the parsing, we can delete the temp dex
    _free_tmp(app->tmp);
    app->tmp = NULL;

    return (0);
}
