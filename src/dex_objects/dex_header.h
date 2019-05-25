#ifndef __DEX_HEADER__
# define __DEX_HEADER__

# include <stdint.h>

/* DEX file magic number */
# define DEX_MAGIC       "dex\n"

/* versions, encoded in 4 bytes of ASCII */
# define DEX_MAGIC_VERS_35  "035\0"
# define DEX_MAGIC_VERS_36  "036\0"
# define DEX_MAGIC_VERS_38  "038\0"

# define ENDIAN_CONSTANT			0x12345678;
# define REVERSE_ENDIAN_CONSTANT	0x78563412;

# define kSHA1DigestLen 20

/*
 * Direct-mapped "header_item" struct.
 */
struct s_dex_header {
    uint8_t   magic[8];           /* includes version number */
    uint32_t  checksum;           /* adler32 checksum */
    uint8_t   signature[kSHA1DigestLen]; /* SHA-1 hash */
    uint32_t  fileSize;           /* length of entire file */
    uint32_t  headerSize;         /* offset to start of next section */
    uint32_t  endianTag;
    uint32_t  linkSize;
    uint32_t  linkOff;
    uint32_t  mapOff;
    uint32_t  stringIdsSize;
    uint32_t  stringIdsOff;
    uint32_t  typeIdsSize;
    uint32_t  typeIdsOff;
    uint32_t  protoIdsSize;
    uint32_t  protoIdsOff;
    uint32_t  fieldIdsSize;
    uint32_t  fieldIdsOff;
    uint32_t  methodIdsSize;
    uint32_t  methodIdsOff;
    uint32_t  classDefsSize;
    uint32_t  classDefsOff;
    uint32_t  dataSize;
    uint32_t  dataOff;
};

#endif /*!__DEX_HEADER__*/