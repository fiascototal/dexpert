#include <stdio.h>

#include <dexpert/dexfile.h>
#include <dexpert/debug.h>
#include <dexpert/file_utils.h>
#include "dexfile_private.h"


int parse_dexfile(const char *dex_path, dexfile_t *arg)
{
    uint8_t *dex_data      = NULL;
    uint64_t dex_data_size = 0;

    if (arg == NULL)
    {
        DEBUG("[-] invalid arg\n");
        return (1);
    }

    if (read_file(dex_path, &dex_data, &dex_data_size) != 0)
    {
        DEBUG("[-] read dex file failed %s\n", dex_path);
        return (2);
    }

    if (parse_dexdata(dex_data, dex_data_size, arg) != 0)
    {
        DEBUG("[-] failed to parse the given dex\n");
        free(dex_data); dex_data = NULL;
        return (3);
    }

    return (0);
}


int parse_dexdata(uint8_t *dex_data, uint64_t dex_data_size, dexfile_t *arg)
{
    struct s_dexfile *dex = NULL;

    if (arg == NULL)
    {
        DEBUG("[-] invalid arg\n");
        return (1);
    }

    *arg = (dexfile_t)dex;
    return (0);
}


void dexfile_close(dexfile_t arg)
{
    struct s_dexfile *dex = (struct s_dexfile *)arg;

    if (dex == NULL)
        return;
        
    free(dex); dex = NULL;
}