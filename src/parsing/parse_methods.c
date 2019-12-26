#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"
#include "../dex_objects/dex_method.h"
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>
#include <dexpert/dxp_prototype.h>


// parse the methods table
int parse_methods(struct s_application *app)
{
    uint8_t        *data     = NULL;
    uint32_t        cur_off  = 0;
    method_id_item *cur_item = NULL;
    dxp_type        cur_cls;
    dxp_string      cur_name;
    dxp_prototype   cur_proto;
    dxp_method      new_item,
                    inserted_item;

    CHECK_ARG(app, 1);

    // iterate of the dex to read all prototypes
    data = app->tmp->data;
    cur_off = app->tmp->hdr->methodIdsOff;
    for (uint32_t i = 0; i < app->tmp->hdr->methodIdsSize; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        cur_item = (method_id_item *)(data + cur_off);
        cur_off += sizeof (method_id_item);

        CHECK_TYPE_IDX(cur_item->class_idx, 3);
        CHECK_STRING_IDX(cur_item->name_idx, 4);
        CHECK_PROTOTYPE_IDX(cur_item->proto_idx, 5);

        cur_cls = app->tmp->types[cur_item->class_idx];
        cur_name = app->tmp->strings[cur_item->name_idx];
        cur_proto = app->tmp->prototypes[cur_item->proto_idx];

        // create a new method object
        new_item = dxp_method_new(cur_cls, cur_proto, cur_name);

        // update the method list of our dexfile
        inserted_item = dxp_method_add3(app, new_item);

        // update the fast indexed list
        app->tmp->methods[i] = inserted_item;
    }

    return (0);
}
