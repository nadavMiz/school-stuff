#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "commSocket.h"

namespace netcpp
{

class ClientSocket: public CommSocket
{
public:
	ClientSocket(const char* _ip, int _port);
	//virtual ~ClientSocket(); default DTOR

	// void Disconnect();
	// int Send(void* _data, std::size_t _size, MsgFlag _flags = e_noFlag);
	// int Recv(void* _data, std::size_t _size, MsgFlag _flags = e_noFlag);

private:
	void Connect(const char* _ip, int _port);
	void InitAddress(const char* _ip, int _port, struct sockaddr_in& _adrr);
	void ConnectSocket(struct sockaddr_in& _adrr);

	ClientSocket(const ClientSocket& _client); //uncopyable
	ClientSocket& operator=(const ClientSocket& _client); //uncopyable

private:
	/* data */
	//Socket_t m_socket;
		
	
};


inline ClientSocket::ClientSocket(const char* _adrr, int _port)
{
	Connect(_adrr, _port);
}

}
#endif /* CLIENT_SOCKET_H */

