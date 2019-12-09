#include <stdio.h>
#include <dexpert/debug.h>
#include <dex_objects/dex_map.h>
#include "parsers.h"


int parse_map(struct s_application *app)
{
    uint32_t           map_elt_count = 0,
                       cur_off       = 0;
    struct s_map_item *cur_item      = NULL;

    if (app == NULL)
    {
        DEBUG("[-] invalid argument\n");
        return (1);
    }

    cur_off = app->tmp->hdr->mapOff;
    if (cur_off + sizeof (uint32_t) > app->tmp->size)
    {
        DEBUG("[-] map offset (0x%x) is out of the dexfile (sz: 0x%x)\n", cur_off, app->tmp->size);
        return (2);
    }

    // get the number of map entries
    map_elt_count = *(uint32_t *)(app->tmp->data + cur_off);
    cur_off += sizeof (uint32_t);

    // iterate on all map entries
    for (uint32_t i = 0; i < map_elt_count; i++)
    {
        if (cur_off + sizeof (struct s_map_item) > app->tmp->size)
        {
            DEBUG("[-] map entry at 0x%x is out of the dexfile (sz: 0x%x)\n", cur_off, app->tmp->size);
            return (3);
        }

        cur_item = (struct s_map_item *)(app->tmp->data + cur_off);
        cur_off += sizeof (struct s_map_item);

        if (cur_item->offset > app->tmp->size)
        {
            DEBUG("[-] invalid offset 0x%x in map entry 0x%x\n", cur_item->offset, cur_item->type);
            return (4);
        }

        switch (cur_item->type)
        {
        case TYPE_HEADER_ITEM:
            break;
        case TYPE_STRING_ID_ITEM:
            break;
        case TYPE_TYPE_ID_ITEM:
            break;
        case TYPE_PROTO_ID_ITEM:
            break;
        case TYPE_FIELD_ID_ITEM:
            break;
        case TYPE_METHOD_ID_ITEM:
            break;
        case TYPE_CLASS_DEF_ITEM:
            break;
        case TYPE_CALL_SITE_ID_ITEM:
            break;
        case TYPE_METHOD_HANDLE_ITEM:
            break;
        case TYPE_MAP_LIST:
            break;
        case TYPE_TYPE_LIST:
            app->tmp->type_list_off = cur_item->offset;
            app->tmp->type_list_count = cur_item->size;
            break;
        case TYPE_ANNOTATION_SET_REF_LIST:
            app->tmp->annotation_set_ref_list_off = cur_item->offset;
            app->tmp->annotation_set_ref_list_count = cur_item->size;
            break;
        case TYPE_ANNOTATION_SET_ITEM:
            app->tmp->annotation_set_item_off = cur_item->offset;
            app->tmp->annotation_set_item_count = cur_item->size;
            break;
        case TYPE_CLASS_DATA_ITEM:
            app->tmp->class_data_item_off = cur_item->offset;
            app->tmp->class_data_item_count = cur_item->size;
            break;
        case TYPE_CODE_ITEM:
            app->tmp->code_item_off = cur_item->offset;
            app->tmp->code_item_count = cur_item->size;
            break;
        case TYPE_STRING_DATA_ITEM:
            app->tmp->string_data_item_off = cur_item->offset;
            app->tmp->string_data_item_count = cur_item->size;
            break;
        case TYPE_DEBUG_INFO_ITEM:
            app->tmp->debug_info_item_off = cur_item->offset;
            app->tmp->debug_info_item_count = cur_item->size;
            break;
        case TYPE_ANNOTATION_ITEM:
            app->tmp->annotation_item_off = cur_item->offset;
            app->tmp->annotation_item_count = cur_item->size;
            break;
        case TYPE_ENCODED_ARRAY_ITEM:
            app->tmp->encoded_array_item_off = cur_item->offset;
            app->tmp->encoded_array_item_count = cur_item->size;
            break;
        case TYPE_ANNOTATIONS_DIRECTORY_ITEM:
            app->tmp->annotation_directory_item_off = cur_item->offset;
            app->tmp->annotation_directory_item_count = cur_item->size;
            break;
        default:
            DEBUG("[-] invalid map entry, unknown type 0x%x\n", cur_item->type);
            return (5);
            break;
        }
    }

    return (0);
}
