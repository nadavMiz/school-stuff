#include "server.h"
#include "listenSocket.h"
#include "masterSocketHandler.h"
#include "reactorImp.h"
#include "dispatcherImp.h"

namespace netcpp
{

const unsigned int MAX_SOCKETS = 1000;

Server::Server():
	m_reactor(new ReactorImp(MAX_SOCKETS))
,	m_dispatcher(new DispatcherImp)
{
	m_reactor->SetDispatcher(m_dispatcher);
	m_dispatcher->SetReactor(m_reactor);
}

void Server::ServerRoutine()
{
	m_reactor->Run();
}

}
