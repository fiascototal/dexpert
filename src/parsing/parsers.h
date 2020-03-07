#ifndef __PARSERS_H__
# define __PARSERS_H__

# include "dex_cache.h"


// parse the DEX header of the given data
int parse_header(struct s_dex_cache *cache);

// parse the map list
int parse_map(struct s_dex_cache *cache);

// parse the strings table
int parse_strings(struct s_dex_cache *cache);

// parse the types table
int parse_types(struct s_dex_cache *cache);

// parse the prototypes table
int parse_prototypes(struct s_dex_cache *cache);

// parse the fields table
int parse_fields(struct s_dex_cache *cache);

// parse the methods table
int parse_methods(struct s_dex_cache *cache);

// parse the classes table
int parse_classes(struct s_dex_cache *cache);

#endif/*!__PARSERS_H__*/
