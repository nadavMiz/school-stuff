CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99

all: signal1.out signal2.out

signal1.out: signal1.c
	$(CC) $(CFLAGS) -o signal1.out signal1.c

signal2.out: signal2.c
	$(CC) $(CFLAGS) -o signal2.out signal2.c
	
clean:
	rm signal1.out
	rm signal2.out
