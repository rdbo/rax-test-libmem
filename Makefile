CFLAGS=-g

all:
	$(CC) -o main $(CFLAGS) -Wall -Wextra -std=c89 -ansi -pedantic main.c libmem/libmem.c -ldl
	$(CC) -o target $(CFLAGS) target.c
