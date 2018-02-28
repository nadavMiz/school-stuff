#ifndef IDISPATCHER_H
#define IDISPATCHER_H

#include <tr1/memory>

#include "serverEnums.h"
#include "ihandler.h"

/*
 * @brief: interface for dispatcher part of the server.
 * dispatcher is the part of the server responsible to hold event handlers
 * and to activate(dispatch) them on their respective sockets when an event occurs.
 *
 * @author: nadav mizrahi
**/

namespace netcpp
{

class IReactor;

typedef std::tr1::shared_ptr<Socket> SocketPtr;
typedef std::tr1::shared_ptr<IHandler> IHandlerPtr;
typedef std::tr1::shared_ptr<IReactor> ReactorPtr;
		
class IDispatcher
{

public:
	IDispatcher(){}
	virtual ~IDispatcher() = 0;
	virtual void Register(SocketPtr _socket, IHandlerPtr _handler) = 0;
	virtual void Remove(SocketPtr _socket) = 0;
	virtual void Dispatch(SocketPtr _socket, EventType _type) = 0;
	
	inline void SetReactor(ReactorPtr _reactor);
	
protected:
	ReactorPtr m_reactor; //reactor to recive events from
	
private:
	IDispatcher(const IDispatcher&); //uncopyable
	IDispatcher& operator=(const IDispatcher&); //uncopyable
};

inline IDispatcher::~IDispatcher(){}

inline void IDispatcher::SetReactor(ReactorPtr _reactor)
{
	m_reactor = _reactor;
}

}
#endif /* IDISPATCHER_H */

