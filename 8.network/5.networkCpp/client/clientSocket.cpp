#include <arpa/inet.h> /* inet_addr */
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <cstring> /* memset */
#include <stdexcept> /* exceptions */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */

#include "clientSocket.h"

namespace netcpp
{

void ClientSocket::InitAddress(const char* _ip, int _port, struct sockaddr_in& _adrr)
{
	memset(&_adrr, 0, sizeof(_adrr));
	_adrr.sin_family = AF_INET;
    _adrr.sin_port = htons(_port);
    _adrr.sin_addr.s_addr = inet_addr(_ip);
}

void ClientSocket::ConnectSocket(struct sockaddr_in& _adrr)
{
	int newSocket;
	
	newSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(newSocket < 0)
	{
		perror("socket creation failed");
		throw std::runtime_error("socket creation failed");
	}
	
	if(connect(newSocket,(struct sockaddr*)&_adrr, sizeof(_adrr)) < 0)
    {
    	perror("connect failed");
    	close(newSocket);
    	throw std::runtime_error("socket creation failed");
    }
    
    m_socket.SetSocket(newSocket);
}

void ClientSocket::Connect(const char* _ip, int _port)
{
	struct sockaddr_in adrress;
	InitAddress(_ip, _port, adrress);
	
	ConnectSocket(adrress);
}

}
