#ifndef __PARSE_DEX_H__
# define __PARSE_DEX_H__

# include <stdint.h>
# include "../internal_structures/application.h"


// parse the given DEX data
int parse_dex(struct s_application *app, uint8_t *data, uint64_t data_size);

#endif/*!__PARSE_DEX_H__*/
