#ifndef __DXP_STRING_H__
# define __DXP_STRING_H__

# include <stdint.h>
# include <dexpert/dexfile.h>


typedef void *dxp_string;

/*
** list of operators / string manipulation
*/

// allocate a new DXP_STRING object
dxp_string dxp_str_new(uint8_t *data, uint32_t data_size, uint32_t utf16_size);

// delete a DXP_STRING object
void dxp_str_del(dxp_string s);

// return the length of the string
uint32_t dxp_str_len(dxp_string s);

// return the string raw data
uint8_t *dxp_str_data(dxp_string s);

// compare 2 strings (like strcmp)
# define STR_EQUAL   0
# define STR_DIFF    1
# define STR_GREATER 2
# define STR_LOWER   3
int dxp_str_eq(dxp_string s1, dxp_string s2);
int dxp_str_cmp(dxp_string s1, dxp_string s2);


/*
** dexfile related primitives
*/

// Add a string in the given dex file
// Return the added string (if does not already exists)
dxp_string dxp_str_add(dexfile_t app, const char *s);
dxp_string dxp_str_add2(dexfile_t app, dxp_string new_item);

// search the given string in the given dex file
// return NULL if not found
dxp_string dxp_str_find(dexfile_t app, const char *s);
dxp_string dxp_str_find2(dexfile_t app, dxp_string s);

// list iterator
typedef void *dxp_str_iterator;
dxp_str_iterator dxp_str_begin(dexfile_t app);
int              dxp_str_next(dxp_str_iterator it);
int              dxp_str_end(dxp_str_iterator it);
dxp_string       dxp_str_current(dxp_str_iterator it);
void             dxp_str_destroy_iterator(dxp_str_iterator it);

// count of the string table
uint32_t dxp_str_count(dexfile_t app);

#endif/*!__DXP_STRING_H__*/
