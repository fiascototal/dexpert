#include <stdio.h>
#include <stdlib.h>

#include <dexpert/dexfile.h>
#include <dexpert/debug.h>
#include <dexpert/file_utils.h>
#include "dexfile_structure.h"
#include "parsing/parsers.h"


int dexfile_new(dexfile_t *arg)
{
    struct s_dexfile *dex = NULL;

    if (arg == NULL)
    {
        DEBUG("[-] invalid arg\n");
        return (1);
    }

    dex = (struct s_dexfile *)malloc(sizeof (struct s_dexfile));
    if (dex == NULL)
    {
        DEBUG("[-] failed to allocate the dex object (%s)\n", ERR_MSG);
        return (2);
    }
    memset(dex, 0, sizeof (struct s_dexfile));

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


int parse_dexfile(dexfile_t dex, const char *dex_path)
{
    uint8_t *dex_data      = NULL;
    uint64_t dex_data_size = 0;

    if (read_file(dex_path, &dex_data, &dex_data_size) != 0)
    {
        DEBUG("[-] read dex file failed %s\n", dex_path);
        return (2);
    }

    if (parse_dexdata(dex, dex_data, dex_data_size) != 0)
    {
        DEBUG("[-] failed to parse the given dex\n");
        free(dex_data); dex_data = NULL;
        return (3);
    }

    free(dex_data); dex_data = NULL;
    return (0);
}


int parse_dexdata(dexfile_t arg, uint8_t *dex_data, uint64_t dex_data_size)
{
    struct s_dexfile *dex = (struct s_dexfile *)arg;
    header_item *hdr = NULL;
    
    if (dex_data == NULL)
    {
        DEBUG("[-] invalid arguments\n");
        return (1);
    }

    // let's say that the beginning is directly in the header format
    hdr = (header_item *)dex_data;
    if (parse_headers(dex, hdr, dex_data, dex_data_size) != 0)
    {
        DEBUG("[-] invalid dex header\n");
        return (2);
    }

    return (0);
}
