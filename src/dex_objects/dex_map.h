#ifndef __MAP_LIST_H__
# define __MAP_LIST_H__

# include <stdint.h>


enum e_map_type
{
    TYPE_HEADER_ITEM,
    TYPE_STRING_ID_ITEM,
    TYPE_TYPE_ID_ITEM,
    TYPE_PROTO_ID_ITEM,
    TYPE_FIELD_ID_ITEM,
    TYPE_METHOD_ID_ITEM,
    TYPE_CLASS_DEF_ITEM,
    TYPE_CALL_SITE_ID_ITEM,
    TYPE_METHOD_HANDLE_ITEM,

    TYPE_MAP_LIST = 0x1000,
    TYPE_TYPE_LIST,
    TYPE_ANNOTATION_SET_REF_LIST,
    TYPE_ANNOTATION_SET_ITEM,

    TYPE_CLASS_DATA_ITEM = 0x2000,
    TYPE_CODE_ITEM,
    TYPE_STRING_DATA_ITEM,
    TYPE_DEBUG_INFO_ITEM,
    TYPE_ANNOTATION_ITEM,
    TYPE_ENCODED_ARRAY_ITEM,
    TYPE_ANNOTATIONS_DIRECTORY_ITEM,
};

struct s_map_item
{
    uint16_t type;
    uint16_t unused;
    uint32_t size;
    uint32_t offset;
};

struct s_map_list
{
    uint32_t          size;
    struct s_map_item list[0];
};

#endif/*!__MAP_LIST_H__*/
