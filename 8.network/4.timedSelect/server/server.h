#ifndef SERVER_H
#define SERVER_H

#include <sys/time.h> /* timeval */

typedef struct Server Server;

typedef struct Client Client;

/*
 * @brief: template to a user function to run on each incoming stream of data to server
 * @param[in] _data: incoming stream of data
 * @param[in] _size: size of data in bytes
 * @param[in] _client: id of the sending client
**/
typedef void(*ServerFunc)(void* _data, size_t _size, Client* _client);

/*
 * 
**/
typedef void(*InitFunc)(Client* _client);

/*
 * @brief: creats a new Server
 * @param[in] port: port for the server to run on
 * @param[in] ServerFunc: function that the server will run on each incomming message
 * @return: Server* on success. NULL on failure
**/
Server* CreateServer(unsigned int port, ServerFunc _runFunc, InitFunc _initFunc, struct timeval* _timeOut );

/*
 * @brief destroys a Server object
 * @param[in] _server: server to destroy
**/
void DestroyServer(Server* _server);

/*
 * @brief: send message to the client.
 * works exactly like send, except for this changes:
 *     1) gets Client* as insted of int.
 *     2) closes the clients socket if he disconnected.
**/
int ServerSend(Client* _clientId, const void* buf, size_t len, int flags);

/*
 * @brief: recive message from the client.
 * works exactly like send, except for this changes:
 *     1) gets Client* as insted of int.
 *     2) closes the clients socket if he disconnected.
**/
int ServerRecive(Client* _clientId, void* buf, size_t len, int flags);

/*
 * @brief run the server routine
 * @param[in] _server: server to start
 * @return: 1 if exited successfuly. 0 if a problem has accured
 *
 * @warning: once the server has started the only way to stop safely it is by signaling it SIGUSR1 signal
**/
int ServerServe(Server* _server);


/*
* 
**/
int GetClientId(Client* _client);

#endif /* SERVER_H */

