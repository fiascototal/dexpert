#ifndef __DEX_METHOD_H__
# define __DEX_METHOD_H__

# include <stdint.h>

/*
appears in the method_ids section
alignment: 4 bytes
*/

struct s_method_id_item
{
    // index into the type_ids list for the definer of this method. 
    // This must be a class or array type, and not a primitive type. 
    uint16_t class_idx;

    // index into the proto_ids list for the prototype of this method
    uint16_t proto_idx;

    // index into the string_ids list for the name of this method. 
    // The string must conform to the syntax for MemberName, defined above. 
    uint32_t name_idx;
};
typedef struct s_method_id_item method_id_item;

#endif/*!__DEX_METHOD_H__*/
