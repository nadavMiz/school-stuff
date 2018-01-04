CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99

all: fifo.out pipes.out

fifo.out: fifo.c
	$(CC) $(CFLAGS) -o fifo.out fifo.c

pipes.out: pipes.c
	$(CC) $(CFLAGS) -o pipes.out pipes.c
	
clean:
	rm fifo.out
	rm pipes.out
