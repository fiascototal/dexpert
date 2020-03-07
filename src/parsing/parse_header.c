#include <string.h>
#include "parsers.h"
#include "../debug.h"
#include "../utils/adler32.h"


int parse_header(struct s_dex_cache *cache)
{
    CHECK_ARG(cache, 1);

    cache->hdr = (struct s_header_item *)cache->data;

    // check the magic "dex\n"
    if (memcmp(cache->hdr->magic, DEX_MAGIC_VERS_35, 4) != 0)
    {
        DXP_DEBUG("[-] invalid dex magic\n");
        return (2);
    }

    // set the version
    if (memcmp(cache->hdr->magic, DEX_MAGIC_VERS_35, 8) == 0)
    {
        cache->app->version = DEX_35;
    }
    else
    {
        DXP_DEBUG("[-] sorry the dex version is not supported\n");
        return (3);
    }

    if (cache->hdr->fileSize > cache->size)
    {
        DXP_DEBUG("[-] invalid dex size (too big)\n");
        return (4);
    }

    if (adler32(1, cache->data + 8 + sizeof (uint32_t), cache->hdr->fileSize - 8 - sizeof (uint32_t)) != cache->hdr->checksum)
    {
        DXP_DEBUG("[-] invalid dex checksum\n");
        return (5);
    }

    if (cache->hdr->endianTag != ENDIAN_CONSTANT)
    {
        DXP_DEBUG("[-] sorry the reverse endianess is not supported\n");
        return (6);
    }

    return (0);
}
