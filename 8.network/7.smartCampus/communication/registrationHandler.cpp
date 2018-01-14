#include <algorithm> //for_each
#include <tr1/functional> //bind
#include <string>
#include <sstream>

#include "registrationHandler.h"
#include "parsingFunctions.h"
#include "query.h"
#include "netExceptions.h"
#include "sectionData.h"
#include "nlogFactory.h"

namespace smartCampus
{

RegistrationHandler::RegistrationHandler(Hub* _hub, RegistrarConectorPtr _registrar, ProtocolPtr _protocol):
	m_hub(_hub)
,	m_registrar(_registrar)
,	m_protocol(_protocol)
,	m_log(NlogFactory::GetLog1("system.log")){}

netcpp::EventStatus RegistrationHandler::HandleEvent(netcpp::SocketPtr _socket)
{
	ProtocolCommSocket* socket = static_cast<ProtocolCommSocket*>(_socket.get());
	std::string response = "ok";
	
	try
	{
		ProtocolMsg msg = socket->Recv();
		HandleRequest(msg);
	}
	catch(const netcpp::BadRequest_error& _err)
	{
		stringstream ss;
		ss << "cought bad_request at RegistrationHandler::HandleEvent: " << _err.what();
		m_log->write(ss.str(), "system");
		
		response = "badRequest";
	}
	catch(const netcpp::BrokenPipe_error& _err)
	{
		stringstream ss;
		ss << "cought broken_pipe at RegistrationHandler::HandleEvent: " << _err.what();
		m_log->write(ss.str(), "system");
		
		return netcpp::e_statusToDelete;
	}
	catch(const std::exception& _err)
	{
		stringstream ss;
		ss << "cought exception at RegistrationHandler::HandleEvent: " << _err.what();
		m_log->write(ss.str(), "system");
		
		response = "error";
	}
	
	socket->SendResponse(response);
	return netcpp::e_statusOk;
}

void RegistrationHandler::HandleRequest(const ProtocolMsg& _msg)
{
	Query query = ParseMsg(_msg);
	NetworkAgentPtr netAgent = GetNetworkAgent(_msg.m_values[0]);
	
	if("subscribe" == _msg.m_topic)
	{
		netAgent->AddRegistration(query);
	}
	else
	{
		netAgent->RemoveRegistration(query);
	}
}

void RegistrationHandler::ParseMsgField(const std::string& _str, Query* _query)
{
	std::string key, value;
	
	ParsingFunctions::ParseKeyValue(_str, key, value);
	if("topic" == key)
	{
		_query->m_topic = value;
	}
	else if("room" == key)
	{
		_query->m_room = value;
	}
	else if("floor" == key)
	{
		_query->m_floor = value;
	}
	else
	{
		throw netcpp::BadRequest_error("invalid key");
	}
}

Query RegistrationHandler::ParseMsg(const ProtocolMsg& _msg) const
{
	if(_msg.m_topic != "subscribe" && _msg.m_topic != "unsubscribe")
	{
		std::stringstream ss;
		ss << "RegistrationHandler::ParseMsgField: invalid subscription type " << std::endl;
		ss << "	msg" << _msg;
		m_log->write(ss.str(), "system");
		
		throw netcpp::BadRequest_error("invalid subscription type");
	}

	Query query;
	std::for_each(_msg.m_values.begin() + 1, _msg.m_values.end(), std::tr1::bind(ParseMsgField, std::tr1::placeholders::_1, &query));
	
	return query;
}

NetworkAgentPtr RegistrationHandler::GetNetworkAgent(const std::string& _sectionPair)
{
	std::string key, section;
	ParsingFunctions::ParseKeyValue(_sectionPair, key, section);
	if("section" != key)
	{
		m_log->write("RegistrationHandler::GetNetworkAgent: invalid key" + key, "system");
		
		throw netcpp::BadRequest_error("invalid key");
	}

	std::map<std::string, NetworkAgentPtr>::iterator itr = m_networkAgents.find(key);
	
	if(itr != m_networkAgents.end())
	{
		return itr->second;
	}
	
	NetworkAgentPtr newAgent = CreateNetworkAgent(section);
	m_networkAgents.insert(std::pair<std::string, NetworkAgentPtr>(section, newAgent));
	
	return newAgent;
}

NetworkAgentPtr RegistrationHandler::CreateNetworkAgent(const std::string& _section)
{
	SectionData data = m_registrar->GetSectionData(_section);
	
	ClientSocketPtr agentsSocket(new ProtocolCommSocket(data.m_ip.c_str(), data.m_msgPort, m_protocol));
	return NetworkAgentPtr(new NetworkAgent(agentsSocket, m_hub));
}

}
