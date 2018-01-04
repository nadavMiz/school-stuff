#ifndef IREACTOR_H
#define IREACTOR_H

#include <tr1/memory>

#include "socket.h"
#include "ihandler.h"

/*
 * @brief: reactor is the part of the server responsible to monitor for new events
 * and to report them to the dispatcher.
 *
 * @author: nadav mizrahi
**/

namespace netcpp
{

class IDispatcher;

typedef std::tr1::shared_ptr<Socket> SocketPtr;
typedef std::tr1::shared_ptr<IHandler> IHandlerPtr;
typedef std::tr1::shared_ptr<IDispatcher> DispatcherPtr;

class IReactor
{
public:
	IReactor(){}
	virtual ~IReactor() = 0;
	
	virtual void AddSocket(SocketPtr _socket, IHandlerPtr _handler) = 0;
	virtual void RemoveSocket(SocketPtr _socket) = 0;
	virtual void Run() = 0;
	
	inline void SetDispatcher(DispatcherPtr _dispatcher);

protected:
	DispatcherPtr m_dispatcher;

private:
	IReactor(const IReactor&); //uncopyable
	IReactor& operator=(const IReactor&); //uncopyable
};

inline IReactor::~IReactor(){}

inline void IReactor::SetDispatcher(DispatcherPtr _dispatcher)
{
	m_dispatcher = _dispatcher;
}

}

#endif /* IREACTOR_H */

