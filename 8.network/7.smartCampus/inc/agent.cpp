#include "agent.h"
#include "agentData.h"
#include "nlog.h"

Agent::Agent(const AgentData& _data, Hub* _hub)
{
	if(0 == _hub)
	{
		throw "invalid hub";
	}
	
	m_id = _data.m_id;
	m_type = _data.m_type;
	m_room = _data.m_room;
	m_floor = _data.m_floor;
	m_log = _data.m_log;
	m_config = _data.m_config;
	m_hub = _hub;
}
