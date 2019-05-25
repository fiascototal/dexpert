#ifndef __DEX_TYPE_H__
# define __DEX_TYPE_H__

# include <stdint.h>

/*
appears in the type_ids section
alignment: 4 bytes
*/

// index into the string_ids list for the descriptor string of this type. The
// string must conform to the syntax for TypeDescriptor, defined above. 
typedef uint32_t descriptor_idx;

#endif/*!__DEX_TYPE_H__*/
