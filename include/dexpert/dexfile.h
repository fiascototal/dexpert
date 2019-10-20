#ifndef __DEXFILE_H__
# define __DEXFILE_H__

# include <stdint.h>


/*
** represent a dexfile object.
*/
typedef void *dexfile_t;

/*
** open the given dex file and build a dexfile_t object (and return it)
** return 0 on success
*/
int parse_dexfile(const char *dex_path, dexfile_t *new_dex);
int parse_dexdata(uint8_t *dex_data, uint64_t dex_data_size, dexfile_t *new_dex);

/*
** clean/free all structure allocated in the given dexfile_t object
*/
void dexfile_close(dexfile_t dex);

#endif/*!__DEXFILE_H__*/
