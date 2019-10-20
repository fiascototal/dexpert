CC=clang
INCLUDES=-I../include -I.
CFLAGS=-W -Wall -ansi -pedantic $(INCLUDES)
LDFLAGS=
LIB_NAME=dexpert.a
LIB_SRC_FILES=					\
	lib_main.c					\
	utils/file_utils.c
LIB_OBJ_FILES=$(LIB_SRC_FILES:.c=.o)

ifdef DEBUG
	CFLAGS += -g -ggdb -D_IS_DEBUG
else
	CFLAGS += -O2
endif

all: $(LIB_NAME)

clean:
	rm -f $(LIB_NAME)
	find . -name "*.o" -print -delete

$(LIB_NAME): $(LIB_OBJ_FILES)
	$(CROSS)$(AR) -o $@ $^

%.o: %.c
	$(CROSS)$(CC) -o $@ -c $^ $(CFLAGS)
