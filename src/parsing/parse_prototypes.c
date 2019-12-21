#include <string.h>
#include <stdlib.h>
#include <dexpert/debug.h>
#include <dexpert/dxp_string.h>
#include <utils/leb128.h>
#include "parsers.h"
#include "../dex_objects/dex_prototype.h"


int parse_prototypes(struct s_application *app)
{
    uint32_t       cur_off        = 0,
                   parameters_off = 0,
                   nb_parameters  = 0;
    uint8_t       *data           = NULL;
    proto_id_item *cur_item       = NULL;
    dxp_type       ret_type,
                   cur_arg;
    dxp_string     shorty_name;
    dxp_prototype  new_item,
                   inserted_item;

    if (app == NULL)
    {
        DEBUG("[-] invalid arguments\n");
        return (1);
    }

    // iterate of the dex to read all prototypes
    data = app->tmp->data;
    cur_off = app->tmp->hdr->protoIdsOff;
    for (uint32_t i = 0; i < app->tmp->hdr->protoIdsSize; i++)
    {
        cur_item = (proto_id_item *)(data + cur_off);
        cur_off += sizeof (proto_id_item);

        // get the corresponding object (based on indexes)
        ret_type = app->tmp->types[cur_item->return_type_idx];
        shorty_name = app->tmp->strings[cur_item->shorty_idx];
        parameters_off = cur_item->parameters_off;
        nb_parameters = 0;
        if (parameters_off != 0)
        {
            nb_parameters = *(uint32_t *)(app->tmp->data + parameters_off);
            parameters_off += sizeof (uint32_t);
        }

        // create a new type object
        new_item = dxp_proto_new(ret_type, nb_parameters);

        for (uint32_t j = 0; j < nb_parameters; j++)
        {
            cur_arg = app->tmp->types[*(uint32_t *)(app->tmp->data + parameters_off)];
            dxp_proto_set_arg(new_item, j, cur_arg);
            parameters_off += sizeof (uint32_t);
        }

        // update the prototype list of our dexfile
        inserted_item = dxp_proto_add(app, new_item);

        // update the fast indexed list
        app->tmp->prorotypes[i] = inserted_item;
    }

    return (0);
}
