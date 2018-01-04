#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi */
#include <string.h> /* strlen */
#include <unistd.h> /* sleep */
#include <sys/socket.h> /*send*/

#include "smartClient.h"

#define NUM_CLIENTS 500
#define PROBABILITY_TO_RUN 70
#define NUM_ITERATIONS 100
#define MAX_MSG_SIZE 1024

void RunClient(Client* _client)
{
	char msg[MAX_MSG_SIZE] = "client";
	if(ClientSend(_client, msg, strlen(msg) + 1, 0) < 0)
    {
        perror("msg send failed");
        return;
    }
    if(ClientRecive(_client, msg, MAX_MSG_SIZE, 0) <= 0)
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
