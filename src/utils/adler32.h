#ifndef __ADLER32_H__
# define __ADLER32_H__

# include <stdint.h>

uint32_t adler32(uint32_t adler, uint8_t *buf, uint32_t len);

#endif/*!__ADLER32_H__*/
