#include <stdlib.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */
#include <arpa/inet.h> /* inet_addr */
#include <signal.h> /* signal */
#include <errno.h>

#include "smartClient.h"
#include "doubleLinkedList.h" /* List */

#define MIN_PORT 2000
#define MAX_PORT 65535
#define MAGIC_NUMBER 0XCB55555D

struct SmartClient
{
	List* m_clients; 					/* list of client sockets */
	struct sockaddr_in* m_socketAdrr; 	/* socket address of the server */
	int m_probabilityToRun;             /* probability to call m_ClientFunc with a certain client socket */
	size_t m_magicNum;                	/* magic number */
};

struct Client
{
	int m_isSocketOpen;
	int m_socket;
	struct sockaddr_in* m_socketAdrr;
};

/* for SmartClientRoutine */
typedef struct
{
	ClientFunc m_clientFunction;
	int m_probability;
} RunFunctionContext; 


/*-------------------------------------------------------------------------------------------*/

static struct sockaddr_in* CreateSocketAddr(unsigned int _port, const char* _ip)
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
    newAddress->sin_addr.s_addr = inet_addr(_ip);
    
    return newAddress;
}

static void DestroyClientAddr(struct sockaddr_in* _addr)
{
	free(_addr);
}

/*---------------------------------------------------------------------------------------------*/

static int CreateSocket(struct sockaddr_in* _serverAddr)
{
	int newSocket;
	
	newSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(newSocket < 0)
	{
		perror("socket creation failed");
		return 0;
	}
	
	if(connect(newSocket,(struct sockaddr*)_serverAddr, sizeof(*_serverAddr)) < 0)
    {
    	perror("connect failed");
    	close(newSocket);
    	return 0;
    }
	
	return newSocket;
}

Client* CreateClient(struct sockaddr_in* _serverAddr)
{
	Client* newClient = malloc(sizeof(Client));
	if(NULL == newClient)
	{
		return NULL;
	}
	newClient->m_socketAdrr = _serverAddr;
	newClient->m_isSocketOpen = 0;
	newClient->m_socket = 0;
	
	return newClient;
}

int DestroyClient(Client* _client, void* _dummy)
{
	if(_client->m_isSocketOpen)
	{
		close(_client->m_socket);
	}
	free(_client);
	
	return 1;
}

/*---------------------------------------------------------------------------------------------*/

size_t CreateClients(List* _listToFill, struct sockaddr_in* _socketAdrr, size_t _NumClients)
{
	size_t i;
	Client* clientPtr;
	for(i = 0; i < _NumClients; ++i)
	{
		clientPtr = CreateClient(_socketAdrr);
		if(NULL == clientPtr)
		{
			break;
		}
		ListPushTail(_listToFill, clientPtr);
	}
	
	return i;
}

/*---------------------------------------------------------------------------------------------*/

SmartClient* CreateSmartClient(size_t _NumClients, int _prob, unsigned int _serverPort, const char* _serverIP)
{
	SmartClient* newSmartClient;
	
	if(100 < _prob || 0 > _prob)
	{
		return NULL;
	}
	
	newSmartClient = malloc(sizeof(SmartClient));
	if(NULL == newSmartClient)
	{
		return NULL;
	}
	
	
	newSmartClient->m_socketAdrr = CreateSocketAddr(_serverPort, _serverIP);
	if(NULL == newSmartClient->m_socketAdrr)
	{
		free(newSmartClient);
		return NULL;
	}
	
	newSmartClient->m_clients = ListCreate();
	if(NULL == newSmartClient->m_clients)
	{
		DestroyClientAddr(newSmartClient->m_socketAdrr);
		free(newSmartClient);
		return NULL;
	}
	CreateClients(newSmartClient->m_clients, newSmartClient->m_socketAdrr, _NumClients);
	
	newSmartClient->m_probabilityToRun = _prob;
	newSmartClient->m_magicNum = MAGIC_NUMBER;
	
	return newSmartClient;
}

/*------------------------------------------------------------------------------------------------*/

void DestroySmartClient(SmartClient* _client)
{
	ListDestroy(&_client->m_clients, (UserActionFunc)DestroyClient);
	DestroyClientAddr(_client->m_socketAdrr);
	free(_client);
}

/*-------------------------------------------------------------------------------------------------*/

void CloseClientsSocket(Client* _client)
{
	close(_client->m_socket);
	_client->m_isSocketOpen = 0;
}

/*-------------------------------------------------------------------------------------------------*/

int ClientSend(Client* _client, const void *buf, size_t len, int flags)
{
	int result;
	
	result = send(_client->m_socket, buf, len, flags | MSG_NOSIGNAL);
	if(result < 0 && EPIPE == errno)
	{
		CloseClientsSocket(_client);
	}
	
	return result;
}

/*-------------------------------------------------------------------------------------------------*/

int ClientRecive(Client* _client, void *buf, size_t len, int flags)
{
	int result;
	
	result = recv(_client->m_socket, buf, len, flags);
	if(0 == result)
	{
		CloseClientsSocket(_client);
	}
	
	return result;
}

/*-------------------------------------------------------------------------------------------------*/

static int ClientRunFunction(Client* _client, RunFunctionContext* _context)
{
	if((rand()%100) < _context->m_probability)
	{
		if(_client->m_isSocketOpen)
		{
			_context->m_clientFunction(_client);
		}
		else
		{
			_client->m_socket = CreateSocket(_client->m_socketAdrr);
			if(_client->m_socket != 0)
			{
				_client->m_isSocketOpen = 1;
			}
		}
	}
	else if(_client->m_isSocketOpen)
	{
		close(_client->m_socket);
		_client->m_isSocketOpen = 0;
	}
	
	return 1;
}

void SmartClientRoutine(SmartClient* _client, ClientFunc _func, size_t _numIterations)
{
	size_t i;
	RunFunctionContext context;
	
	context.m_probability = _client->m_probabilityToRun;
	context.m_clientFunction = _func;
	
	for(i = 0; i < _numIterations; ++i)
	{
		ListForEach(_client->m_clients, (UserActionFunc)ClientRunFunction, &context);
	}
}

