#include <sys/select.h> /* select */
#include <errno.h> /* errno */
#include <stdexcept>
#include <unistd.h> /* close */
#include <cstring> /* memset + strerror */
#include <algorithm> // std::for_each

#include "selectSet.h"

namespace netcpp
{

static const int MAX_EVENTS = 10;

static inline EventType GetEventTypeImp(const struct epoll_event& _event)
{
	return (_event.events & EPOLLIN) ? e_typeRead: e_typeError;
} 

/*----------------------iterator-------------------------------------*/

SelectSet::iterator::iterator(struct epoll_event* _event, std::map<Socket_t, SocketPtr>* _sockets):
	m_event(_event) 
,	m_sockets(_sockets){}

SocketPtr SelectSet::iterator::operator*()
{
	std::map<Socket_t, SocketPtr>::iterator itr = m_sockets->find(Socket_t(m_event->data.fd));
	
	return itr->second;
}

SocketPtr SelectSet::iterator::operator->()
{
	std::map<Socket_t, SocketPtr>::iterator itr = m_sockets->find(Socket_t(m_event->data.fd));
	
	return itr->second;
}

EventType SelectSet::iterator::GetType()
{
	return GetEventTypeImp(*m_event);
} 

/*---------------------selectSet----------------------------------*/

SelectSet::SelectSet():
m_numReadySockets(0)
{
	m_resultEvents = new struct epoll_event[MAX_EVENTS];
	memset(m_resultEvents, 0, sizeof(struct epoll_event) * MAX_EVENTS);
	
	memset(&m_event, 0, sizeof(struct epoll_event));
	m_event.events = EPOLLIN | EPOLLERR;
	
	m_epoll = epoll_create(1);
	if(-1 == m_epoll)
	{
		delete m_resultEvents;
		throw std::runtime_error("select set creation");
	}
}

SelectSet::~SelectSet()
{
	delete m_resultEvents;
	close(m_epoll);
}

void SelectSet::CloseSet()
{
	if(close(m_epoll) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
}

unsigned int SelectSet::WaitImp(int _time)
{
	int result;
	
	result = epoll_wait(m_epoll, m_resultEvents, MAX_EVENTS, _time);
	if(result < 0)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	m_numReadySockets = (unsigned int)result;
	return m_numReadySockets;
}

void SelectSet::Set(SocketPtr _socket)
{
	m_sockets.insert(std::pair<Socket_t, SocketPtr>(_socket->GetNativeHandler(), _socket));
	
	Socket_t newSocket = _socket->GetNativeHandler();
	m_event.data.fd = newSocket;	
	if(epoll_ctl(m_epoll, EPOLL_CTL_ADD, newSocket, &m_event) < 0)
	{
		m_sockets.erase(m_sockets.find(_socket->GetNativeHandler()));
		throw std::runtime_error(strerror(errno));
	}
}

EventType SelectSet::IsSet(SocketPtr _socket)
{
	Socket_t socketHanle = _socket->GetNativeHandler();
	
	for(unsigned int i = 0; i < m_numReadySockets; ++i)
	{
		if(socketHanle == m_resultEvents[i].data.fd)
		{
			return GetEventType(m_resultEvents[i]);
		}
	}
	
	return e_typeNull;
}

/* functor to clear socket from epoll list */
struct ClearSocket
{
	ClearSocket(int _epollFD): m_epoll(_epollFD){}
	
	void operator()(std::pair<Socket_t, SocketPtr> _socketPair)
	{
		if(epoll_ctl(m_epoll, EPOLL_CTL_DEL, _socketPair.first, NULL) < 0)
		{
			throw std::runtime_error(strerror(errno));
		}
	}
	
	int m_epoll;
};

void SelectSet::ClearOne(SocketPtr _socket)
{
	Socket_t socketHandle = _socket->GetNativeHandler();
	
	ClearSocket clearSocketFunctor(m_epoll);

	clearSocketFunctor(std::pair<Socket_t, SocketPtr>(socketHandle, _socket));
	
	m_sockets.erase(socketHandle);
} 

void SelectSet::ClearAll()
{
	std::for_each(m_sockets.begin(), m_sockets.end(), ClearSocket(m_epoll));
	
	m_sockets.clear();
}

EventType SelectSet::GetEventType(const struct epoll_event& _event)
{
	return GetEventTypeImp(_event);
}

}
