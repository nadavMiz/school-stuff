#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "commSocket.h"

namespace netcpp
{

class ServerSocket: public CommSocket
{

friend class ListenSocket;

public:
	//virtual ~ServerSocket(); default DTOR
	
	// void Disconnect();
	// int Send(void* _data, std::size_t _size, MsgFlag _flags = e_noFlag);
	// int Recv(void* _data, std::size_t _size, MsgFlag _flags = e_noFlag);

protected:
	/* data */
	//Socket_t m_socket;
	
private:
	ServerSocket(Socket_t _socket);
	
	ServerSocket(const ServerSocket& _socket); //uncopyable
	ServerSocket& operator=(const ServerSocket& _socket); //uncopyable
};

inline ServerSocket::ServerSocket(Socket_t _socket)
{
	m_socket.SetSocket(_socket);
}

}
#endif /* SERVER_SOCKET_H */

