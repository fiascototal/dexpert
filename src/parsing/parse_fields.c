#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"
#include "../dex_objects/dex_field.h"
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>


// parse the fields table
int parse_fields(struct s_application *app)
{
    uint8_t       *data     = NULL;
    uint32_t       cur_off  = 0;
    field_id_item *cur_item = NULL;
    dxp_type       cur_cls, cur_typ;
    dxp_string     cur_name;
    dxp_field      new_item,
                   inserted_item;

    CHECK_ARG(app, 1);

    // iterate of the dex to read all prototypes
    data = app->tmp->data;
    cur_off = app->tmp->hdr->fieldIdsOff;
    for (uint32_t i = 0; i < app->tmp->hdr->fieldIdsSize; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        cur_item = (field_id_item *)(data + cur_off);
        cur_off += sizeof (field_id_item);

        CHECK_TYPE_IDX(cur_item->class_idx, 3);
        CHECK_TYPE_IDX(cur_item->type_idx, 3);
        CHECK_STRING_IDX(cur_item->name_idx, 4);

        cur_cls = app->tmp->types[cur_item->class_idx];
        cur_typ = app->tmp->types[cur_item->type_idx];
        cur_name = app->tmp->strings[cur_item->name_idx];

        // create a new field object
        new_item = dxp_field_new(cur_cls, cur_typ, cur_name);

        // update the prototype list of our dexfile
        inserted_item = dxp_field_add2(app, new_item);

        // update the fast indexed list
        app->tmp->fields[i] = inserted_item;
    }

    return (0);
}
