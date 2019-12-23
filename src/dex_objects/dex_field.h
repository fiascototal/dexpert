#ifndef __DEX_FIELD_H__
# define __DEX_FIELD_H__

# include <stdint.h>

/*
appears in the field_ids section
alignment: 4 bytes
*/

struct s_field_id_item
{
    // index into the type_ids list for the definer of this field.
    // This must be a class type, and not an array or primitive type. 
    uint16_t class_idx;

    // index into the type_ids list for the type of this field
    uint16_t type_idx;

    // index into the string_ids list for the name of this field.
    // The string must conform to the syntax for MemberName, defined above. 
    uint32_t name_idx;
};
typedef struct s_field_id_item field_id_item;

#endif/*!__DEX_FIELD_H__*/
