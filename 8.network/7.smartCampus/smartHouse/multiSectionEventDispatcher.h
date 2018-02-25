#ifndef __MULTISECTION_EVENT_DISPATCHER_H__
#define __MULTISECTION_EVENT_DISPATCHER_H__

#include <string>

#include "eventDispatcher.h"

namespace smartCampus
{

class MultisectionEventDispatcher: public EventDispatcher
{
public:
	//MultisectionEventDispatcher();
	virtual ~MultisectionEventDispatcher() = 0;
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query) = 0;
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _section) = 0;
	virtual bool Unsubscribe(Agent* _agent) = 0; //no throw return false on failure
	virtual bool Unsubscribe(Agent* _agent, const std::string& _section) = 0; //no throw return false on failure
	virtual void SendEvent(const Event _event) = 0;
	virtual void SendEvent(const Event _event, const std::string& _sectionName) = 0;
	
};

inline MultisectionEventDispatcher::~MultisectionEventDispatcher(){}

}
#endif /* __MULTISECTION_EVENT_DISPATCHER_H__ */

