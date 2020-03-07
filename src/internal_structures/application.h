#ifndef __DEXFILE_PRIVATE_H__
# define __DEXFILE_PRIVATE_H__

# include <stdint.h>
# include <dexpert/version.h>
# include "../utils/dxp_rbtree.h"
# include "../utils/dxp_list.h"


/*
** the main structure: represent an Android app
*/
struct s_application
{
    // the dex version. It has some impact for some tables, some opcodes, ...
    enum e_dex_version version;

    // the string list
    dxp_rbtree strings;

    // the type list
    dxp_rbtree types;

    // the prototype list
    dxp_rbtree prototypes;

    // the field list
    dxp_rbtree fields;

    // the method list
    dxp_rbtree methods;

    // the class list
    // we do not use a RB tree because the list needs to have the super
    // class and interfaces BEFORE the current class
    dxp_list classes;
};

#endif/*!__DEXFILE_PRIVATE_H__*/
