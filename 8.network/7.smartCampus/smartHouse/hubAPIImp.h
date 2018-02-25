#ifndef __AGETN_API_IMP_H__
#define __AGETN_API_IMP_H__

#include "uncopyable.h"
#include "iHubAPI.h"

class Hub;

namespace smartCampus
{

class Communicator;

class HubAPIIMP: public IHubAPI
{
public:
	HubAPIIMP(Hub* _hub, Communicator* _communicator);
	//virtual ~HubAPIIMP();
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query);
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName);
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query);
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName);
	virtual void SendEvent(const Event& _event);
	
private:
	Hub* m_hub;
	Communicator* m_communicator;
	
};

}

#endif /* __AGETN_API_IMP_H__ */

