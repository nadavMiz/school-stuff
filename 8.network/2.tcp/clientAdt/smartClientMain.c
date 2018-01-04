#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi */
#include <string.h> /* strlen */
#include <sys/socket.h> /*send*/

#include "smartClient.h"

#define NUM_CLIENTS 1000
#define PROBABILITY_TO_RUN 60
#define NUM_ITERATIONS 30
#define MAX_MSG_SIZE 1024

void RunClient(int _socket)
{
	char msg[MAX_MSG_SIZE] = "client";
	if(send(_socket, msg, strlen(msg) + 1, 0) < 0)
    {
        perror("msg send failed");
        return;
    }
    if(recv(_socket, msg, MAX_MSG_SIZE, 0) < 0)
    {
        perror("msg recive failed");
        return;
    }
    printf("msg recived: %s\n", msg);
}

int main(int argc, char* argv[])
{
	unsigned int port;
	char* serverIp;
	SmartClient* client;
	
	if(argc < 3)
    {
    	fprintf(stderr, "main: invalid number of arguments\n");
    	return 0;
    }
    
    port = (unsigned int)atoi(argv[1]);
    serverIp = argv[2];
    
    client = CreateSmartClient(NUM_CLIENTS, PROBABILITY_TO_RUN, port, serverIp);
    
    SmartClientRoutine(client, RunClient, NUM_ITERATIONS);
    
    DestroySmartClient(client);
    
	return 1;
}
