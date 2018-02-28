#include "inCommunication.h"
#include "server.h"
#include "protocolListenerSocket.h"
#include "registrationHandler.h"
#include "eventCommHandler.h"
#include "registrationListenerHandler.h"
#include "eventListenerHandler.h"
#include "sectionData.h"
#include "dbSmartBuildingInformation.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;
typedef std::tr1::shared_ptr<PrototcolListenerSocket> PrototcolListenerSocketPtr;
typedef std::tr1::shared_ptr<EventCommHandler> EventCommHandlerPtr;
typedef std::tr1::shared_ptr<netcpp::IHandler> IHandlerPtr;

InCommunication::InCommunication(Hub* _hub, ProtocolPtr _protocol, RegistrarConectorPtr _registrar, const std::string& _configPath):
	m_protocol(_protocol)
,	m_smartBuildingInformation(new DBSmartBuildingInformation)
,	m_server(new  netcpp::Server)
,	m_serverThread(m_server, &netcpp::Server::ServerRoutine)
{
	SectionData data = m_smartBuildingInformation->GetSectionData(_configPath);

	AddRegistrationHandler(_hub, data.m_regtistrationPort, _registrar);
	
	AddEventHandler(_hub, data.m_msgPort);
}

InCommunication::~InCommunication()
{
	m_serverThread.Cancel();
	m_serverThread.Join();
}

void InCommunication::AddRegistrationHandler(Hub* _hub, int _port, RegistrarConectorPtr _registrar)
{
	RegistrationHandlerPtr registrationHandler(new RegistrationHandler(_hub, _registrar, m_protocol));
	
	PrototcolListenerSocketPtr registrationListener(new PrototcolListenerSocket(_port, m_protocol));
	registrationListener->SetNoBlock();
	
	IHandlerPtr regListenerHandler(new RegistrationListenerHandler(m_server, registrationHandler));
	
	m_server->AddSocket(registrationListener, regListenerHandler);
}

void InCommunication::AddEventHandler(Hub* _hub, int _port)
{
	EventCommHandlerPtr enentHandler(new EventCommHandler(_hub));
	
	PrototcolListenerSocketPtr eventListener(new PrototcolListenerSocket(_port, m_protocol));
	eventListener->SetNoBlock();
	
	IHandlerPtr eventListenHandler(new EventListenerHandler(m_server, enentHandler));
	
	m_server->AddSocket(eventListener, eventListenHandler);
}

}
