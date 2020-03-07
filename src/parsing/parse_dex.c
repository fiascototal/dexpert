#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse_dex.h"
#include "parsers.h"
#include "../debug.h"


static void _allocate_cache(struct s_dex_cache *cache)
{
    uint32_t count = 0;

    count = cache->hdr->stringIdsSize;
    cache->strings = (dxp_string *)malloc(sizeof (dxp_string) * count);
    memset(cache->strings, 0, sizeof (dxp_string) * count);

    count = cache->hdr->typeIdsSize;
    cache->types = (dxp_type *)malloc(sizeof (dxp_type) * count);
    memset(cache->types, 0, sizeof (dxp_type) * count);

    count = cache->hdr->protoIdsSize;
    cache->prototypes = (dxp_prototype *)malloc(sizeof (dxp_prototype) * count);
    memset(cache->prototypes, 0, sizeof (dxp_prototype) * count);

    count = cache->hdr->fieldIdsSize;
    cache->fields = (dxp_field *)malloc(sizeof (dxp_field) * count);
    memset(cache->fields, 0, sizeof (dxp_field) * count);

    count = cache->hdr->methodIdsSize;
    cache->methods = (dxp_method *)malloc(sizeof (dxp_method) * count);
    memset(cache->methods, 0, sizeof (dxp_method) * count);

    count = cache->hdr->classDefsSize;
    cache->classes = (dxp_class *)malloc(sizeof (dxp_class) * count);
    memset(cache->classes, 0, sizeof (dxp_class) * count);
}


static void _free_cache(struct s_dex_cache *cache)
{
    if (cache->strings)
    {
        free(cache->strings);
        cache->strings = NULL;
    }

    if (cache->types)
    {
        free(cache->types);
        cache->types = NULL;
    }

    if (cache->prototypes)
    {
        free(cache->prototypes);
        cache->prototypes = NULL;
    }

    if (cache->fields)
    {
        free(cache->fields);
        cache->fields = NULL;
    }

    if (cache->methods)
    {
        free(cache->methods);
        cache->methods = NULL;
    }

    if (cache->classes)
    {
        free(cache->classes);
        cache->classes = NULL;
    }
}


int parse_dex(struct s_application *app, uint8_t *data, uint64_t data_size)
{
    int ret = 0;
    struct s_dex_cache cache;

    CHECK_ARG(app, 1);
    CHECK_ARG(data, 1);

    memset(&cache, 0, sizeof (struct s_dex_cache));

    cache.data = data;
    cache.size = (data_size & 0xFFFFFFFF);
    cache.app = app;

    if ((ret = parse_header(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex header failed (%d)\n", ret);
        return (1);
    }

    _allocate_cache(&cache);

    if ((ret = parse_map(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex map failed (%d)\n", ret);
        return (2);
    }

    if ((ret = parse_strings(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex strings failed (%d)\n", ret);
        return (3);
    }

    if ((ret = parse_types(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex types failed (%d)\n", ret);
        return (4);
    }

    if ((ret = parse_prototypes(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex prototypes failed (%d)\n", ret);
        return (5);
    }

    if ((ret = parse_fields(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex fields failed (%d)\n", ret);
        return (6);
    }

    if ((ret = parse_methods(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex methods failed (%d)\n", ret);
        return (7);
    }

    if ((ret = parse_classes(&cache)) != 0)
    {
        DXP_DEBUG("[-] parse dex classes failed (%d)\n", ret);
        return (8);
    }

    // once we have finish the parsing, we can delete the temp dex
    _free_cache(&cache);

    return (0);
}
