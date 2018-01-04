#include <stdlib.h> /* malloc, hton */
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */
#include <signal.h> /* signal */
#include <sys/select.h> /* select */
#include <sys/time.h> /* timeval */
#include <errno.h> /* errno */

#include "server.h"
#include "doubleLinkedList.h" /* List */

#define MIN_PORT 2000
#define MAX_PORT 65535
#define MAGIC_NUMBER 0XCB55555C
#define MSG_SIZE 1024
#define MAX_FDs MSG_SIZE + 1
#define BACKLOG_SIZE 100
#define MAX_CLIENTS 1000

struct Server
{
	int m_socketFd;		              	/* socket file descriptor to recive new clients */
	ServerFunc m_ServerFunc;			/* function that the server runs on the clients messages */
	InitFunc m_initFunc;				/* function that server runs on each new client */
	fd_set* m_readFDs;     				/* set of all socket fd to use with the select function */
	List* m_clients;				  	/* list of client socket FDs to recive and send messages */
	struct sockaddr_in* m_socketAdrr; 	/* socket address of the server */
	size_t m_numClients;				/* number of connected clients */
	struct timeval m_timeOut;			/* time that a socket may remain inactive before the server closes it */
	struct timeval m_nextTime;			/* time to wait untill next time out */
	size_t m_magicNum;                	/* magic number */
};

struct Client
{
	int m_socket;
	int m_isActive;
	struct timeval* m_timeOut;
};

/*---------------------------------------------------*/

static sig_atomic_t g_isRunning = 1;

static void ExitSignal(int _sig)
{
	g_isRunning = 0;
}



static void InitializeExitSignal()
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

/*-------------------------------------------------------------------*/

static void SetToNextTimeOut(struct timeval* _time, struct timeval* _timeOut)
{
	gettimeofday(_time, NULL);
	timeradd(_time, _timeOut, _time);
}

static Client* CreateClient(int _socket, struct timeval* _timeOut)
{
	Client* client = malloc(sizeof(Client));
	if(NULL == client)
	{
		return NULL;
	}
	
	client->m_timeOut = malloc(sizeof(struct timeval));
	if(NULL == client->m_timeOut)
	{
		free(client);
		return NULL;
	}
	
	SetToNextTimeOut(client->m_timeOut, _timeOut);
	
	client->m_socket = _socket;
	client->m_isActive = 1;

	
	return client;
} 

static int DestroyClient(Client* _client, void* _dummy)
{
	close(_client->m_socket);
	free(_client->m_timeOut);
	free(_client);
	
	return 1;
}

/*-----------------------------------------------------------------*/

static void UpdateClientTime(Server* _server, ListItr _clientItr)
{
	Client* client = (Client*)ListItr_Get(_clientItr);
	
	/* update clients time */
	SetToNextTimeOut(client->m_timeOut, &_server->m_timeOut);
	
	/* update position on list */
	ListItr_Remove(_clientItr);
	ListPushTail(_server->m_clients, client);
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


/*----------------------------------------------------------------*/

fd_set* CreateFDSet(int _serverSocket)
{
	fd_set* clients = malloc(sizeof(fd_set));
	if(0 == clients)
	{
		return NULL;
	}
	
	FD_ZERO(clients);
	
	FD_SET(_serverSocket, clients);
	
	return 	clients;
}

/*-----------------------------------------------------------------*/

Server* CreateServer(unsigned int port, ServerFunc _runFunc, InitFunc _initFunc, struct timeval* _timeOut)
{
	Server* newServer;
	
	/* check for invalid paramaters */	
	if(NULL == _runFunc || NULL == _initFunc)
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
		ListDestroy(&(newServer->m_clients), (int(*)(void*,void*))DestroyClient);
		free(newServer);
		return NULL;
	}
	
	newServer->m_socketFd = CreateSocketFD(newServer->m_socketAdrr);
	if(0 == newServer->m_socketFd)
	{
		DestroySocketAddr(newServer->m_socketAdrr);
		ListDestroy(&newServer->m_clients, (int(*)(void*,void*))DestroyClient);
		free(newServer);
		return NULL;
	}
	
	newServer->m_readFDs = CreateFDSet(newServer->m_socketFd);
	if(NULL == newServer->m_readFDs)
	{
		close(newServer->m_socketFd);
		DestroySocketAddr(newServer->m_socketAdrr);
		ListDestroy(&newServer->m_clients, (int(*)(void*,void*))DestroyClient);
		free(newServer);
		return NULL;
	}

	newServer->m_timeOut = *_timeOut;
	newServer->m_ServerFunc = _runFunc;
	newServer->m_initFunc = _initFunc;
	newServer->m_numClients = 0;
	newServer->m_magicNum = MAGIC_NUMBER;
	
	InitializeExitSignal();
	
	return newServer;
}

