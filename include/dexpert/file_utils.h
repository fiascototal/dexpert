#ifndef __FILE_UTILS_H__
# define __FILE_UTILS_H__

# include <stdint.h>


int read_file(const char *filepath, uint8_t **data, uint64_t *data_size);

#endif/*!__FILE_UTILS_H__*/
