#ifndef DISPATCHER_IMP_H
#define DISPATCHER_IMP_H

#include <map>

#include "iDispatcher.h"
#include "ihandler.h"
#include "serverEnums.h"

namespace netcpp
{

class DispatcherImp: public IDispatcher
{

public:
	// DispatcherImp(); default CTOR
	virtual ~DispatcherImp(){}
	virtual void Register(SocketPtr _socket, IHandlerPtr _handler);
	virtual void Remove(SocketPtr _socket);
	virtual void Dispatch(SocketPtr _socket, EventType _type);
	
	//inline void SetReactor(std::tr1::shared_ptr<IReactor> _reactor);
	
private:
	std::map<SocketPtr, IHandlerPtr> m_handlers;
	//std::tr1::shared_ptr<iReactor> m_reactor;
	
private:
	EventStatus HandleEvent(SocketPtr _socket, EventType _type);
	void HandleEventStatus(SocketPtr _socket, EventStatus _status);
	
};

}
#endif /* DISPATCHER_IMP_H */

