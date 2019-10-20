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

    if (dexfile_new(&dex) != 0)
    {
        fprintf(stderr, "[-] failed to build a dex object\n");
        return (2);
    }

    if (parse_dexfile(dex, argv[1]) != 0)
    {
        fprintf(stderr, "[-] failed to parse the given dex file %s\n", argv[1]);
        return (3);
    }

    printf("[+] Ok\n");

    dexfile_close(dex);
    return (0);
}
