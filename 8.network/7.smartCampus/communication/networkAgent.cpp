#include "networkAgent.h"
#include "nlogFactory.h"
#include "agentData.h"

namespace smartCampus
{

NetworkAgent::NetworkAgentData::NetworkAgentData()
{
	m_agentData.m_id = "0";
	m_agentData.m_type = "network agent";
	m_agentData.m_room = "0";
	m_agentData.m_floor = 0;
	m_agentData.m_config = "";
	m_agentData.m_log = NlogFactory::GetNlogFactory().GetLog("network agent");
}

bool NetworkAgent::IsRelevantEvent(const Event& _event) const
{
	std::multimap<std::string, std::multiset<std::string> >::iterator topicItr = m_topics.find(_event.m_type);
	if(topicItr == m_topics.end())
	{
		return false;
	}
	
	std::multiset<std::string>::iterator roomItr = topicItr->find(_event.m_floor);
}

NetworkAgent::NetworkAgent(ClientSocketPtr _socket, Hub* _hub):
	Agent(m_networkAgentData.GetData(), _hub)
,	m_socket(_socket){}
	
}
