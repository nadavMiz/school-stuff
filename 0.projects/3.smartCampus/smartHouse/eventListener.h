#ifndef __EVENT_LISTNER_H__
#define __EVENT_LISTNER_H__

#include "agent.h"
#include "protectedQueue.h"

class Event;

class EventListener
{
public:
	explicit EventListener(const Agent* _agent);
	virtual ~EventListener();	
	
	void SendEvent(const Event _event);
	bool IsRelevantEvent(const Event _event) const {return m_agent->IsRelevantEvent(_event); }

protected:
	virtual void ListenToEvent();

private:
	static void* EventListnerFunc(EventListener* _listener); //calls ListenToEvent()
	
	EventListener(const EventListener& _listener);
	EventListener& operator=(const EventListener& _listner);

protected:
	/* data */
	Agent* m_agent;
	ProtectedQueue<Event> m_eventQueue;
	pthread_t m_thread;
};

#endif /* __EVENT_LISTNER_H__ */

