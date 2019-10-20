#ifndef __PARSERS_H__
# define __PARSERS_H__

# include <stdint.h>
# include "../dexfile_structure.h"
# include "../dex_objects/dex_header.h"

// parse the DEX header of the given data
int parse_headers(struct s_dexfile *dex, header_item *hdr, uint8_t *data, uint64_t data_size);

#endif/*!__PARSERS_H__*/
