#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi */
#include <string.h>
#include <sys/socket.h> /*send*/

#include "server.h"

void ServerFunction(char* _data, size_t _size, int _clientSocket)
{
	char* msg = "server";
	
	printf("msg recived from %d: %s\n", _clientSocket, _data);*/
	
	if(send(_clientSocket, msg, strlen(msg) + 1, MSG_NOSIGNAL) < 0)
    {
        perror("msg send failed");
        return;
    }
}

int main(int argc, char* argv[])
{
	Server* server;
	unsigned int port;
	
	if(argc != 2)
    {
    	fprintf(stderr, "main: invalid number of arguments\n");
    	return 0;
    }
    
    port = (unsigned int)atoi(argv[1]);
    
	server = CreateServer(port, (void(*)(void*, size_t, int))ServerFunction);
	
	ServerServe(server);
	
	DestroyServer(server);
    
	return 1;
}
