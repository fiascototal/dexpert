#ifndef __DXP_STRING_H__
# define __DXP_STRING_H__

# include <stdint.h>

typedef void *dxp_string;

/*
** list of operators / string manipulation
*/

// allocate a new DXP_STRING object
dxp_string dxp_str_new(uint8_t *data, uint32_t data_size, uint32_t utf16_size);

// delete a DXP_STRING object
void dxp_str_del(dxp_string s);

#endif/*!__DXP_STRING_H__*/
