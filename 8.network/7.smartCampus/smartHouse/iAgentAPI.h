#ifndef __IAGENT_API_H__
#define __IAGENT_API_H__

#include "uncopyable.h"

namespace smartCampus
{

class IAgentAPI: private Uncopyable
{
public:
	//IAgentsAPI();
	virtual ~IAgentAPI() = 0;
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query);
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName);
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query);
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName);
	virtual void SendEvent(const Event& _event) = 0;
};

inline IAgentAPI::~IAgentAPI(){}

}

#endif /* __AGENTS_API_H__ */

