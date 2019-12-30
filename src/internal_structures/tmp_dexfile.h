#ifndef __TMP_DEXFILE_H__
# define __TMP_DEXFILE_H__

# include <stdint.h>
# include "../dex_objects/dex_header.h"
# include <dexpert/dxp_string.h>
# include <dexpert/dxp_type.h>
# include <dexpert/dxp_prototype.h>
# include <dexpert/dxp_field.h>
# include <dexpert/dxp_method.h>
# include <dexpert/dxp_class.h>


/*
** A "temporary" structure useful when parsing a dex file
*/
struct s_tmp_dexfile
{
    // the dex buffer
    uint8_t *data;
    uint32_t size;

    // the orginal dex header
    struct s_header_item *hdr;

    // an array of strings. We need it for keeping indexes
    dxp_string *strings;

    // an array of types. We need it for keeping indexes
    dxp_type *types;

    // an array of prototypes. We need it for keeping indexes
    dxp_prototype *prototypes;

    // an array of fields. We need it for keeping indexes.
    dxp_field *fields;

    // an array of methods. We need it for keeping indexes.
    dxp_method *methods;

    // an array of classes. We need it for keeping indexes.
    dxp_class *classes;

    // the dex map
    // only the none redondancy elements with the header
    // @{

    uint32_t type_list_off;
    uint32_t type_list_count;

    uint32_t annotation_set_ref_list_off;
    uint32_t annotation_set_ref_list_count;

    uint32_t annotation_set_item_off;
    uint32_t annotation_set_item_count;

    uint32_t class_data_item_off;
    uint32_t class_data_item_count;

    uint32_t code_item_off;
    uint32_t code_item_count;

    uint32_t string_data_item_off;
    uint32_t string_data_item_count;

    uint32_t debug_info_item_off;
    uint32_t debug_info_item_count;

    uint32_t annotation_item_off;
    uint32_t annotation_item_count;

    uint32_t encoded_array_item_off;
    uint32_t encoded_array_item_count;

    uint32_t annotation_directory_item_off;
    uint32_t annotation_directory_item_count;

    // @}
};

#endif/*!__TMP_DEXFILE_H__*/
