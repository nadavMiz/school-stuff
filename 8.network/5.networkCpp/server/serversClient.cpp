#include "serversClient.h"
#include "netExceptions.h"

namespace netcpp
{

ServersClient::ServersClient(SocketPtr _socket, const TimeValue& _timeOut):
	m_socket(_socket)
,	m_timeOut(_timeOut)
,	m_isActive(true)	
{}

int ServersClient::Send(void* _data, std::size_t _size, CommSocket::MsgFlag _flags)
{
	try
	{
		return m_socket->Send(_data, _size, _flags);
	}
	catch(const BrokenPipe_error& _err)
	{
		m_isActive = false;
		throw;
	}
}

int ServersClient::Recv(void* _data, std::size_t _size, CommSocket::MsgFlag _flags)
{
	try
	{
		return m_socket->Recv(_data, _size, _flags);
	}
	catch(const BrokenPipe_error& _err)
	{
		m_isActive = false;
		throw;
	}
}

}
