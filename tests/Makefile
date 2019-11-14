CC=clang
CFLAGS=-W -Wall -ansi -pedantic -std=c11 -g -ggdb
LDFLAGS=-pie

all: leb128 rbtree

leb128: ../src/utils/leb128.c test_leb128.c
	${CC} ${CFLAGS} -o $@ $^

rbtree: ../src/utils/dxp_rbtree.c test_rbtree.c
	${CC} ${CFLAGS} -o $@ $^ -I../include

clean:
	rm -rf leb128 rbtree *.o