/*------------------------------------------------------------------------------*/

void DestroyServer(Server* _server)
{
	_server->m_magicNum = 0;
	free(_server->m_readFDs);
	close(_server->m_socketFd);
	DestroySocketAddr(_server->m_socketAdrr);
	ListDestroy(&_server->m_clients, (int(*)(void*,void*))DestroyClient);
	free(_server);
}

/*-------------------------------------------------------------------------------*/

int GetClientId(Client* _client)
{
	return _client->m_socket;
}

/*-------------------------------------------------------------------------------*/

int ServerSend(Client* _client, const void *buf, size_t len, int flags)
{
	int result;
	Client* client = (Client*)_client;
	
	result = send(client->m_socket, buf, len, flags | MSG_NOSIGNAL);
	if(result < 0 && EPIPE == errno)
	{
		close(client->m_socket);
		client->m_isActive = 0;
	}
	
	return result;
}

int ServerRecive(Client* _client, void *buf, size_t len, int flags)
{
	int result;
	Client* client = (Client*)_client;
	
	result = recv(client->m_socket, buf, len, flags | MSG_NOSIGNAL);
	if(0 == result)
	{
		close(client->m_socket);
		client->m_isActive = 0;
	}
	
	return result;
}

/*-------------------------------------------------------------------------------*/

static Client* EnterNewClient(Server* _server, int clientFD)
{
	Client* clientPtr = CreateClient(clientFD, &_server->m_timeOut);
	if(NULL == clientPtr)
	{
		close(clientFD);
		return NULL;
	}
	
	if(ListPushTail(_server->m_clients, clientPtr) != LIST_OK)
	{
		close(clientFD);
		DestroyClient(clientPtr, NULL);
		return NULL;
	}
	
	FD_SET(clientFD, _server->m_readFDs);
	++_server->m_numClients;
	
	return clientPtr;
}

static void RemoveClient(Server* _server, ListItr _itr)
{
	Client* client = ListItr_Remove(_itr);
	FD_CLR(client->m_socket, _server->m_readFDs);
	DestroyClient(client, NULL);
	--_server->m_numClients;
}

/*-------------------------------------------------------------------------------*/

static int AcceptErrorHandler(int* _clientsToRead)
{
	/* if the queue is empty */
	if(EAGAIN == errno || EWOULDBLOCK == errno)
	{
		*_clientsToRead = 0;
		return 1;
	}
	/* if a problem has accured */
	else
	{
		perror("ERROR on accept");
		return 0;
	}
}

static int LoadNewClients(Server* _server)
{
	int clientSockFd;
	int clientsToAccept = BACKLOG_SIZE;
	Client* currentClient;
	
	while(0 < clientsToAccept)
	{
		clientSockFd = accept(_server->m_socketFd, 0, 0);
		/* accept incontered an error */
		if(clientSockFd < 0)
		{
			if(0 == AcceptErrorHandler(&clientsToAccept))
			{
				return 0;
			}
		}
		/* server is full */
		else if(_server->m_numClients == MAX_CLIENTS)
		{
			close(clientSockFd);
		}
		/* client was accepted successfully*/
		else
		{
			currentClient = EnterNewClient(_server, clientSockFd);
			if(NULL != currentClient)
			{
				_server->m_initFunc(currentClient);
			}
		}
	}
	
	return 1;
}

/*--------------------------------------------------------*/

static void HandleClientMsgError(Server* _server, ListItr _clientItr)
{
	/* if a problem has accured */
	if(!(EAGAIN == errno || EWOULDBLOCK == errno))
	{
		perror("ERROR on accept");
		RemoveClient(_server, _clientItr);
	}
}

