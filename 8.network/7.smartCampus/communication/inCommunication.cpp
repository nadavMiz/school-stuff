#include "inCommunication.h"
#include "server.h"
#include "protocolListenerSocket.h"
#include "registrationHandler.h"
#include "eventCommHandler.h"
#include "registrationListenerHandler.h"
#include "eventListenerHandler.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;
typedef std::tr1::shared_ptr<PrototcolListenerSocket> PrototcolListenerSocketPtr;
typedef std::tr1::shared_ptr<EventCommHandler> EventCommHandlerPtr;
typedef std::tr1::shared_ptr<netcpp::IHandler> IHandlerPtr;

InCommunication::InCommunication(Hub* _hub, ProtocolPtr _protocol, RegistrarConectorPtr _registrar, SqlControllerPtr _dataBase):
	m_protocol(_protocol)
,	m_server(new  netcpp::Server)
,	m_serverThread(m_server, &netcpp::Server::ServerRoutine)
{
	SectionData data = GetSectionData(_dataBase);

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

SectionData InCommunication::GetSectionData(SqlControllerPtr _dataBase) const
{
	ResultSetPtr results = _dataBase->Query("SELECT * FROM Info");
	
	return CreateSectionData(results);
}

SectionData InCommunication::CreateSectionData(ResultSetPtr _results) const
{
	if(!_results->next())
	{
		throw std::runtime_error("invalid section name");
	}
	
	SectionData data;
	
	data.m_name = _results->getString("section_name");
	data.m_ip = _results->getString("ip");
	data.m_msgPort = _results->getInt("msg_port");
	data.m_regtistrationPort = _results->getInt("registration_port");
	
	return data;
}

}
