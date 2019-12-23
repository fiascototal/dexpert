#ifndef __DEBUG_H__
# define __DEBUG_H__

# ifdef _DXP_DEBUG

# include <string.h>
# include <stdio.h>
# include <errno.h>

# define ERR_MSG strerror(errno)
# define DXP_DEBUG(...) do { fprintf(stderr, __VA_ARGS__); } while(0)

# define CHECK_ARG(arg, ret) if (arg == NULL) { DXP_DEBUG("[-] invalid NULL argument\n"); return (ret); }
# define CHECK_ALLOCATION(ptr, ret) if (ptr == NULL) { DXP_DEBUG("[-] out of memory\n"); return (ret); }
# define CHECK_OFFSET(off, ret) if (off >= app->tmp->size) { DXP_DEBUG("[-] invalid offset (0x%x) out of file\n", off); return (ret); }
# define CHECK_STRING_IDX(idx, ret) if (idx >= app->tmp->hdr->stringIdsSize) { DXP_DEBUG("[-] invalid string index (0x%x)\n", idx); return (ret); }
# define CHECK_TYPE_IDX(idx, ret) if (idx >= app->tmp->hdr->typeIdsSize) { DXP_DEBUG("[-] invalid type index (0x%x)\n", idx); return (ret); }

# else/*!_DXP_DEBUG*/

# define ERR_MSG ""
# define DXP_DEBUG(...) do {} while(0)

# define CHECK_ARG(arg, ret)
# define CHECK_ALLOCATION(ptr, ret)
# define CHECK_OFFSET(off, ret)
# define CHECK_STRING_IDX(idx, ret)
# define CHECK_TYPE_IDX(idx, ret)

# endif/*!_DXP_DEBUG*/

#endif/*!__DEBUG_H__*/
