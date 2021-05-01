# Define required macros here
SHELL = /bin/sh

OBJS =  test_main.o mem_pool.o
CFLAGS = -Wall -g -ansi
CC = gcc
INCLUDES = -I"./CUnit"
LIBS = -lcunit

# Single line compile!
ut: test_main.c mem_pool.c mem_pool.h
	mkdir -p ./output
	${CC} ${CFLAGS} ${INCLUDES} -o ./output/$@ $^ ${LIBS}

# More typical multiline compilation below
test_main:${OBJS}
	echo test_main
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

test_main.o: test_main.c
	echo testmain.o
	${CC} ${CFLAGS} ${INCLUDES} -c $< ${LIBS}

mem_pool.o: mem_pool.c mem_pool.h
	echo mem_pool
	${CC} ${CFLAGS} ${INCLUDES} -c $<

clean:
	-rm -rf output

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<
