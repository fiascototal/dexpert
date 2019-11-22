#ifndef __DEXFILE_H__
# define __DEXFILE_H__

# include <stdint.h>
# include <dexpert/dxp_rbtree.h>


/*
** represent a dexfile object.
*/
typedef void *dexfile_t;

// create a new dexfile object
int dexfile_new(dexfile_t *new_dex);

// delete a dexfile object
void dexfile_close(dexfile_t dex);

//open the given dex file and add it into the given dexfile object
int dexfile_open_file(dexfile_t dex, const char *dex_path);
int dexfile_open_data(dexfile_t dex, uint8_t *dex_data, uint64_t dex_data_size);

// some accessors
// @{

dxp_rbtree dexfile_get_strings(dexfile_t dex);

// @}

#endif/*!__DEXFILE_H__*/
