#include "communicator.h"
#include "hub.h"
#include "server.h"
#include "protocol.h"
#include "shmpProtocol.h"
#include "dbRegistrarConnector.h"
#include "registrationConnector.h"

namespace smartCampus
{

Communicator::Communicator(Hub* _hub, SqlControllerPtr _dataBase):
	m_protocol(new ShmpProtocol)
,	m_registrarConnector(new DbRegistrarConnector)
,	m_registrationConnector(new RegistrationConnector(m_registrarConnector, m_protocol))
,	m_inCommunication(_hub, m_protocol, m_registrarConnector, _dataBase)
{}

void Communicator::Subscribe(const std::string& _sectionName, const Query& _query)
{
	m_registrationConnector->Register(_sectionName, _query);
}

void Communicator::Unsubscribe(const std::string& _sectionName, const Query& _query)
{
	m_registrationConnector->Unregister(_sectionName, _query);
}

}

