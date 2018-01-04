#ifndef SMART_CLIENT_H
#define SMART_CLIENT_H

#include <stddef.h> /* size_t */

typedef struct SmartClient SmartClient;

typedef struct Client Client;

typedef void(*ClientFunc)(Client* clientId);

/*----------------------------------------------------*/

SmartClient* CreateSmartClient(size_t _NumClients, int _prob, unsigned int _serverPort, const char* _serverIP);

int ClientSend(Client* _client, const void *buf, size_t len, int flags);

int ClientRecive(Client* clientId, void *buf, size_t len, int flags);

void DestroySmartClient(SmartClient* _client);

void SmartClientRoutine(SmartClient* _client, ClientFunc _func, size_t _numIterations);

#endif /* SMART_CLIENT_H */

