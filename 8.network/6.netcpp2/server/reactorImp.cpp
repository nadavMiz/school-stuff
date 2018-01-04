#include <stdexcept>
#include <algorithm>

#include "reactorImp.h"
#include "serverEnums.h"
#include "iDispatcher.h"

namespace netcpp
{

ReactorImp::ReactorImp(unsigned int _maxSockets): m_maxSockets(_maxSockets){}

void ReactorImp::AddSocket(SocketPtr _socket, IHandlerPtr _handler)
{
	if(m_sockets.size() != m_maxSockets)
	{
		m_dispatcher->Register(_socket, _handler);
		m_sockets.insert(_socket);
		m_selectSet.Set(*_socket);
	}
}

void ReactorImp::RemoveSocket(SocketPtr _socket)
{
	std::set<SocketPtr>::iterator socketItr = m_sockets.find(_socket);
	if(m_sockets.end() == socketItr)
	{
		throw std::runtime_error("reactor remove: socket doesn't exist");
	}
	
	m_selectSet.ClearOne(*_socket);
	m_sockets.erase(socketItr);
	m_dispatcher->Remove(_socket);
}

void ReactorImp::HandleSingleEvent(SocketPtr _socket, unsigned int& _NumActiveSockets)
{
	EventType eventType = m_selectSet.IsSet(*_socket);
	if(eventType)
	{
		m_dispatcher->Dispatch(_socket, eventType);
		--_NumActiveSockets;
	}
}

void ReactorImp::Run()
{
	unsigned int NumActiveSockets;
	std::set<SocketPtr>::iterator socketItr, nextItr;
	
	while(true)
	{
		NumActiveSockets = m_selectSet.Wait();
		for(socketItr = nextItr = m_sockets.begin(); 0 < NumActiveSockets; socketItr = nextItr)
		{
			++nextItr;
			HandleSingleEvent(*socketItr, NumActiveSockets);
		}
	}
}

}
