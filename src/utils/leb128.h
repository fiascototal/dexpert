#ifndef __LEB128_H__
# define __LEB128_H__

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