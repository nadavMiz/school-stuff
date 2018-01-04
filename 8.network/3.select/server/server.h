#ifndef SERVER_H
#define SERVER_H

#define REFUSE_MSG 0
#define ACCEPT_MSG 1

#include "doubleLinkedList.h" /* ListItr */

typedef struct Server Server;

typedef ListItr ClientId;

/*
 * @brief: template to a user function to run on each incoming stream of data to server
 * @param[in] _data: incoming stream of data
 * @param[in] _size: size of data in bytes
 * @param[in] _client: id of the sending client
**/
typedef void(*ServerFunc)(void* _data, size_t _size, int _client);

/*
 * 
**/
typedef void(*InitFunc)(int _client);

/*
 * @brief: creats a new Server
 * @param[in] port: port for the server to run on
 * @param[in] ServerFunc: function that the server will run on each incomming message
 * @return: Server* on success. NULL on failure
**/
Server* CreateServer(unsigned int port, ServerFunc _runFunc, InitFunc _initFunc );

/*
 * @brief destroys a Server object
 * @param[in] _server: server to destroy
**/
void DestroyServer(Server* _server);

/*
 *
**/
int ServerSend(ClientId _clientId, const void *buf, size_t len, int flags);

/*
 *
**/
int ServerRecive(ClientId _clientId, void *buf, size_t len, int flags);

/*
 * @brief run the server routine
 * @param[in] _server: server to start
 * @return: 1 if exited successfuly. 0 if a problem has accured
 *
 * @warning: once the server has started the only way to stop safely it is by signaling it SIGUSR1 signal
**/
int ServerServe(Server* _server);

#endif /* SERVER_H */

