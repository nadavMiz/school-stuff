#include <cstring> /* strerror */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */
#include <stdexcept> /* exceptions */
#include <sys/types.h> /* ssize_t */
#include <sys/socket.h> /* sockets */
#include <errno.h> /* errno */

#include "commSocket.h"
#include "netExceptions.h"


namespace netcpp
{

static const int flags[] = {0, MSG_DONTWAIT};
std::vector<int> CommSocket::m_flags(flags, flags + sizeof(flags)/sizeof(flags[0]));

CommSocket::~CommSocket()
{
	close(m_socket);
}

void CommSocket::Disconnect()
{
	if(close(m_socket) < 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

void CommSocket::MsgErrorHandler()
{
	switch(errno)
	{
		case EAGAIN:
			throw std::underflow_error(strerror(errno));
			
		case EPIPE:
			throw BrokenPipe_error("connection closed");
			
		default:
			throw ReadWrite_error(strerror(errno));
	}
}

std::size_t CommSocket::Send(const void* _data, std::size_t _size, MsgFlag _flag)
{
	std::size_t result;
	
	result = send(m_socket, _data, _size, GetFlag(_flag) | MSG_NOSIGNAL);
	if(result < 0)
	{
		MsgErrorHandler();
	}
	
	return result;
}

std::size_t CommSocket::Recv(void* _data, std::size_t _size, MsgFlag _flag)
{
	ssize_t result;
	
	result = recv(m_socket, _data, _size, GetFlag(_flag));
	if(0 == result)
	{
		throw BrokenPipe_error("connection closed");
	}
	else if(result < 0)
	{
		MsgErrorHandler();
	}
	
	return result;
}

int CommSocket::GetFlag(MsgFlag _flag) const
{
	return m_flags.at(_flag);
}

}
