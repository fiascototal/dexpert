#include <string.h>
#include <stdlib.h>
#include <dexpert/debug.h>
#include <dexpert/dxp_string.h>
#include <utils/leb128.h>
#include "parsers.h"


int parse_strings(struct s_application *app)
{
    uint32_t   string_count = 0,
               cur_off      = 0,
               string_off   = 0,
               string_size  = 0,
               utf16_size   = 0;
    uint8_t   *data         = NULL;
    dxp_string new_item,
               inserted_item;

    if (app == NULL)
    {
        DEBUG("[-] invalid arguments\n");
        return (1);
    }

    string_count = app->tmp.hdr->stringIdsSize;

    // allocate the tmp string list
    app->tmp.strings = (dxp_string *)malloc(sizeof (dxp_string) * string_count);
    memset(app->tmp.strings, 0, sizeof (dxp_string) * string_count);

    // iterate of the dex to read all strings
    data = app->tmp.data;
    cur_off = app->tmp.hdr->stringIdsOff;
    for (uint32_t i = 0; i < string_count; i++)
    {
        string_off = *(uint32_t *)(data + cur_off);
        cur_off += sizeof (uint32_t);

        // read the string size (utf16 unit)
        utf16_size = 0;
        string_off += uleb128_decode(data + string_off, &utf16_size);

        // read the string DATA size
        string_size = 0;
        while (data[string_off + string_size] != 0)
            string_size++;

        // create a new string object
        new_item = dxp_str_new(data + string_off, string_size, utf16_size);

        // update the string list of our dexfile
        inserted_item = dxp_str_add2(app, new_item);

        // update the fast indexed list
        app->tmp.strings[i] = inserted_item;
    }

    return (0);
}
