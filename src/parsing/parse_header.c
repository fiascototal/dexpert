#include <string.h>
#include "parsers.h"
#include "../utils/adler32.h"
#include <dexpert/debug.h>


int parse_headers(struct s_dexfile *dex, header_item *hdr, uint8_t *data, uint64_t data_size)
{
    if (dex == NULL || hdr == NULL || data == NULL)
    {
        DEBUG("[-] invalid argument\n");
        return (1);
    }

    if (memcmp(hdr->magic, DEX_MAGIC_VERS_35, 4) != 0)
    {
        DEBUG("[-] invalid dex magic\n");
        return (2);
    }

    if (memcmp(hdr->magic, DEX_MAGIC_VERS_35, 8) == 0)
    {
        dex->version = DEX_35;
    }
    else
    {
        DEBUG("[-] sorry the dex version is not supported\n");
        return (3);
    }

    if (hdr->fileSize > data_size)
    {
        DEBUG("[-] invalid dex size (too big)\n");
        return (4);
    }

    if (adler32(1, (uint8_t *)hdr + 8 + sizeof (uint32_t), hdr->fileSize - 8 - sizeof (uint32_t)) != hdr->checksum)
    {
        DEBUG("[-] invalid dex checksum\n");
        return (5);
    }

    return (0);
}