static void ClientRoutine(Server* _server, ListItr _clientItr, char* _msg, size_t _count)
{
	Client* client = (Client*)ListItr_Get(_clientItr);
	
	_server->m_ServerFunc(_msg, _count, client);
	if(client->m_isActive)
	{
		UpdateClientTime(_server, _clientItr);
	}
	else
	{
		RemoveClient(_server, _clientItr);
	}
}

static void HandleSingleClient(Server* _server, ListItr _clientItr)
{
	Client* client;
	char msg[MSG_SIZE];
	ssize_t count;

	client = (Client*)ListItr_Get(_clientItr);
	count = recv(client->m_socket, msg, MSG_SIZE, MSG_DONTWAIT);
	
	/* client has disconnected */
	if(0 == count)
	{
		RemoveClient(_server, _clientItr);
	}
	/*error has accured*/
	else if(count < 0)
	{
		HandleClientMsgError(_server, _clientItr);
	}
	/* msg was recived successfully */
    else
    {
    	ClientRoutine(_server, _clientItr, msg, (size_t)count);
    }
}

/*---------------------------------------------------------*/

static int HandleAllClientsMessages(Server* _server, fd_set* _activeSockets, int _NumActiveSockets)
{
	Client* client;
	ListItr clientItr, nextItr;
	
	for(clientItr = ListItr_Begin(_server->m_clients); 0 < _NumActiveSockets;
		clientItr = nextItr)
	{
		nextItr = ListItr_Next(clientItr);
		
		client = (Client*)ListItr_Get(clientItr);
		
		/* client has issued a call to the server */
		if(FD_ISSET(client->m_socket, _activeSockets))
		{
			HandleSingleClient(_server, clientItr);
			--_NumActiveSockets;
		}
	}
	
	return 1;
}

/*----------------------------------------------------------*/

static struct timeval* AbsTime(struct timeval* _time)
{
	if((_time->tv_sec < 0) || (_time->tv_usec < 0))
	{
		_time->tv_sec = 0;
		_time->tv_usec = 0;
	}
	
	return _time;
}

static struct timeval* GetNextTime(Server* _server)
{
	struct timeval currentTime;
	
	Client* nextClient = (Client*)ListItr_Get(ListItr_Begin(_server->m_clients));
	
	if(NULL == nextClient)
	{
		return NULL;
	}
	
	gettimeofday(&currentTime, NULL);
	
	timersub(nextClient->m_timeOut, &currentTime, &_server->m_nextTime);
	
	AbsTime(&_server->m_nextTime);
	
	return &_server->m_nextTime;
}

static void RemoveTimedOutClients(Server* _server)
{
	struct timeval currentTime;
	ListItr clientItr = ListItr_Begin(_server->m_clients);
	Client* currentClient;
	
	gettimeofday(&currentTime, NULL);
	
	while(!ListIsEmpty(_server->m_clients))
	{
		
		clientItr = ListItr_Begin(_server->m_clients);
		currentClient = ((Client*)ListItr_Get(clientItr));
		
		if(timercmp(currentClient->m_timeOut, &currentTime, <=))
		{
			printf("client %d was removed\n", currentClient->m_socket);
			RemoveClient(_server, clientItr);
		}
		else
		{
			break;
		}
	}
}

/*----------------------------------------------------------*/

int ServerServe(Server* _server)
{	
	int NumActiveSockets = 0;
	fd_set socketsMask;
	
	if(MAGIC_NUMBER != _server->m_magicNum)
	{
		return 0;
	}
	
	g_isRunning = 1;
	
    while(g_isRunning)
    {
    	socketsMask = *_server->m_readFDs;
    	
    	NumActiveSockets = select(MAX_FDs + 1, &socketsMask, NULL, NULL, GetNextTime(_server));
    	
    	/* client has timed out */
    	if(0 == NumActiveSockets)
    	{
    		RemoveTimedOutClients(_server);
    		continue;
    	}
    	/* new clients trying to connect */
    	if(FD_ISSET(_server->m_socketFd, &socketsMask))
    	{
    		LoadNewClients(_server);
    		--NumActiveSockets;
    	}
    	
    	HandleAllClientsMessages(_server, &socketsMask, NumActiveSockets);
    }
    
    return 1;
}
