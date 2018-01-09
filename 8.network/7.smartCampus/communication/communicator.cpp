#include "communicator.h"
#include "eventCommHandler.h"
#include "protocolListenerSocket.h"
#include "shmpProtocol.h"
#include "dbRegistrarConnector.h"
#include "registrationListenerHandler.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<PrototcolListenerSocket> PrototcolListenerSocketPtr;
typedef std::tr1::shared_ptr<RegistrationListenerHandler> RegistrationListenerHandlerPtr;

Communicator::Communicator(Hub* _hub):
	m_hub(_hub)
,	m_protocol(new ShmpProtocol)
,	m_server(new  netcpp::Server)
,	m_serverThread(m_server, &netcpp::Server::ServerRoutine)
,	m_registrarConnector(new DbRegistrarConnector)
,	m_registrationHandler(new RegistrationHandler(m_hub, m_registrarConnector, m_protocol))
{	

	PrototcolListenerSocketPtr registrationListener(new PrototcolListenerSocket(2003, m_protocol));
	registrationListener->SetNoBlock();
	RegistrationListenerHandlerPtr regListenerHandler(new RegistrationListenerHandler(m_server.get(), m_registrationHandler));
	m_server->AddSocket(registrationListener, regListenerHandler);
	
	/*-------------------------------------------*/
	
	PrototcolListenerSocket listener(2001, m_protocol);
	
	std::tr1::shared_ptr<netcpp::Socket> newSocket = listener.Accept();
	std::tr1::shared_ptr<netcpp::IHandler> handler(new EventCommHandler(m_hub));
	
	m_server->AddSocket(newSocket, handler);
}

Communicator::~Communicator()
{
	m_serverThread.Cancel();
	m_serverThread.Join();
}

}

