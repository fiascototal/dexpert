#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"
#include "../dex_objects/dex_prototype.h"
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>


int parse_prototypes(struct s_dex_cache *cache)
{
    uint32_t       cur_off        = 0,
                   parameters_off = 0,
                   nb_parameters  = 0,
                   cur_arg_index  = 0;
    uint8_t       *data           = NULL;
    proto_id_item *cur_item       = NULL;
    dxp_type       ret_type,
                   cur_arg;
    dxp_prototype  new_item,
                   inserted_item;

    CHECK_ARG(cache, 1);

    // iterate of the dex to read all prototypes
    data = cache->data;
    cur_off = cache->hdr->protoIdsOff;
    for (uint32_t i = 0; i < cache->hdr->protoIdsSize; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        cur_item = (proto_id_item *)(data + cur_off);
        cur_off += sizeof (proto_id_item);

        CHECK_TYPE_IDX(cur_item->return_type_idx, 3);
        CHECK_STRING_IDX(cur_item->shorty_idx, 4);

        // get the corresponding object (based on indexes)
        ret_type = cache->types[cur_item->return_type_idx];
        parameters_off = cur_item->parameters_off;

        CHECK_OFFSET(parameters_off, 2);

        // create a new prototype object
        new_item = dxp_proto_new(ret_type);

        nb_parameters = 0;
        if (parameters_off != 0)
        {
            nb_parameters = *(uint32_t *)(cache->data + parameters_off);
            parameters_off += sizeof (uint32_t);
        }

        // create arguments for this prototype (read the list in the data section)
        for (uint32_t j = 0; j < nb_parameters; j++)
        {
            cur_arg_index = *(uint32_t *)(cache->data + parameters_off);
            CHECK_TYPE_IDX(cur_arg_index, 3);

            cur_arg = cache->types[cur_arg_index];
            dxp_proto_add_arg(new_item, cur_arg);
            parameters_off += sizeof (uint32_t);
        }

        // update the prototype list of our dexfile
        inserted_item = dxp_proto_add2(cache->app, new_item);

        // update the fast indexed list
        cache->prototypes[i] = inserted_item;
    }

    return (0);
}
