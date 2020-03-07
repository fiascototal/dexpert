#ifndef __DEBUG_H__
# define __DEBUG_H__

# ifdef _DXP_DEBUG

# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>

# define ERR_MSG strerror(errno)
# define DXP_DEBUG(...) do { fprintf(stderr, __VA_ARGS__); } while(0)

# define CHECK_NULL_FATAL(arg) if (arg == NULL) { DXP_DEBUG("[-] cannot be null\n"); exit(1); }
# define CHECK_ARG(arg, ret) if (arg == NULL) { DXP_DEBUG("[-] invalid NULL argument\n"); return (ret); }
# define CHECK_ALLOCATION(ptr, ret) if (ptr == NULL) { DXP_DEBUG("[-] out of memory\n"); return (ret); }
# define CHECK_OFFSET(off, ret) if (off >= cache->size) { DXP_DEBUG("[-] invalid offset (0x%x) out of file\n", off); return (ret); }
# define CHECK_STRING_IDX(idx, ret) if (idx >= cache->hdr->stringIdsSize) { DXP_DEBUG("[-] invalid string index (0x%x)\n", idx); return (ret); }
# define CHECK_TYPE_IDX(idx, ret) if (idx >= cache->hdr->typeIdsSize) { DXP_DEBUG("[-] invalid type index (0x%x)\n", idx); return (ret); }
# define CHECK_PROTOTYPE_IDX(idx, ret) if (idx >= cache->hdr->protoIdsSize) { DXP_DEBUG("[-] invalid prototype index (0x%x)\n", idx); return (ret); }
# define CHECK_FIELD_IDX(idx, ret) if (idx >= cache->hdr->fieldIdsSize) { DXP_DEBUG("[-] invalid field index (0x%x)\n", idx); return (ret); }
# define CHECK_METHOD_IDX(idx, ret) if (idx >= cache->hdr->methodIdsSize) { DXP_DEBUG("[-] invalid method index (0x%x)\n", idx); return (ret); }


# else/*!_DXP_DEBUG*/

# define ERR_MSG ""
# define DXP_DEBUG(...) do {} while(0)

# define CHECK_NULL_FATAL(arg)
# define CHECK_ARG(arg, ret)
# define CHECK_ALLOCATION(ptr, ret)
# define CHECK_OFFSET(off, ret)
# define CHECK_STRING_IDX(idx, ret)
# define CHECK_TYPE_IDX(idx, ret)
# define CHECK_PROTOTYPE_IDX(idx, ret)
# define CHECK_FIELD_IDX(idx, ret)
# define CHECK_METHOD_IDX(idx, ret)

# endif/*!_DXP_DEBUG*/

#endif/*!__DEBUG_H__*/
