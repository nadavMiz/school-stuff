#include <stdlib.h> /* malloc */
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <unistd.h> /* close */
#include <stdlib.h> /* htons */
#include <stdio.h> /* perror */
#include <signal.h> /* signal */
#include <errno.h>

#include "server.h"
#include "doubleLinkedList.h" /* List */

#define MIN_PORT 2000
#define MAX_PORT 65535
#define MAGIC_NUMBER 0XCB55555C
#define MSG_SIZE 1024
#define BACKLOG_SIZE 100
#define MAX_CLIENTS 1000

struct Server
{
	int m_socketFd;		              	/* socket file descriptor to recive new clients */
	ServerFunc m_ServerFunc;			/* function that the server runs on the clients messages */
	List* m_clients;				  	/* list of client socket FDs to recive and send messages */
	struct sockaddr_in* m_socketAdrr; 	/* socket address of the server */
	size_t m_numClients;				/* number of connexted clients */
	size_t m_magicNum;                	/* magic number */
};


/*--------------------------------*/
sig_atomic_t g_isRunning = 1;

void ExitSignal(int _sig)
{
	g_isRunning = 0;
}

/*-------------------------------*/

void InitializeExitSignal()
{
	struct sigaction sa;
	sa.sa_handler = ExitSignal;
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(1);
    }
}

/*---------------------------------------------------------------*/

static struct sockaddr_in* CreateSocketAddr(unsigned int _port)
{
	struct sockaddr_in* newAddress;
	
	/* check for invalid paramaters */
	if(MIN_PORT > _port || MAX_PORT < _port)
	{
		return NULL;
	}
	
	newAddress = calloc(1, sizeof(struct sockaddr_in));
	if(NULL == newAddress)
	{
		return NULL;
	}
	
	newAddress->sin_family = AF_INET;
    newAddress->sin_port = htons(_port);
    newAddress->sin_addr.s_addr = INADDR_ANY;
    
    return newAddress;
}

static void DestroySocketAddr(struct sockaddr_in* _addr)
{
	free(_addr);
}

int DestroySocket(int* _socket, void* _dummy)
{
	close(*_socket);
	free(_socket);
	
	return 1;
}

/*-----------------------------------------------------------------*/

int CreateSocketFD(struct sockaddr_in* _socketAdrr)
{
	int socketFd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
    unsigned int adrrLength = sizeof(struct sockaddr_in);
    if(socketFd < 0)
    {
        perror("socket creation failed");
        return -1;
    }
    if(bind(socketFd, (struct sockaddr *)_socketAdrr, adrrLength) < 0)
    {
        perror("bind failed");
        close(socketFd);
        return -1;
    }
    if(listen(socketFd, BACKLOG_SIZE) < 0)
    {
    	perror("listen failed");
    	close(socketFd);
        return -1;
    }
    
    return socketFd;
}

/*-----------------------------------------------------------------*/

Server* CreateServer(unsigned int port, ServerFunc _func)
{
	Server* newServer;
	
	/* check for invalid paramaters */	
	if(NULL == _func)
	{
		return NULL;
	}
	
	newServer = malloc(sizeof(Server));
	if(0 == newServer)
	{
		return NULL;
	}
	
	newServer->m_clients = ListCreate();
	if(NULL == newServer->m_clients)
	{
		free(newServer);
		return NULL;
	}
	
	newServer->m_socketAdrr = CreateSocketAddr(port);
	if(NULL == newServer->m_socketAdrr)
	{
		ListDestroy(&(newServer->m_clients), (int(*)(void*,void*))DestroySocket);
		free(newServer);
		return NULL;
	}
	
	newServer->m_socketFd = CreateSocketFD(newServer->m_socketAdrr);
	if(0 == newServer->m_socketFd)
	{
		DestroySocketAddr(newServer->m_socketAdrr);
		ListDestroy(&newServer->m_clients, (int(*)(void*,void*))DestroySocket);
		free(newServer);
		return NULL;
	}

	newServer->m_ServerFunc = _func;
	newServer->m_magicNum = MAGIC_NUMBER;
	newServer->m_numClients = 0;
	
	InitializeExitSignal();
	
	return newServer;
}

