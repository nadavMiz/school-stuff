#include <sstream>

#include "networkAgent.h"
#include "nlogFactory.h"
#include "agentData.h"
#include "vectorSearchTable.h"
#include "query.h"
#include "hub.h"
#include "eventImp.h"

namespace smartCampus
{

const AgentData& NetworkAgent::GetAgentData()
{
	static const NetworkAgentData networkAgentData;
	
	return networkAgentData.GetData();
}

NetworkAgent::NetworkAgentData::NetworkAgentData()
{
	m_agentData.m_id = "0";
	m_agentData.m_type = "network agent";
	m_agentData.m_room = "0";
	m_agentData.m_floor = 0;
	m_agentData.m_config = "";
	m_agentData.m_log = NlogFactory::GetNlogFactory().GetLog("network agent");
}

NetworkAgent::NetworkAgent(ClientSocketPtr _socket, Hub* _hub):
	Agent(GetAgentData(), _hub)
,	m_socket(_socket)
,	m_topics(new VectorSearchTable<int>)
{
	m_hub->Subscribe(this);
}

NetworkAgent::~NetworkAgent()
{
	m_hub->Unsubscribe(this);
}

Query NetworkAgent::ParseEvent(const Event& _event) const
{
	Query query;
	query.m_topic = _event->m_type;
	query.m_room = _event->m_room;
	std::ostringstream stm;
	stm << _event->m_floor;
	query.m_floor = stm.str();
	query.m_section = _event->m_section;
	
	return query;
}

bool NetworkAgent::IsRelevantEvent(const Event& _event) const
{
	Query query = ParseEvent(_event);
	
	return m_topics->IsPresent(query);
}

void NetworkAgent::ReciveEvent(const Event& _event)
{
	ProtocolMsg protocolMsg = m_serializer.Serialize(_event);
	m_socket->Send(protocolMsg);
}

}
