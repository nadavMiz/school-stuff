#ifndef SELECT_SET_H
#define SELECT_SET_H

#include <sys/select.h> /* fd_set */
#include <sys/epoll.h>
#include <tr1/memory> /* shared_ptr */
#include <map> 

#include "timeValue.h" /* timeValue */
#include "timeValueOperations.h" // timevalueToMiliseconds
#include "socket.h" /* Socket */
#include "serverEnums.h" /* EventType */
#include "uncopyable.h"
#include "socket_t.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<Socket> SocketPtr;

class SelectSet: private Uncopyable
{
public:
	class iterator
	{
	friend class SelectSet;
	
	public:
		iterator();
		void operator++();
		void operator--();
		bool operator==(const iterator& _itr);
		bool operator!=(const iterator& _itr);
		SocketPtr operator*();
		SocketPtr operator->();
		EventType GetType();
	
	private:
		iterator(struct epoll_event* _event, std::map<Socket_t, SocketPtr>* _sockets);
	
	private:
		struct epoll_event* m_event;
		std::map<Socket_t, SocketPtr>* m_sockets;
	};

public:
	SelectSet();
	~SelectSet();
	void CloseSet(); // perfoms DTOR operation but throws exceptions 
	
	unsigned int Wait();
	unsigned int WaitUntil(const TimeValue& _time);
	void Set(SocketPtr _selectable);
	EventType IsSet(SocketPtr _socket);
	iterator GetResultSetBegin();
	iterator GetResultSetEnd();
	void ClearOne(SocketPtr _socket);
	void ClearAll();

private:
	EventType GetEventType(const struct epoll_event& _event); 
	
	unsigned int WaitImp(int _time);

private:
	/* data */
	int m_epoll;
	unsigned int m_numReadySockets;
	struct epoll_event m_event;
	struct epoll_event* m_resultEvents;
	std::map<Socket_t, SocketPtr> m_sockets;
};

/* iterator functions*/

inline void SelectSet::iterator::operator++()
{
	++m_event;
}

inline void SelectSet::iterator::operator--()
{
	--m_event;
}

inline bool SelectSet::iterator::operator==(const iterator& _itr)
{
	return m_event == _itr.m_event;
}

inline bool SelectSet::iterator::operator!=(const iterator& _itr)
{
	return !(*this == _itr);
}

/* selectSet functions */

inline unsigned int SelectSet::Wait()
{
	return WaitImp(-1);
}

inline unsigned int SelectSet::WaitUntil(const TimeValue& _time)
{
	return WaitImp(TimeValueToMiliSeconds(_time));
}

inline SelectSet::iterator SelectSet::GetResultSetBegin()
{
	return SelectSet::iterator(m_resultEvents, &m_sockets);
}

inline SelectSet::iterator SelectSet::GetResultSetEnd()
{
	return SelectSet::iterator(m_resultEvents + m_numReadySockets, &m_sockets);
}

}
#endif /* SELECT_SET_H */

