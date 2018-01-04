#include "server.h"
#include "listenSocket.h"
#include "masterSocketHandler.h"
#include "reactorImp.h"
#include "dispatcherImp.h"

namespace netcpp
{

const unsigned int MAX_SOCKETS = 1000;

Server::Server(int _port, IHandlerPtr _handler, const TimeValue& _timeOut, std::size_t _backlogSize):
	m_reactor(new ReactorImp(MAX_SOCKETS))
,	m_dispatcher(new DispatcherImp)
{
	m_reactor->SetDispatcher(m_dispatcher);
	m_dispatcher->SetReactor(m_reactor);
	
	SocketPtr masterSocket(new ListenSocket(_port, _backlogSize));
	dynamic_cast<ListenSocket*>(masterSocket.get())->SetNoBlock();
	IHandlerPtr masterSocketHandler(new MasterSocketHandler(m_reactor, _handler));
	
	m_reactor->AddSocket(masterSocket, masterSocketHandler);
}

void Server::ServerRoutine()
{
	m_reactor->Run();
}

}
