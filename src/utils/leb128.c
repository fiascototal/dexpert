#include "leb128.h"

uint32_t sleb128_decode(uint8_t *buf, int32_t *out)
{
	uint32_t nb_char_read = 0,
			 tmp          = 0;
	int32_t  result       = 0;
	uint8_t  c			  = 0;

	do
	{
		c = buf[nb_char_read];
		tmp = c;
		tmp = (tmp & 0x7F) << (7 * nb_char_read);
		result |= tmp;
		nb_char_read++;
	}
	while (c & 0x80);

	result <<= (32 - (7 * nb_char_read));
	result >>= (32 - (7 * nb_char_read));

	*out = result;
	return (nb_char_read);
}

uint32_t sleb128_encode(uint8_t *buf, int32_t arg)
{
	uint32_t nb_char_written = 0;

	do
	{
		buf[nb_char_written] = (arg & 0x7F);
		if ((arg > 0x7F) || (arg < 0 && (arg >> 7 != arg)))
			buf[nb_char_written] |= 0x80;
		nb_char_written++;
		if (arg >> 7 == arg)
			break;
		arg >>= 7;
	}
	while (arg);

	return (nb_char_written);
}

uint32_t uleb128_decode(uint8_t *buf, uint32_t *out)
{
	uint32_t nb_char_read = 0,
			 tmp		  = 0,
			 result		  = 0;
	uint8_t  c			  = 0;

	do
	{
		c = buf[nb_char_read];
		tmp = (c & 0x7F) << (7 * nb_char_read);
		result |= tmp;
		nb_char_read++;
	} while (c & 0x80);

	*out = result;
	return (nb_char_read);
}

uint32_t uleb128_encode(uint8_t *buf, uint32_t arg)
{
	uint32_t nb_char_written = 0;

	do
	{
		buf[nb_char_written] = (arg & 0x7F);
		arg >>= 7;
		if (arg > 0)
			buf[nb_char_written] |= 0x80;
		nb_char_written++;
	}
	while (arg > 0);

	return (nb_char_written);
}

uint32_t uleb128p1_decode(uint8_t *buf, int32_t *out)
{
	uint32_t result       = 0,
		     nb_read_byte = uleb128_decode(buf, &result);

	*out = ((int32_t)result - 1);
	return (nb_read_byte);
}

uint32_t uleb128p1_encode(uint8_t *buf, int32_t arg)
{
	uint32_t result = (uint32_t)(arg + 1);
	return (uleb128_encode(buf, result));
}