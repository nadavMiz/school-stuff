#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */
#include <arpa/inet.h> /* inet_addr */

#define NUM_THREADS 200
#define PORT 5555
#define IP "192.168.0.46"

void* clientFunc(struct sockaddr_in* _serverAddr)
{
	char msg[7000] = "virus virus";
	int newSocket;
	
	while(1)
	{
		newSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(connect(newSocket,(struct sockaddr*)_serverAddr, sizeof(*_serverAddr)) < 0)
		{
			perror("connect");
		}
		send(newSocket, msg, 7000, MSG_NOSIGNAL);
		close(newSocket);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	int i;
	pthread_t threads[NUM_THREADS];
	struct sockaddr_in socketAddr;
	
	if(argc != 3)
	{
		fprintf(stderr, "invalid number of arguments\n");
		return 0;
	}
	
	socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons((unsigned int)atoi(argv[1]));
    socketAddr.sin_addr.s_addr = inet_addr(argv[2]);
	
	for(i = 0; i < NUM_THREADS; ++i)
	{
		if(pthread_create(threads + i, NULL, (void*(*)(void*))clientFunc, &socketAddr) < 0)
		{
			perror("thread join");
		}
	}
	
	for(i = 0; i < NUM_THREADS; ++i)
	{
		if(pthread_join(threads[i], NULL) < 0)
		{
			perror("thread join");
		}
	}
	sleep(1);
}


