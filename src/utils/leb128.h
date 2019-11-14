#ifndef __LEB128_H__
# define __LEB128_H__

/*

LEB128 ("Little-Endian Base 128") is a variable-length encoding for arbitrary
signed or unsigned integer quantities. The format was borrowed from the DWARF3
specification. In a .dex file, LEB128 is only ever used to encode 32-bit
quantities.

Each LEB128 encoded value consists of one to five bytes, which together
represent a single 32-bit value. Each byte has its most significant bit set
except for the final byte in the sequence, which has its most significant bit
clear. The remaining seven bits of each byte are payload, with the least
significant seven bits of the quantity in the first byte, the next seven in the
second byte and so on. In the case of a signed LEB128 (sleb128), the most
significant payload bit of the final byte in the sequence is sign-extended to
produce the final value. In the unsigned case (uleb128), any bits not
explicitly represented are interpreted as 0

*/

# include <stdint.h>

// DECODE the given "buf" into a signed int32_t using the SLEB128 format
// return the number of read char from "buf" + store the result in "out"
uint32_t sleb128_decode(uint8_t *buf, int32_t *out);

// ENCODE the given int32_t "arg" into "buf" using the SLEB128 format
// return the number of written char to "buf" + store the result in "out"
uint32_t sleb128_encode(uint8_t *buf, int32_t arg);



// DECODE the given "buf" into a uint32_t using the ULEB128 format
// return the number of read char from "buf" + store the result in "out"
uint32_t uleb128_decode(uint8_t *buf, uint32_t *out);

// ENCODE the given uint32_t "arg" into "buf" using the ULEB128 format
// return the number of written char to "buf" + store the result in "out"
uint32_t uleb128_encode(uint8_t *buf, uint32_t arg);



// DECODE the given "buf" into a signed uint32_t using the ULEB128P1 format
// return the number of read char from "buf" + store the result in "out"
uint32_t uleb128p1_decode(uint8_t *buf, int32_t *out);

// ENCODE the given uint32_t "arg" into "buf" using the ULEB128P1 format
// return the number of written char to "buf" + store the result in "out"
uint32_t uleb128p1_encode(uint8_t *buf, int32_t arg);

#endif /*!__LEB128_H__*/
