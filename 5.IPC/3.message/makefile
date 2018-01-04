CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99

all: ping.out pong.out ping2.out pong2.out

ping.out: ping.c message.c
	$(CC) $(CFLAGS) -o ping.out ping.c message.c

pong.out: pong.c message.c
	$(CC) $(CFLAGS) -o pong.out pong.c message.c
	
ping2.out: ping2.c message.c
	$(CC) $(CFLAGS) -o ping2.out ping2.c message.c

pong2.out: pong2.c message.c
	$(CC) $(CFLAGS) -o pong2.out pong2.c message.c
	
clean:
	rm pong.out
	rm ping.out
	rm ping2.out
	rm pong2.out
