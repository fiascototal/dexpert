#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"
#include "../dex_objects/dex_prototype.h"
#include "../utils/leb128.h"
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>


int parse_prototypes(struct s_application *app)
{
    uint32_t       cur_off        = 0,
                   parameters_off = 0,
                   nb_parameters  = 0,
                   cur_arg_index  = 0;
    uint8_t       *data           = NULL;
    proto_id_item *cur_item       = NULL;
    dxp_type       ret_type,
                   cur_arg;
    dxp_string     shorty_name;
    dxp_prototype  new_item,
                   inserted_item;

    CHECK_ARG(app, 1);

    // iterate of the dex to read all prototypes
    data = app->tmp->data;
    cur_off = app->tmp->hdr->protoIdsOff;
    for (uint32_t i = 0; i < app->tmp->hdr->protoIdsSize; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        cur_item = (proto_id_item *)(data + cur_off);
        cur_off += sizeof (proto_id_item);

        CHECK_TYPE_IDX(cur_item->return_type_idx, 3);
        CHECK_STRING_IDX(cur_item->shorty_idx, 4);

        // get the corresponding object (based on indexes)
        ret_type = app->tmp->types[cur_item->return_type_idx];
        shorty_name = app->tmp->strings[cur_item->shorty_idx];
        shorty_name = shorty_name; /* unused */
        parameters_off = cur_item->parameters_off;

        CHECK_OFFSET(parameters_off, 2);

        nb_parameters = 0;
        if (parameters_off != 0)
        {
            nb_parameters = *(uint32_t *)(app->tmp->data + parameters_off);
            parameters_off += sizeof (uint32_t);
        }

        // create a new type object
        new_item = dxp_proto_new(ret_type, nb_parameters);

        // create arguments for this prototype (read the list in the data section)
        for (uint32_t j = 0; j < nb_parameters; j++)
        {
            cur_arg_index = *(uint32_t *)(app->tmp->data + parameters_off);
            CHECK_TYPE_IDX(cur_arg_index, 3);

            cur_arg = app->tmp->types[cur_arg_index];
            dxp_proto_set_arg(new_item, j, cur_arg);
            parameters_off += sizeof (uint32_t);
        }

        // update the prototype list of our dexfile
        inserted_item = dxp_proto_add(app, new_item);

        // update the fast indexed list
        app->tmp->prototypes[i] = inserted_item;
    }

    return (0);
}
