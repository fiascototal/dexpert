#ifndef __DEXFILE_PRIVATE_H__
# define __DEXFILE_PRIVATE_H__

# include <stdint.h>
# include <dexpert/version.h>
# include <internal_structures/tmp_dexfile.h>
# include "../utils/dxp_rbtree.h"


/*
** the main structure: represent an Android app
*/
struct s_application
{
    // the dex version. It has some impact for some tables, some opcodes, ...
    enum e_dex_version version;

    // the temporary dex object (contains some tables useful for indexing)
    struct s_tmp_dexfile tmp;

    // the string list
    dxp_rbtree strings;
};

#endif/*!__DEXFILE_PRIVATE_H__*/
