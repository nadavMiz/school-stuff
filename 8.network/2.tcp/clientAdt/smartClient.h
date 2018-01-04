#ifndef SMART_CLIENT_H
#define SMART_CLIENT_H

#include <stddef.h> /* size_t */

typedef struct SmartClient SmartClient;

typedef void(*ClientFunc)(int clientSocket);

/*----------------------------------------------------*/

SmartClient* CreateSmartClient(size_t _NumClients, int _prob, unsigned int _serverPort, const char* _serverIP);

void DestroySmartClient(SmartClient* _client);

void SmartClientRoutine(SmartClient* _client, ClientFunc _func, size_t _numIterations);

#endif /* SMART_CLIENT_H */

