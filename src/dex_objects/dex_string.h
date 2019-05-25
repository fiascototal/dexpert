#ifndef __DEX_STRING_H__
# define __DEX_STRING_H__

# include <stdint.h>

/*
offset from the start of the file to the string data for this item. The offset
should be to a location in the data section, and the data should be in the
format specified by "string_data_item" below. There is no alignment requirement
for the offset. 
*/
typedef uint32_t string_data_off;

/*
appears in the data section
alignment: none (byte-aligned)
*/
struct s_string_data_item
{
    // size of this string, in UTF-16 code units (which is the "string length"
    // in many systems). That is, this is the decoded length of the string.
    // (The encoded length is implied by the position of the 0 byte.)
    uint32_t utf16_size;

    // a series of MUTF-8 code units (a.k.a. octets, a.k.a. bytes) followed
    // by a byte of value 0. See "MUTF-8 (Modified UTF-8) Encoding" above for
    // details and discussion about the data format. 
    uint8_t  data;
};
typedef struct s_string_data_item string_data_item;

#endif/*!__DEX_STRING_H__*/
