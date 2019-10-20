#ifndef __DEBUG_H__
# define __DEBUG_H__

# ifdef _IS_DEBUG

# include <string.h>
# include <stdio.h>
# include <errno.h>

# define ERR_MSG strerror(errno)
# define DEBUG(...) do { fprintf(stderr, __VA_ARGS__); } while(0)

# else/*!_IS_DEBUG*/

# define DEBUG(...) do {} while(0)
# define DEBUG_ERRNO(...) do {} while(0)

# endif/*!_IS_DEBUG*/

#endif/*!__DEBUG_H__*/
