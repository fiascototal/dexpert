CC=clang
INCLUDES=-I../include
CFLAGS=-W -Wall -ansi -pedantic -std=c11 -fPIC $(INCLUDES)
LDFLAGS=
LIB_NAME=dexpert.a
LIB_SRC_FILES=					\
	dexfile.c					\
	dxp_string.c				\
	dxp_type.c					\
	dxp_prototype.c				\
	dxp_field.c				    \
	utils/file_utils.c			\
	utils/adler32.c				\
	utils/dxp_rbtree.c			\
	utils/leb128.c				\
	utils/crc32.c				\
	parsing/parse_dex.c			\
	parsing/parse_header.c		\
	parsing/parse_map.c			\
	parsing/parse_strings.c		\
	parsing/parse_types.c		\
	parsing/parse_prototypes.c  \
	parsing/parse_fields.c
LIB_OBJ_FILES=$(LIB_SRC_FILES:.c=.o)

ifdef DXP_DEBUG
	CFLAGS += -g -ggdb -D_DXP_DEBUG
else
	CFLAGS += -O2
endif

all: $(LIB_NAME)

clean:
	rm -f $(LIB_NAME)
	find . -name "*.o" -print -delete

$(LIB_NAME): $(LIB_OBJ_FILES)
	$(CROSS)$(AR) csr $@ $^

%.o: %.c
	$(CROSS)$(CC) -o $@ -c $^ $(CFLAGS)
