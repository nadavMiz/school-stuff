#include "communicator.h"
#include "eventCommHandler.h"
#include "protocolListenerSocket.h"
#include "shmpProtocol.h"
#include "dbRegistrarConnector.h"
#include "registrationHandler.h"
#include "eventCommHandler.h"
#include "registrationListenerHandler.h"
#include "eventListenerHandler.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<PrototcolListenerSocket> PrototcolListenerSocketPtr;
typedef std::tr1::shared_ptr<netcpp::IHandler> IHandlerPtr;
typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;
typedef std::tr1::shared_ptr<EventCommHandler> EventCommHandlerPtr;


Communicator::Communicator(Hub* _hub):
	m_protocol(new ShmpProtocol)
,	m_server(new  netcpp::Server)
,	m_serverThread(m_server, &netcpp::Server::ServerRoutine)
,	m_registrarConnector(new DbRegistrarConnector)
{	
	AddRegistrationHandler(_hub);
	
	AddEventHandler(_hub);
}

Communicator::~Communicator()
{
	m_serverThread.Cancel();
	m_serverThread.Join();
}

void Communicator::AddRegistrationHandler(Hub* _hub)
{
	RegistrationHandlerPtr registrationHandler(new RegistrationHandler(_hub, m_registrarConnector, m_protocol));
	
	PrototcolListenerSocketPtr registrationListener(new PrototcolListenerSocket(2003, m_protocol));
	registrationListener->SetNoBlock();
	
	IHandlerPtr regListenerHandler(new RegistrationListenerHandler(m_server, registrationHandler));
	
	m_server->AddSocket(registrationListener, regListenerHandler);
}

void Communicator::AddEventHandler(Hub* _hub)
{
	EventCommHandlerPtr enentHandler(new EventCommHandler(_hub));
	
	PrototcolListenerSocketPtr eventListener(new PrototcolListenerSocket(2004, m_protocol));
	eventListener->SetNoBlock();
	
	IHandlerPtr eventListenHandler(new EventListenerHandler(m_server, enentHandler));
	
	m_server->AddSocket(eventListener, eventListenHandler);
}

}

