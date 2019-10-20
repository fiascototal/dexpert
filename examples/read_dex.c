#include <stdio.h>
#include <dexpert/dexfile.h>


int main(int argc, char *argv[])
{
    dexfile_t dex;

    if (argc != 2)
    {
        fprintf(stderr, "[-] usage: %s <dex_path>\n", argv[0]);
        return (1);
    }

    if (parse_dexfile(argv[1], &dex) != 0)
    {
        fprintf(stderr, "[-] failed to parse the given dex file %s\n", argv[1]);
        return (2);
    }

    printf("[+] Ok\n");

    dexfile_close(dex);
    return (0);
}
