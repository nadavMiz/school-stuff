#include <stdexcept>

#include "registrationConnector.h"
#include "vectorSearchTable.h"
#include "protocolMsg.h"

namespace smartCampus
{

const QuerySerializer RegistrationConnector::Record::m_serializer;

/*------------------------RegistrationConnector::Record-----------------------------------*/

RegistrationConnector::Record::Record(const char* _ip, int _port, ProtocolPtr _protocol):
	m_queries(new VectorSearchTable)
,	m_socket(_ip, _port, _protocol){}

ProtocolMsg RegistrationConnector::Record::GetRequestMsg(const Query& _query, const std::string& _topic) const
{
	ProtocolMsg	regRequest;
	regRequest.m_topic = _topic;
	m_serializer.Serialize(_query, regRequest);
	
	return regRequest;
}

void RegistrationConnector::Record::SendRequest(const Query& _query, const std::string& _topic)
{
	ProtocolMsg	regRequest = GetRequestMsg(_query, _topic);
	m_socket.Send(regRequest);
}

void RegistrationConnector::Record::ReciveResponse()
{
	std::string response = m_socket.RecvResponse();
	
	if(response != "ok")
	{
		throw std::runtime_error("request failed");
	}
}

void RegistrationConnector::Record::Register(const Query& _query)
{
	m_queries->Insert(_query);
	
	try
	{
		SendRequest(_query, "subscribe");
		ReciveResponse();
	}
	catch(const std::exception& _err)
	{
		m_queries->ExactRemove(_query);
		throw;
	}
}

/*----------------------------RegistrationConnector---------------------------------------*/

RegistrationConnector::RegistrationConnector(RegistrarConectorPtr _registrar, ProtocolPtr _protocol):
	m_registrar(_registrar)
,	m_protocol(_protocol){}
	
void RegistrationConnector::Register(const std::string& _sectionName, const Query& _query)
{
	
}

}
