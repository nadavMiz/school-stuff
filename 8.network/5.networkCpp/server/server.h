#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <tr1/memory>

#include "serverSocket.h"
#include "serversClient.h"
#include "listenSocket.h"
#include "selectSet.h"


typedef std::tr1::shared_ptr<netcpp::ServerSocket> SocketPtr;
typedef std::tr1::shared_ptr<netcpp::ServersClient> ClientPtr;

typedef void(*RunFunction)(void* _data, size_t _size, ClientPtr _client); 

namespace netcpp
{

class Server
{

public:
	Server(int _port, RunFunction _runFunc, const TimeValue& _timeOut, std::size_t _backlogSize = 32);
	//~Server(); default DTOR
	
	void ServerRoutine();

private:
	void LoadNewClients();
	void RemoveClient(std::list<ClientPtr>::iterator _clientItr);
	void AddClient(SocketPtr _socket);
	void HandleAllClients(unsigned int _numActiveSockets);
	void HanleSingleClient(std::list<ClientPtr>::iterator _clientItr);
	void HandleClientMsgError(std::list<ClientPtr>::iterator _clientItr);
	void ClientRoutine(void* _msg, std::size_t _msgSize, std::list<ClientPtr>::iterator _clientItr);
	unsigned int WaitForActivity();
	void UpdateNextTime();
	void UpdateClientTimeOut(std::list<ClientPtr>::iterator _clientItr);
	TimeValue GetNextTimeToWait();
	void RemoveAllInactiveClients();

	Server(const Server&); //uncopyable
	Server& operator=(const Server); //uncopyable

private:
	/* data */
	std::list<ClientPtr> m_clients;
	ListenSocket m_masterSocket;
	RunFunction m_RunFunc;
	std::size_t m_backlogSize;
	SelectSet m_selectSet;
	TimeValue m_timeOut;
	TimeValue m_nextTime;
	
};

}
#endif /* SERVER_H */

