#include <stdlib.h>
#include <string.h>
#include <dexpert/dxp_string.h>
#include "utils/crc32.h"
#include "internal_structures/application.h"


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

    result->data = (uint8_t *)malloc(data_size + 1);
    memset(result->data, 0, data_size + 1);
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

uint32_t dxp_str_len(dxp_string s)
{
    struct s_dxp_string *str = (struct s_dxp_string *)s;
    return (str->utf16_size);
}

// return the string raw data
uint8_t *dxp_str_data(dxp_string s)
{
    struct s_dxp_string *str = (struct s_dxp_string *)s;
    return (str->data);
}

// compare 2 strings (like strcmp)
int dxp_str_cmp(dxp_string s1, dxp_string s2)
{
    struct s_dxp_string *str1 = (struct s_dxp_string *)s1;
    struct s_dxp_string *str2 = (struct s_dxp_string *)s2;
    return (strcmp((char *)str1->data, (char *)str2->data));
}

// Add a string in the given dex file
// Return the added string (if does not already exists)
dxp_string dxp_str_add(dexfile_t app, const char *s)
{
    dxp_string new_item = dxp_str_new((uint8_t *)s, strlen(s), strlen(s));
    return (dxp_str_add2(app, new_item));
}

dxp_string dxp_str_add2(dexfile_t dex, dxp_string new_item)
{
    struct s_application *app = (struct s_application *)dex;
    dxp_string            result;

    result = dxp_rbtree_insert_unique(app->strings, new_item);

    if (result != new_item)
        dxp_str_del(new_item);

    return (result);
}

// search the given string in the given dex file
// return NULL if not found
dxp_string dxp_str_find(dexfile_t app, const char *s)
{
    dxp_string new_item = dxp_str_new((uint8_t *)s, strlen(s), strlen(s));
    dxp_string result   = dxp_str_find2(app, new_item);
    dxp_str_del(new_item);
    return (result);
}

dxp_string dxp_str_find2(dexfile_t dex, dxp_string s)
{
    struct s_application *app = (struct s_application *)dex;
    return (dxp_rbtree_find(app->strings, s));
}

dxp_str_iterator dxp_str_begin(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    return (dxp_rbtree_begin(app->strings));
}

int dxp_str_next(dxp_str_iterator it)
{
    return (dxp_rbtree_next(it));
}

int dxp_str_end(dxp_str_iterator it)
{
    return (dxp_rbtree_end(it));
}

dxp_string dxp_str_current(dxp_str_iterator it)
{
    return (dxp_rbtree_data(it));
}

void dxp_str_destroy_iterator(dxp_str_iterator it)
{
    free(it);
    it = NULL;
}

uint32_t dxp_str_count(dexfile_t dex)
{
    struct s_application *app = (struct s_application *)dex;
    return (dxp_rbtree_length(app->strings));
}
