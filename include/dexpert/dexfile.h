#ifndef __DEXFILE_H__
# define __DEXFILE_H__

/*
** represent a dexfile object.
*/
typedef void *dexfile_t;

/*
** open the given dex file and build a dexfile_t object (and return it)
** return NULL on error
*/
dexfile_t dexfile_open(const char *dex_path);

/*
** clean/free all structure allocated in the given dexfile_t object
*/
void dexfile_close(dexfile_t dex);

#endif/*!__DEXFILE_H__*/
