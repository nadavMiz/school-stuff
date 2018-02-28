#ifndef __HUB_IMP_H__
#define __HUB_IMP_H__

#include <tr1/memory>

#include "hub.h"
#include "multiSectionEventDispatcher.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<MultisectionEventDispatcher> MultiSectionEventDispatcherPtr;

class HubImp: public Hub //uncopyable
{
public:
	HubImp(const std::string& _sectionName);
	//virtual ~HubImp();
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query);
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName); 
	virtual bool Unsubscribe(Agent* _agent); //no throw. return false if fails
	virtual bool Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName); //no throw. return false if fails
	virtual void SendEvent(Event _event);
	virtual void SendEvent(Event _event, const std::string& _sectionName);
	//void ConnectCommunicator(smartCampus::Communicator* _communicator){m_communicator = _communicator;}

	
protected:
	//smartCampus::Communicator* m_communicator;
	MultiSectionEventDispatcherPtr m_dispatcher;
	std::string m_sectionName;
	
};

}
#endif /* __HUB_IMP_H__ */

