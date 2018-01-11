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

void RegistrationConnector::Record::InitializeRequestMsg(const Query& _query, const std::string& _topic, ProtocolMsg& _msg) const
{
	_msg.m_topic = _topic;
	m_serializer.Serialize(_query, _msg);
}

void RegistrationConnector::Record::SendRequest(const Query& _query, const std::string& _topic)
{
	ProtocolMsg	regRequest;
	InitializeRequestMsg(_query, _topic, regRequest);
	
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

void RegistrationConnector::Record::Unregister(const Query& _query)
{
	SendRequest(_query, "unsubscribe");
	ReciveResponse();
	
	m_queries->Remove(_query);
}

/*----------------------------RegistrationConnector---------------------------------------*/

RegistrationConnector::RegistrationConnector(RegistrarConectorPtr _registrar, ProtocolPtr _protocol):
	m_registrar(_registrar)
,	m_protocol(_protocol){}


RegistrationConnector::RecordPtr RegistrationConnector::CreateRecord(const std::string& _section) const
{
	SectionData data = m_registrar->GetSectionData(_section);
	return RecordPtr(new Record(data.m_ip.c_str(), data.m_regtistrationPort, m_protocol));
}

RegistrationConnector::RecordPtr RegistrationConnector::GetRecord(const std::string& _section)
{
	std::map<std::string, std::tr1::shared_ptr<Record> >::iterator recordItr = m_sectionRegistrations.find(_section);
	if(recordItr != m_sectionRegistrations.end())
	{
		return recordItr->second;
	}
	
	RecordPtr record = CreateRecord(_section);
	m_sectionRegistrations.insert(std::pair<std::string, RecordPtr >(_section, record));
	
	return record;
}
	
void RegistrationConnector::Register(const std::string& _section, const Query& _query)
{
	RecordPtr record = GetRecord(_section);
	
	try
	{
		record->Register(_query);
	}
	catch(std::exception& _err)
	{
		if(record->Empty())
		{
			m_sectionRegistrations.erase(_section);
			throw;
		}
	}
}

void RegistrationConnector::Unregister(const std::string& _section, const Query& _query)
{
	std::map<std::string, std::tr1::shared_ptr<Record> >::iterator recordItr = m_sectionRegistrations.find(_section);
	if(recordItr != m_sectionRegistrations.end())
	{
		throw std::runtime_error("invalid section name");
	}
	
	recordItr->second->Unregister(_query);
	
	if(recordItr->second->Empty())
	{
		m_sectionRegistrations.erase(recordItr);
	}
}

}
