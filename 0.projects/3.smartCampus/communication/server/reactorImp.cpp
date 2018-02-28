#include <stdexcept>

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
		m_selectSet.Set(_socket);
	}
}

void ReactorImp::RemoveSocket(SocketPtr _socket)
{
	std::set<SocketPtr>::iterator socketItr = m_sockets.find(_socket);
	if(m_sockets.end() == socketItr)
	{
		throw std::runtime_error("reactor remove: socket doesn't exist");
	}
	
	m_selectSet.ClearOne(_socket);
	m_sockets.erase(socketItr);
	m_dispatcher->Remove(_socket);
}

void ReactorImp::Run()
{
	std::set<SocketPtr>::iterator socketItr, nextItr;
	
	while(true)
	{
		m_selectSet.Wait();
		
		SelectSet::iterator end = m_selectSet.GetResultSetEnd();
		for(SelectSet::iterator itr = m_selectSet.GetResultSetBegin(); itr != end; ++itr)
		{
			m_dispatcher->Dispatch(*itr, itr.GetType());
		}
	}
}

}
