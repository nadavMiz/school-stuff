#ifndef __HUB_H__
#define __HUB_H__

#include <string>

#include "query.h"

class Agent;
class Event;
namespace smartCampus
{
	class Communicator;
}

class Hub
{
public:
	Hub(){}
	virtual ~Hub(){}
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query) = 0;
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName) = 0;
	virtual bool Unsubscribe(Agent* _agent) = 0; //no throw
	virtual bool Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName) = 0; //no throw
	virtual void SendEvent(const Event _event) = 0;
	void ConnectCommunicator(smartCampus::Communicator* _communicator){m_communicator = _communicator;}
	
protected:
	smartCampus::Communicator* m_communicator;
};

#endif /* __MY_HUB_H__ */

