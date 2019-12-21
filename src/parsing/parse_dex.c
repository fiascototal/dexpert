#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dexpert/debug.h>
#include "parsers.h"


int parse_dex(struct s_application *app, uint8_t *data, uint64_t data_size)
{
    int ret = 0;

    if (app == NULL || data == NULL)
    {
        DEBUG("[-] parse dex failed, invalid arguments\n");
        return (1);
    }

    if (app->tmp)
    {
        DEBUG("[-] the app is not clean, the tmp struct is still there\n");
        free(app->tmp);
        app->tmp = NULL;
    }

    app->tmp = (struct s_tmp_dexfile *)malloc(sizeof (struct s_tmp_dexfile));
    memset(app->tmp, 0, sizeof (struct s_tmp_dexfile));

    app->tmp->data = data;
    app->tmp->size = (data_size & 0xFFFFFFFF);

    if ((ret = parse_header(app)) != 0)
    {
        DEBUG("[-] parse dex header failed (%d)\n", ret);
        return (1);
    }

    if ((ret = parse_map(app)) != 0)
    {
        DEBUG("[-] parse dex map failed (%d)\n", ret);
        return (2);
    }

    if ((ret = parse_strings(app)) != 0)
    {
        DEBUG("[-] parse dex strings failed (%d)\n", ret);
        return (2);
    }

    if ((ret = parse_types(app)) != 0)
    {
        DEBUG("[-] parse dex types failed (%d)\n", ret);
        return (3);
    }

    if ((ret = parse_prototypes(app)) != 0)
    {
        DEBUG("[-] parse dex prototypes failed (%d)\n", ret);
        return (3);
    }

    // once we have finish the parsing, we can delete the temp dex
    free(app->tmp);
    app->tmp = NULL;

    return (0);
}
