#ifndef __IHUB_API_H__
#define __IHUB_API_H__

#include "uncopyable.h"
#include "agent.h"
#include "query.h"

namespace smartCampus
{

class IHubAPI: private Uncopyable
{
public:
	//IHubAPI();
	virtual ~IHubAPI() = 0;
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query) = 0;
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName) = 0;
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query) = 0;
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName) = 0;
	virtual void SendEvent(const Event& _event) = 0;
};

inline IHubAPI::~IHubAPI(){}

}

#endif /* __IHUB_API_H__ */

