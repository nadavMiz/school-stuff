#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <string>

#include "nlog.h"

class AgentData
{
public:
	AgentData(){}
	virtual ~AgentData (){}
		
	AgentData(const AgentData& _data);
	AgentData& operator=(const AgentData& _data);
	
	/* data */
	std::string m_id;
	std::string m_type;
	std::string m_room;
	unsigned int m_floor;
	std::string m_config;
	Nlog* m_log;

};

#endif /* __AGENT_DATA_H__ */

