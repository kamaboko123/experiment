CC = gcc
CFLAGS = -m32 -g -Wall -O0 -fno-stack-protector
INCLUDE = -I./

all:
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDE) -c -o bin/stdlibc.o stdlibc.c
	$(CC) $(CFLAGS) $(INCLUDE )-o bin/test main.c bin/stdlibc.o

run: all
	bin/test

clean:
	rm -rf bin/

