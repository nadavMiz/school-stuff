#include <stdexcept>
#include "dispatcherImp.h"
#include "netExceptions.h"
#include "ireactor.h"

namespace netcpp
{

void DispatcherImp::Register(SocketPtr _socket, IHandlerPtr _handler)
{
	m_handlers.insert(std::pair<SocketPtr, IHandlerPtr>(_socket, _handler));
}

void DispatcherImp::Remove(SocketPtr _socket)
{
	std::map<SocketPtr, IHandlerPtr>::iterator itr = m_handlers.find(_socket);
	if(m_handlers.end() == itr)
	{
		throw std::runtime_error("dispatcher remove: invalid socket");
	}
	m_handlers.erase(itr);
}

EventStatus DispatcherImp::HandleEvent(SocketPtr _socket, EventType _type)
{
	std::map<SocketPtr, IHandlerPtr>::iterator itr = m_handlers.find(_socket);
	if(m_handlers.end() == itr)
	{
		throw std::runtime_error("dispatcher dispatch: invalid socket");
	}
	
	try
	{
	switch(_type)
	{
		case e_typeRead:
			return itr->second->HandleEvent(itr->first);
			break;
			
		default:
			return e_statusOk;
	}
	}
	catch(const BrokenPipe_error& _err)
	{
		return e_statusToDelete;
	}
}

void DispatcherImp::HandleEventStatus(SocketPtr _socket, EventStatus _status)
{
	if(_status == e_statusToDelete)
	{
		m_reactor->RemoveSocket(_socket);
	}
}

void DispatcherImp::Dispatch(SocketPtr _socket, EventType _type)
{
	EventStatus status = HandleEvent(_socket, _type);
	
	HandleEventStatus(_socket, status);
}

}
