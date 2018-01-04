#ifndef SERVER_H
#define SERVER_H

typedef struct Server Server;

typedef void(*ServerFunc)(void* _data, size_t _size, int clientSocket);

Server* CreateServer(unsigned int port, ServerFunc _func);

void DestroyServer(Server* _server);

int ServerServe(Server* _server);

#endif /* SERVER_H */

