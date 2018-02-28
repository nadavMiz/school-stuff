#include <cstring>
#include <stdlib.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */
#include <arpa/inet.h> /* inet_addr */
#include <signal.h> /* signal */
#include <stdexcept> /* exceptions */
#include <fcntl.h> /* fcntl */
#include <errno.h>

#include "listenSocket.h"

namespace netcpp
{

ListenSocket::ListenSocket(int _port, std::size_t _backlogSize)
{
	Listen(_port, _backlogSize);
}

ListenSocket::~ListenSocket()
{
	if(!m_isClosed)
	{
		close(m_socket);
	}
}

void ListenSocket::CloseSocket()
{
	if(!m_isClosed)
	{
		if(close(m_socket) < 0)
		{
			throw std::runtime_error(strerror(errno));
		}
	}
}

void ListenSocket::InitAddress(int _port, struct sockaddr_in& _adrr)
{
	memset(&_adrr, 0, sizeof(_adrr));
	_adrr.sin_family = AF_INET;
    _adrr.sin_port = htons(_port);
    _adrr.sin_addr.s_addr = INADDR_ANY;
}

void ListenSocket::ConnectSocket(struct sockaddr_in& _adrr, std::size_t _backlogSize )
{
	int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    unsigned int adrrLength = sizeof(struct sockaddr_in);
    if(socketFd < 0)
    {
        perror("socket creation failed");
        throw std::runtime_error("socket creation failed");
    }
    if(bind(socketFd, (struct sockaddr*)&_adrr, adrrLength) < 0)
    {
        perror("bind failed");
        close(socketFd);
        throw std::runtime_error("socket creation failed");
    }
    if(listen(socketFd, _backlogSize) < 0)
    {
    	perror("listen failed");
    	close(socketFd);
        throw std::runtime_error("socket creation failed");
    }
    
    m_socket.SetSocket(socketFd);
}

void ListenSocket::Listen(int _port, std::size_t _backlogSize)
{
	struct sockaddr_in adrress;
	InitAddress(_port, adrress);
	
	ConnectSocket(adrress, _backlogSize);
}
	

void ListenSocket::SetNoBlock()
{
   int flags;
   if(-1 ==(flags = fcntl(m_socket, F_GETFL)))
   {
       throw std::runtime_error(strerror(errno));
   }
   
   if(-1 == fcntl(m_socket, F_SETFL, flags | O_NONBLOCK))
   {
       throw std::runtime_error(strerror(errno));
   }
}

std::tr1::shared_ptr<ServerSocket> ListenSocket::Accept()
{
	int newSocket = accept(m_socket, 0, 0);

	if(newSocket < 0)
	{
		if(EAGAIN == errno || EWOULDBLOCK == errno)
		{
			throw std::underflow_error("accept: queue is empty");
		}
		else
		{
			throw std::runtime_error("accept error");
		}
	}
	
	try
	{
		return std::tr1::shared_ptr<ServerSocket>(new ServerSocket(Socket_t(newSocket)));
	}
	catch(std::exception& _err)
	{
		close(newSocket);
		throw;
	}
}

}
