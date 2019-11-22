#include <stdio.h>
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

    app->tmp.data = data;
    app->tmp.size = (data_size & 0xFFFFFFFF);

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

    return (0);
}
