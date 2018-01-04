#ifndef __AGENT_H__
#define __AGENT_H__

#include <string>

#include "event.h"

using namespace std;

class Hub;
class AgentData;
class Nlog;

class Agent
{
public:
	Agent(const AgentData& _data, Hub* _hub);
	virtual ~Agent(){}
	
	const string& GetType() {return m_type;}
	const string& GetRoom() {return m_room;}
	unsigned int GetFloor() {return m_floor;}
	
	virtual bool IsRelevantEvent(const Event& _event) const {return false;}
	virtual void ReciveEvent(const Event& _event){}

protected:
	/* data */
	string m_id;
	string m_type;
	string m_room;
	string m_config;
	unsigned int m_floor;
	Nlog* m_log;
	Hub* m_hub;
	
private:
	Agent(const Agent& _agent);
	Agent& operator=(const Agent& _agent);
};

#endif /* __AGENT_H__ */

