#ifndef __MEGA_EVENT_DISPATCHER_H__
#define __MEGA_EVENT_DISPATCHER_H__

#include <tr1/memory>
#include <map>

#include "multiSectionEventDispatcher.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<EventDispatcher> EventDispatcherPtr;

class MegaEventDispatcher: public MultisectionEventDispatcher
{
public:
	MegaEventDispatcher();
	//virtual ~MegaEventDispatcher();
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query);
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _section);
	virtual bool Unsubscribe(Agent* _agent); //no throw return false on failure
	virtual bool Unsubscribe(Agent* _agent, const std::string& _section); //no throw return false on failure
	virtual void SendEvent(const Event _event);
	virtual void SendEvent(const Event _event, const std::string& _sectionName);

private:
	EventDispatcherPtr AddDispatcher(const std::string& _section);

private:
	EventDispatcherPtr m_mainDispatcher;
	std::map<std::string, EventDispatcherPtr> m_dispatchers;

};

}

#endif /* __MEGA_EVENT_DISPATCHER_H__ */

