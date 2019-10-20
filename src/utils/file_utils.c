#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <dexpert/file_utils.h>
#include <dexpert/debug.h>


int read_file(const char *filepath, uint8_t **data, uint64_t *data_size)
{
    uint8_t    *result      = NULL;
    uint64_t    result_size = 0;
    int         fd          = 0;
    struct stat st;

    if (data == NULL || data_size == NULL)
    {
        DEBUG("[-] invalid argument\n");
        return (1);
    }

    if ((fd = open(filepath, O_RDONLY)) < 0)
    {
        DEBUG("[-] failed to open file %s (%s)\n", filepath, ERR_MSG);
        return (2);
    }

    // get file size
    memset(&st, 0, sizeof (struct stat));
    if (fstat(fd, &st) != 0)
    {
        DEBUG("[-] failed to stat file %s (%s)\n", filepath, ERR_MSG);
        close(fd);
        return (3);
    }
    result_size = st.st_size;

    // alocate a buffer to receiv the file content
    result = (uint8_t *)malloc(result_size);
    if (result == NULL)
    {
        DEBUG("[-] allocate file for %s failed (%s)\n", filepath, ERR_MSG);
        close(fd);
        return (4);
    }

    // read the dex file
    if (read(fd, result, result_size) < 0)
    {
        DEBUG("[-] read file failed %s (%s)\n", filepath, ERR_MSG);
        close(fd);
        free(result); result = NULL;
        return (5);
    }

    close(fd);
    *data = result;
    *data_size = result_size;

    return (0);
}
