#include <stdio.h>
#include "parsers.h"
#include "../dex_objects/dex_map.h"
#include "../debug.h"


int parse_map(struct s_dex_cache *cache)
{
    uint32_t           map_elt_count = 0,
                       cur_off       = 0;
    struct s_map_item *cur_item      = NULL;

    CHECK_ARG(cache, 1);

    cur_off = cache->hdr->mapOff;
    CHECK_OFFSET(cur_off, 2);

    // get the number of map entries
    map_elt_count = *(uint32_t *)(cache->data + cur_off);
    cur_off += sizeof (uint32_t);

    // iterate on all map entries
    for (uint32_t i = 0; i < map_elt_count; i++)
    {
        CHECK_OFFSET(cur_off, 2);

        cur_item = (struct s_map_item *)(cache->data + cur_off);
        cur_off += sizeof (struct s_map_item);

        CHECK_OFFSET(cur_item->offset, 2);

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
            cache->type_list_off = cur_item->offset;
            cache->type_list_count = cur_item->size;
            break;
        case TYPE_ANNOTATION_SET_REF_LIST:
            cache->annotation_set_ref_list_off = cur_item->offset;
            cache->annotation_set_ref_list_count = cur_item->size;
            break;
        case TYPE_ANNOTATION_SET_ITEM:
            cache->annotation_set_item_off = cur_item->offset;
            cache->annotation_set_item_count = cur_item->size;
            break;
        case TYPE_CLASS_DATA_ITEM:
            cache->class_data_item_off = cur_item->offset;
            cache->class_data_item_count = cur_item->size;
            break;
        case TYPE_CODE_ITEM:
            cache->code_item_off = cur_item->offset;
            cache->code_item_count = cur_item->size;
            break;
        case TYPE_STRING_DATA_ITEM:
            cache->string_data_item_off = cur_item->offset;
            cache->string_data_item_count = cur_item->size;
            break;
        case TYPE_DEBUG_INFO_ITEM:
            cache->debug_info_item_off = cur_item->offset;
            cache->debug_info_item_count = cur_item->size;
            break;
        case TYPE_ANNOTATION_ITEM:
            cache->annotation_item_off = cur_item->offset;
            cache->annotation_item_count = cur_item->size;
            break;
        case TYPE_ENCODED_ARRAY_ITEM:
            cache->encoded_array_item_off = cur_item->offset;
            cache->encoded_array_item_count = cur_item->size;
            break;
        case TYPE_ANNOTATIONS_DIRECTORY_ITEM:
            cache->annotation_directory_item_off = cur_item->offset;
            cache->annotation_directory_item_count = cur_item->size;
            break;
        default:
            DXP_DEBUG("[-] invalid map entry, unknown type 0x%x\n", cur_item->type);
            return (5);
            break;
        }
    }

    return (0);
}
