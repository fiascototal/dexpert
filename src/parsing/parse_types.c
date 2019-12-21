#include <string.h>
#include <stdlib.h>
#include <dexpert/debug.h>
#include <dexpert/dxp_string.h>
#include <utils/leb128.h>
#include "parsers.h"


int parse_types(struct s_application *app)
{
    uint32_t   cur_off      = 0,
               string_index = 0;
    uint8_t   *data         = NULL;
    dxp_type   new_item,
               inserted_item;

    if (app == NULL)
    {
        DEBUG("[-] invalid arguments\n");
        return (1);
    }

    // iterate of the dex to read all types
    data = app->tmp->data;
    cur_off = app->tmp->hdr->typeIdsOff;
    for (uint32_t i = 0; i < app->tmp->hdr->typeIdsSize; i++)
    {
        string_index = *(uint32_t *)(data + cur_off);
        cur_off += sizeof (uint32_t);

        // create a new type object
        new_item = dxp_type_new(app->tmp->strings[string_index]);

        // update the type list of our dexfile
        inserted_item = dxp_type_add3(app, new_item);

        // update the fast indexed list
        app->tmp->types[i] = inserted_item;
    }

    return (0);
}
