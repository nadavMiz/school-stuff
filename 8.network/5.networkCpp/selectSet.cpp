#include <sys/select.h> /* select */
#include <errno.h> /* errno */
#include <stdexcept>
#include <cstring>

#include "socket_t.h"
#include "selectSet.h"

namespace netcpp
{

const int MAX_SOCKETS = 1024;

SelectSet::SelectSet()
{
	ClearAll();
}

unsigned int SelectSet::WaitImp(struct timeval* _time)
{
	int result;
	m_activeFDs = m_fdSet;
	
	result = select(MAX_SOCKETS, &m_activeFDs, NULL, NULL, _time);
	if(result < 0)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	return (unsigned int)result;
}

void SelectSet::Set(const Socket& _selectable)
{
	Socket_t newSocket = _selectable.GetNativeHandler();
	
	FD_SET(newSocket, &m_fdSet);
}

bool SelectSet::IsSet(const Socket& _selectable)
{
	Socket_t socket = _selectable.GetNativeHandler();
	
	return FD_ISSET(socket, &m_activeFDs);
}

void SelectSet::ClearOne(const Socket& _selectable)
{
	Socket_t socket = _selectable.GetNativeHandler();
	
	FD_CLR(socket, &m_fdSet);
}

void SelectSet::ClearAll()
{
	FD_ZERO(&m_fdSet);
	FD_ZERO(&m_activeFDs);
}

}
