#ifndef __DEXFILE_PRIVATE_H__
# define __DEXFILE_PRIVATE_H__

# include <stdint.h>
# include <dexpert/version.h>


struct s_dexfile
{
    // the dex version. It has some impact for some tables, some opcodes, ...
    enum e_dex_version version;
};

#endif/*!__DEXFILE_PRIVATE_H__*/
