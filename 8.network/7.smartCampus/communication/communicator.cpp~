#include "communicator.h"
#include "hub.h"
#include "server.h"
#include "protocol.h"
#include "eventCommHandler.h"
#include "protocolListenerSocket.h"
#include "shmpProtocol.h"
#include "dbRegistrarConnector.h"
#include "registrationHandler.h"
#include "eventCommHandler.h"
#include "registrationListenerHandler.h"
#include "eventListenerHandler.h"
#include "registrarConector.h"
#include "registrationConnector.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<PrototcolListenerSocket> PrototcolListenerSocketPtr;
typedef std::tr1::shared_ptr<netcpp::IHandler> IHandlerPtr;
typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;
typedef std::tr1::shared_ptr<EventCommHandler> EventCommHandlerPtr;


Communicator::Communicator(Hub* _hub, SqlControllerPtr _dataBase):
	m_protocol(new ShmpProtocol)
,	m_server(new  netcpp::Server)
,	m_serverThread(m_server, &netcpp::Server::ServerRoutine)
,	m_registrarConnector(new DbRegistrarConnector)
,	m_registrationConnector(new RegistrationConnector(m_registrarConnector, m_protocol))
{	
	SectionData data = GetSectionData(_dataBase);

	AddRegistrationHandler(_hub, data.m_regtistrationPort);
	
	AddEventHandler(_hub, data.m_msgPort);
}

Communicator::~Communicator()
{
	m_serverThread.Cancel();
	m_serverThread.Join();
}

void Communicator::AddRegistrationHandler(Hub* _hub, int _port)
{
	RegistrationHandlerPtr registrationHandler(new RegistrationHandler(_hub, m_registrarConnector, m_protocol));
	
	PrototcolListenerSocketPtr registrationListener(new PrototcolListenerSocket(_port, m_protocol));
	registrationListener->SetNoBlock();
	
	IHandlerPtr regListenerHandler(new RegistrationListenerHandler(m_server, registrationHandler));
	
	m_server->AddSocket(registrationListener, regListenerHandler);
}

void Communicator::AddEventHandler(Hub* _hub, int _port)
{
	EventCommHandlerPtr enentHandler(new EventCommHandler(_hub));
	
	PrototcolListenerSocketPtr eventListener(new PrototcolListenerSocket(_port, m_protocol));
	eventListener->SetNoBlock();
	
	IHandlerPtr eventListenHandler(new EventListenerHandler(m_server, enentHandler));
	
	m_server->AddSocket(eventListener, eventListenHandler);
}

void Communicator::Subscribe(const std::string& _sectionName, const Query& _query)
{
	m_registrationConnector->Register(_sectionName, _query);
}

void Communicator::Unsubscribe(const std::string& _sectionName, const Query& _query)
{
	m_registrationConnector->Unregister(_sectionName, _query);
}

SectionData Communicator::GetSectionData(SqlControllerPtr _dataBase) const
{
	ResultSetPtr results = _dataBase->Query("SELECT * FROM Info");
	
	return CreateSectionData(results);
}

SectionData Communicator::CreateSectionData(ResultSetPtr _results) const
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

