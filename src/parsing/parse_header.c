#include <string.h>
#include <dexpert/debug.h>
#include <utils/adler32.h>
#include "parsers.h"


int parse_header(struct s_application *app)
{
    if (app == NULL)
    {
        DEBUG("[-] parse header failed, invalid argument\n");
        return (1);
    }

    app->tmp.hdr = (struct s_header_item *)app->tmp.data;
    
    // check the magic "dex\n"
    if (memcmp(app->tmp.hdr->magic, DEX_MAGIC_VERS_35, 4) != 0)
    {
        DEBUG("[-] invalid dex magic\n");
        return (2);
    }

    // set the version
    if (memcmp(app->tmp.hdr->magic, DEX_MAGIC_VERS_35, 8) == 0)
    {
        app->version = DEX_35;
    }
    else
    {
        DEBUG("[-] sorry the dex version is not supported\n");
        return (3);
    }

    if (app->tmp.hdr->fileSize > app->tmp.size)
    {
        DEBUG("[-] invalid dex size (too big)\n");
        return (4);
    }

    if (adler32(1, app->tmp.data + 8 + sizeof (uint32_t), app->tmp.hdr->fileSize - 8 - sizeof (uint32_t)) != app->tmp.hdr->checksum)
    {
        DEBUG("[-] invalid dex checksum\n");
        return (5);
    }

    if (app->tmp.hdr->endianTag != ENDIAN_CONSTANT)
    {
        DEBUG("[-] sorry the reverse endianess is not supported\n");
        return (6);
    }

    return (0);
}
