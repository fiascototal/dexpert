#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"
#include "../utils/leb128.h"
#include <dexpert/dxp_string.h>


int parse_types(struct s_dex_cache *cache)
{
    uint32_t   cur_off      = 0,
               string_index = 0;
    uint8_t   *data         = NULL;
    dxp_type   new_item,
               inserted_item;

    CHECK_ARG(cache, 1);

    // iterate of the dex to read all types
    data = cache->data;
    cur_off = cache->hdr->typeIdsOff;
    for (uint32_t i = 0; i < cache->hdr->typeIdsSize; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        string_index = *(uint32_t *)(data + cur_off);
        cur_off += sizeof (uint32_t);

        CHECK_STRING_IDX(string_index, 3);

        // create a new type object
        new_item = dxp_type_new(cache->strings[string_index]);

        // update the type list of our dexfile
        inserted_item = dxp_type_add3(cache->app, new_item);

        // update the fast indexed list
        cache->types[i] = inserted_item;
    }

    return (0);
}
