#include <stdlib.h>
#include <string.h>
#include <dexpert/dxp_string.h>
#include "utils/crc32.h"


/*
** out internal representation of a string
*/
struct s_dxp_string
{
    uint32_t checksum;
    uint32_t utf16_size;
    uint32_t data_size;
    uint8_t *data;
};


dxp_string dxp_str_new(uint8_t *data, uint32_t data_size, uint32_t utf16_size)
{
    struct s_dxp_string *result = NULL;

    result = (struct s_dxp_string *)malloc(sizeof (struct s_dxp_string));
    memset(result, 0, sizeof (struct s_dxp_string));

    result->data = (uint8_t *)malloc(data_size);
    memcpy(result->data, data, data_size);
    result->utf16_size = utf16_size;
    result->checksum = crc32(data, data_size);

    return ((dxp_string)result);
}

void dxp_str_del(dxp_string s)
{
    struct s_dxp_string *str = (struct s_dxp_string *)s;

    if (str)
    {
        if (str->data)
        {
            free(str->data); str->data = NULL;
        }
        free(str); str = NULL;
    }
}
