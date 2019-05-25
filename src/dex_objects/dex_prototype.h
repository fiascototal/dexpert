#ifndef __DEX_PROTOTYPE_H__
# define __DEX_PROTOTYPE_H__

# include <stdint.h>

/*
appears in the proto_ids section
alignment: 4 bytes
*/

struct s_proto_id_item
{
    // index into the string_ids list for the short-form descriptor string of
    // this prototype. The string must conform to the syntax for
    // ShortyDescriptor, defined above, and must correspond to the return type
    // and parameters of this item. 
    uint32_t shorty_idx;

    // index into the type_ids list for the return type of this prototype 
    uint32_t return_type_idx;

    // offset from the start of the file to the list of parameter types for
    // this prototype, or 0 if this prototype has no parameters. This offset,
    // if non-zero, should be in the data section, and the data there should
    // be in the format specified by "type_list" below. Additionally, there
    // should be no reference to the type void in the list. 
    uint32_t parameters_off;
};

#endif/*!__DEX_PROTOTYPE_H__*/
