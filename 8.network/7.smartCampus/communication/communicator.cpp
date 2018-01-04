#include "communicator.h"
#include "eventCommHandler.h"
#include "listenSocket.h"
#include "intEventFactory.h"
#include "shmpProtocol.h"

namespace smartCampus
{

Communicator::Communicator(Hub* _hub):
	m_protocol(new ShmpProtocol)
,	m_server(new  netcpp::Server)
,	m_serverThread(m_server, &netcpp::Server::ServerRoutine)
,	m_hub(_hub)
{
	netcpp::ListenSocket listener(2001);
	
	std::tr1::shared_ptr<netcpp::Socket> newSocket = listener.Accept();
	std::tr1::shared_ptr<netcpp::IHandler> handler(new EventCommHandler(m_protocol , m_hub));
	
	m_server->AddSocket(newSocket, handler);
}

Communicator::~Communicator()
{
	m_serverThread.Cancel();
	m_serverThread.Join();
}

}

