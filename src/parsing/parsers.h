#ifndef __PARSERS_H__
# define __PARSERS_H__

# include <stdint.h>
# include <internal_structures/application.h>


// parse the given DEX data
int parse_dex(struct s_application *app, uint8_t *data, uint64_t data_size);

// parse the DEX header of the given data
int parse_header(struct s_application *app);

// parse the map list
int parse_map(struct s_application *app);

// parse the strings table
int parse_strings(struct s_application *app);

// parse the types table
int parse_types(struct s_application *app);

// parse the prototypes table
int parse_prototypes(struct s_application *app);

#endif/*!__PARSERS_H__*/
