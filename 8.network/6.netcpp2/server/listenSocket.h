#ifndef LISTEN_SOCKET_H
#define LISTEN_SOCKET_H

#include <tr1/memory>

#include "socket.h"
#include "serverSocket.h"

namespace netcpp
{

const std::size_t DEFAULT_BACKLOG_SIZE = 1000;

class ListenSocket: public Socket
{
public:

	ListenSocket(int _port, std::size_t _backlogSize = DEFAULT_BACKLOG_SIZE);
	virtual ~ListenSocket();
	
	void SetNoBlock();
	std::tr1::shared_ptr<ServerSocket> Accept();
	void CloseSocket();
	//socket_t GetNativeHandler();
	
private:
	void Listen(int _port, std::size_t _backlogSize);
	void InitAddress(int _port, struct sockaddr_in& _adrr);
	void ConnectSocket(struct sockaddr_in& _adrr, std::size_t _backlogSize);

protected:
	//Socket_t m_socket;

private:
	/* data */
	bool m_isClosed;	
};

}

#endif /* LISTEN_SOCKET_H */

