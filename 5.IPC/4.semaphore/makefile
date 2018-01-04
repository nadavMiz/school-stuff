CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99

all: ping.out pong.out

ping.out: ping.c message.c message.h
	$(CC) $(CFLAGS) -o ping.out ping.c message.c -lpthread

pong.out: pong.c message.c message.h
	$(CC) $(CFLAGS) -o pong.out pong.c message.c -lpthread
	
clean:
	rm pong.out
	rm ping.out
