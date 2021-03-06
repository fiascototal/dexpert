#include <stdio.h>
#include <dexpert/dexfile.h>
#include <dexpert/dxp_string.h>
#include <dexpert/dxp_type.h>
#include <dexpert/dxp_prototype.h>
#include <dexpert/dxp_field.h>
#include <dexpert/dxp_method.h>
#include <dexpert/dxp_class.h>


/* Example of a small program that use the dexpert library. */

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

    if (dexfile_open_file(dex, argv[1]) != 0)
    {
        fprintf(stderr, "[-] failed to parse the given dex file %s\n", argv[1]);
        return (3);
    }

    printf("[+] %d strings\n", dxp_str_count(dex));
    printf("[+] %d types\n", dxp_type_count(dex));
    printf("[+] %d prototypes\n", dxp_proto_count(dex));
    printf("[+] %d fields\n", dxp_field_count(dex));
    printf("[+] %d methods\n", dxp_method_count(dex));
    printf("[+] %d classes\n", dxp_class_count(dex));

    dexfile_close(dex);
    return (0);
}
