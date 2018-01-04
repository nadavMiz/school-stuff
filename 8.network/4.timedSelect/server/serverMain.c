#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi */
#include <string.h> /* strlen */
#include <sys/socket.h> /*send*/
#include <sys/time.h> /* timeval */

#include "server.h"

void WelcomFunction(Client* _client)
{
	return;
}

void ServerFunction(char* _data, size_t _size, Client* _client)
{
	char* msg = "server";
	
	printf("msg recived from %d: %s\n", GetClientId(_client), _data);
	
	if(ServerSend(_client, msg, strlen(msg) + 1, MSG_NOSIGNAL) < 0)
    {
        perror("msg send failed");
        return;
    }
}

int main(int argc, char* argv[])
{
	Server* server;
	unsigned int port;
	struct timeval timeOut;
	timeOut.tv_sec = 1;
	timeOut.tv_usec = 0;
	
	if(argc != 2)
    {
    	fprintf(stderr, "main: invalid number of arguments\n");
    	return 0;
    }
    
    port = (unsigned int)atoi(argv[1]);
    
	server = CreateServer(port, (void(*)(void*, size_t, Client*))ServerFunction, WelcomFunction, &timeOut);
	
	ServerServe(server);
	
	DestroyServer(server);
    
	return 1;
}
