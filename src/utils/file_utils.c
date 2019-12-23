#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <dexpert/file_utils.h>
#include "../debug.h"


int read_file(const char *filepath, uint8_t **data, uint64_t *data_size)
{
    uint8_t    *result      = NULL;
    uint64_t    result_size = 0;
    int         fd          = 0;
    struct stat st;

    CHECK_ARG(data, 1);
    CHECK_ARG(data_size, 1);

    if ((fd = open(filepath, O_RDONLY)) < 0)
    {
        DXP_DEBUG("[-] failed to open file %s (%s)\n", filepath, ERR_MSG);
        return (2);
    }

    // get file size
    memset(&st, 0, sizeof (struct stat));
    if (fstat(fd, &st) != 0)
    {
        DXP_DEBUG("[-] failed to stat file %s (%s)\n", filepath, ERR_MSG);
        close(fd);
        return (3);
    }
    result_size = st.st_size;

    // alocate a buffer to receiv the file content
    result = (uint8_t *)malloc(result_size);
    if (result == NULL)
    {
        DXP_DEBUG("[-] allocate file for %s failed (%s)\n", filepath, ERR_MSG);
        close(fd);
        return (4);
    }

    // read the dex file
    if (read(fd, result, result_size) < 0)
    {
        DXP_DEBUG("[-] read file failed %s (%s)\n", filepath, ERR_MSG);
        close(fd);
        free(result); result = NULL;
        return (5);
    }

    close(fd);
    *data = result;
    *data_size = result_size;

    return (0);
}
