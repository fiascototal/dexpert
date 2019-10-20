#ifndef __DEXFILE_H__
# define __DEXFILE_H__

# include <stdint.h>


/*
** represent a dexfile object.
*/
typedef void *dexfile_t;

// create a new dexfile object
int dexfile_new(dexfile_t *new_dex);

// delete a dexfile object
void dexfile_close(dexfile_t dex);

//open the given dex file and add it into the given dexfile object
int parse_dexfile(dexfile_t dex, const char *dex_path);
int parse_dexdata(dexfile_t dex, uint8_t *dex_data, uint64_t dex_data_size);

#endif/*!__DEXFILE_H__*/
