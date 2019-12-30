#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include "../debug.h"
#include "../dex_objects/dex_class.h"
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>


// parse the classes table
int parse_classes(struct s_application *app)
{
    uint8_t        *data          = NULL;
    uint32_t        cur_off       = 0,
                    interface_off = 0,
                    nb_interfaces = 0,
                    cur_type_idx  = 0;
    class_def_item *cur_item      = NULL;
    dxp_type        cur_type;
    dxp_string      cur_name;
    dxp_class       new_item,
                    inserted_item;

    CHECK_ARG(app, 1);

    // iterate of the dex to read all prototypes
    data = app->tmp->data;
    cur_off = app->tmp->hdr->classDefsOff;
    for (uint32_t i = 0; i < app->tmp->hdr->classDefsSize; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        cur_item = (class_def_item *)(data + cur_off);
        cur_off += sizeof (class_def_item);

        CHECK_TYPE_IDX(cur_item->class_idx, 3);

        if (cur_item->superclass_idx != 0xFFFFFFFF)
            CHECK_TYPE_IDX(cur_item->superclass_idx, 3);

        if (cur_item->source_file_idx != 0xFFFFFFFF)
            CHECK_STRING_IDX(cur_item->source_file_idx, 4);
            
        cur_type = app->tmp->types[cur_item->class_idx];

        // create a new class object
        new_item = dxp_class_new(cur_type);

        // set the super class
        if (cur_item->superclass_idx != 0xFFFFFFFF)
        {
            cur_type = app->tmp->types[cur_item->class_idx];
            dxp_class_set_super_type(new_item, cur_type);
        }

        // set the source filename
        if (cur_item->source_file_idx != 0xFFFFFFFF)
        {
            cur_name = app->tmp->strings[cur_item->source_file_idx];
            dxp_class_set_source(new_item, cur_name);
        }

        // set the interfaces
        if (cur_item->interfaces_off != 0)
        {
            interface_off = cur_item->interfaces_off;
            CHECK_OFFSET(interface_off, NULL);
            nb_interfaces = *(uint32_t *)(data + interface_off);
            for (uint32_t j = 0; j < nb_interfaces; j++)
            {
                interface_off += sizeof (uint32_t);
                cur_type_idx = *(uint32_t*)(data + interface_off);
                CHECK_TYPE_IDX(cur_type_idx, NULL);
                cur_type = app->tmp->types[cur_type_idx];
                dxp_class_add_interface(new_item, cur_type);
            }
        }

        // update the class list of our dexfile
        inserted_item = dxp_class_add(app, new_item);

        // update the fast indexed list
        app->tmp->classes[i] = inserted_item;
    }

    return (0);
}
