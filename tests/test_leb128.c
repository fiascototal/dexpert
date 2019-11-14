#include "../src/utils/leb128.h"
#include <stdio.h>
#include <string.h>


int main()
{
    unsigned char in[6] = {0x00, 0x01, 0x7F, 0x80, 0x7F, 0x00};
    unsigned char out[3];
    int32_t  i1 = 0;
    uint32_t i2 = 0,
             nb = 0;

    // 1)

    printf("test sleb128\n");

    // 1.1) READING 

    if ((nb = sleb128_decode(in, &i1)) != 1)
        printf("sleb128_decode failed, nb_read(%d) should be 1\n", nb);
    if (i1 != 0)
        printf("sleb128_decode failed, result(%d) should be 0\n", i1);

    if ((nb = sleb128_decode(in+1, &i1)) != 1)
        printf("sleb128_decode failed, nb_read(%d) should be 1\n", nb);
    if (i1 != 1)
        printf("sleb128_decode failed, result(%d) should be 1\n", i1);

    if ((nb = sleb128_decode(in+2, &i1)) != 1)
        printf("sleb128_decode failed, nb_read(%d) should be 1\n", nb);
    if (i1 != -1)
        printf("sleb128_decode failed, result(%d) should be -1\n", i1);

    if ((nb = sleb128_decode(in+3, &i1)) != 2)
        printf("sleb128_decode failed, nb_read(%d) should be 2\n", nb);
    if (i1 != -128)
        printf("sleb128_decode failed, result(%d) should be -128\n", i1);

    // 1.2) WRITING
    
    memset(out, 0, sizeof(out));
    if ((nb = sleb128_encode(out, 0)) != 1)
        printf("sleb128_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x00 || out[1] != 0x00 || out[2] != 0x00)
        printf("sleb128_encode failed, result(%02x %02x %02x) should be 0x00 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = sleb128_encode(out, 1)) != 1)
        printf("sleb128_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x01 || out[1] != 0x00 || out[2] != 0x00)
        printf("sleb128_encode failed, result(%02x %02x %02x) should be 0x01 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = sleb128_encode(out, -1)) != 1)
        printf("sleb128_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x7f || out[1] != 0x00 || out[2] != 0x00)
        printf("sleb128_encode failed, result(%02x %02x %02x) should be 0x7F 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = sleb128_encode(out, -128)) != 2)
        printf("sleb128_encode failed, nb_write(%d) should be 2\n", nb);
    if (out[0] != 0x80 || out[1] != 0x7F || out[2] != 0x00)
        printf("sleb128_encode failed, result(%02x %02x %02x) should be 0x80 0x7F 0x00\n", out[0], out[1], out[2]);


    // 2)
    printf("test uleb128\n");

    // 2.1) READING 

    if ((nb = uleb128_decode(in, &i2)) != 1)
        printf("uleb128_decode failed, nb_read(%d) should be 1\n", nb);
    if (i2 != 0)
        printf("uleb128_decode failed, result(%d) should be 0\n", i2);

    if ((nb = uleb128_decode(in+1, &i2)) != 1)
        printf("uleb128_decode failed, nb_read(%d) should be 1\n", nb);
    if (i2 != 1)
        printf("uleb128_decode failed, result(%d) should be 1\n", i2);

    if ((nb = uleb128_decode(in+2, &i2)) != 1)
        printf("uleb128_decode failed, nb_read(%d) should be 1\n", nb);
    if (i2 != 127)
        printf("uleb128_decode failed, result(%d) should be 127\n", i2);

    if ((nb = uleb128_decode(in+3, &i2)) != 2)
        printf("uleb128_decode failed, nb_read(%d) should be 2\n", nb);
    if (i2 != 16256)
        printf("uleb128_decode failed, result(%d) should be 16256\n", i2);

    // 2.2) WRITING
    
    memset(out, 0, sizeof(out));
    if ((nb = uleb128_encode(out, 0)) != 1)
        printf("uleb128_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x00 || out[1] != 0x00 || out[2] != 0x00)
        printf("uleb128_encode failed, result(%02x %02x %02x) should be 0x00 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = uleb128_encode(out, 1)) != 1)
        printf("uleb128_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x01 || out[1] != 0x00 || out[2] != 0x00)
        printf("uleb128_encode failed, result(%02x %02x %02x) should be 0x01 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = uleb128_encode(out, 127)) != 1)
        printf("uleb128_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x7f || out[1] != 0x00 || out[2] != 0x00)
        printf("uleb128_encode failed, result(%02x %02x %02x) should be 0x7F 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = uleb128_encode(out, 16256)) != 2)
        printf("uleb128_encode failed, nb_write(%d) should be 2\n", nb);
    if (out[0] != 0x80 || out[1] != 0x7F || out[2] != 0x00)
        printf("uleb128_encode failed, result(%02x %02x %02x) should be 0x80 0x7F 0x00\n", out[0], out[1], out[2]);


    // 3)
    printf("test uleb128p1\n");

    // 3.1) READING 

    if ((nb = uleb128p1_decode(in, &i1)) != 1)
        printf("uleb128p1_decode failed, nb_read(%d) should be 1\n", nb);
    if (i1 != -1)
        printf("uleb128p1_decode failed, result(%d) should be -1\n", i1);

    if ((nb = uleb128p1_decode(in+1, &i1)) != 1)
        printf("uleb128p1_decode failed, nb_read(%d) should be 1\n", nb);
    if (i1 != 0)
        printf("uleb128p1_decode failed, result(%d) should be 0\n", i1);

    if ((nb = uleb128p1_decode(in+2, &i1)) != 1)
        printf("uleb128p1_decode failed, nb_read(%d) should be 1\n", nb);
    if (i1 != 126)
        printf("uleb128p1_decode failed, result(%d) should be 126\n", i1);

    if ((nb = uleb128p1_decode(in+3, &i1)) != 2)
        printf("uleb128p1_decode failed, nb_read(%d) should be 2\n", nb);
    if (i1 != 16255)
        printf("uleb128p1_decode failed, result(%d) should be 16255\n", i1);

    // 3.2) WRITING
    
    memset(out, 0, sizeof(out));
    if ((nb = uleb128p1_encode(out, -1)) != 1)
        printf("uleb128p1_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x00 || out[1] != 0x00 || out[2] != 0x00)
        printf("uleb128p1_encode failed, result(%02x %02x %02x) should be 0x00 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = uleb128p1_encode(out, 0)) != 1)
        printf("uleb128p1_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x01 || out[1] != 0x00 || out[2] != 0x00)
        printf("uleb128p1_encode failed, result(%02x %02x %02x) should be 0x01 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = uleb128p1_encode(out, 126)) != 1)
        printf("uleb128p1_encode failed, nb_write(%d) should be 1\n", nb);
    if (out[0] != 0x7f || out[1] != 0x00 || out[2] != 0x00)
        printf("uleb128p1_encode failed, result(%02x %02x %02x) should be 0x7F 0x00 0x00\n", out[0], out[1], out[2]);

    memset(out, 0, sizeof(out));
    if ((nb = uleb128p1_encode(out, 16255)) != 2)
        printf("uleb128p1_encode failed, nb_write(%d) should be 2\n", nb);
    if (out[0] != 0x80 || out[1] != 0x7F || out[2] != 0x00)
        printf("uleb128p1_encode failed, result(%02x %02x %02x) should be 0x00 0x00 0x00\n", out[0], out[1], out[2]);

    printf("Done.\n");
    return (0);
}
