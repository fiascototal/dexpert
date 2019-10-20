CC=clang
INCLUDES=-I../include
CFLAGS=-W -Wall -ansi -pedantic $(INCLUDES)
LDFLAGS=-pie
LIB_NAME=../src/dexpert.a

all: read_dex

read_dex: read_dex.c $(LIB_NAME)
	$(CROSS)$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(LIB_NAME):
	make -C $(dir $(LIB_NAME)) $(basename $(LIB_NAME))

clean:
	rm -f read_dex
	find . -name "*.o" -print -delete
	make -C $(dir $(LIB_NAME)) clean
