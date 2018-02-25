#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include "uncopyable.h"
#include "event.h"

class Agent;

namespace smartCampus
{

class Query;

class EventDispatcher: private Uncopyable
{
public:
	//EventDispatcher();
	virtual ~EventDispatcher() = 0;
	virtual void Subscribe(Agent* _agent, const Query& _query) = 0;
	virtual bool Unsubscribe(Agent* _agent) = 0; //no throw return false on failure
	virtual void SendEvent(const Event _event) = 0;

};

inline EventDispatcher::~EventDispatcher(){}

}

#endif /* __EVENT_DISPATCHER_H__ */