/*------------------------------------------------------------------------------*/

void DestroyServer(Server* _server)
{
	_server->m_magicNum = 0;
	close(_server->m_socketFd);
	DestroySocketAddr(_server->m_socketAdrr);
	ListDestroy(&_server->m_clients, (int(*)(void*,void*))DestroySocket);
	free(_server);
}

/*-------------------------------------------------------------------------------*/

static int AcceptErrorHandler(int* _isQueueEmpty)
{
	/* if the queue is empty */
	if(EAGAIN == errno || EWOULDBLOCK == errno)
	{
		*_isQueueEmpty = 1;
		return 1;
	}
	/* if a problem has accured */
	else
	{
		perror("ERROR on accept");
		return 0;
	}
}

static int EnterNewClient(Server* _server, int clientFD)
{
	int* ClientPtr = malloc(sizeof(int));
	if(0 == ClientPtr)
	{
		return 0;
	}
	*ClientPtr = clientFD;
	
	ListPushTail(_server->m_clients, ClientPtr);
	return 1;
}

static int LoadNewClients(Server* _server)
{
	int clientSockFd;
	int isQueueEmpty = 0;
	
	while(!isQueueEmpty)
	{
		clientSockFd = accept(_server->m_socketFd, 0, 0);
		if(clientSockFd < 0)
		{
			if(0 == AcceptErrorHandler(&isQueueEmpty))
			{
				return 0;
			}
		}
		else if(_server->m_numClients == MAX_CLIENTS)
		{
			printf("closed\n");
			close(clientSockFd);
		}
		else
		{
			EnterNewClient(_server, clientSockFd);
			++_server->m_numClients;
		}
	}
	
	return 1;
}

/*--------------------------------------------------------*/

void RemoveListNode(Server* _server, ListItr _itr)
{
	int* clientSocketPtr = ListItr_Remove(_itr);
	DestroySocket(clientSocketPtr, NULL);
	--_server->m_numClients;
}

/*--------------------------------------------------------*/

static void HandleClientMsgError(Server* _server, ListItr _clientItr)
{
	/* if a problem has accured */
	if(!(EAGAIN == errno || EWOULDBLOCK == errno))
	{
		perror("ERROR on accept");
		RemoveListNode(_server, _clientItr);
	}
}

static int HandleAllClientsMessages(Server* _server)
{
	ListItr clientItr, listEnd;
	int clientSocket;
	char msg[MSG_SIZE];
	ssize_t count;
	
	listEnd = ListItr_End(_server->m_clients);
	for(clientItr = ListItr_Begin(_server->m_clients); !ListItr_Equals(clientItr, listEnd); clientItr = ListItr_Next(clientItr))
	{
		clientSocket = *((int*)ListItr_Get(clientItr));
		count = recv(clientSocket, msg, MSG_SIZE, MSG_DONTWAIT);
		
		/* client has disconnected */
		if(0 == count)
		{
			RemoveListNode(_server, clientItr);
		}
		/*error has accured*/
		else if(count < 0)
		{
			HandleClientMsgError(_server, clientItr);
		}
		/* msg was recived successfully */
	    else
	    {
	    	_server->m_ServerFunc(msg, (size_t)count, clientSocket);
	    }
	}
	
	return 1;
}

/*----------------------------------------------------------*/

int ServerServe(Server* _server)
{	
	if(MAGIC_NUMBER != _server->m_magicNum)
	{
		return 0;
	}
	
    while(g_isRunning)
    {
    	LoadNewClients(_server);
    	
    	HandleAllClientsMessages(_server);
    }
    
    return 1;
}
