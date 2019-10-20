CC=clang
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-pie

all: leb128

leb128: ../src/utils/leb128.c test_leb128.c
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -rf leb128 *.o
