#ifndef __SINGLE_SECTION_DISPATCHER__
#define __SINGLE_SECTION_DISPATCHER__

#include <map>
#include <pthread.h>

#include "eventDispatcher.h"
#include "protectedQueue.h"

using namespace std;

class Agent;
class EventListener;
class Event;

namespace smartCampus
{

class SingleSectionDispatcher: public EventDispatcher
{
public:
	SingleSectionDispatcher();
	virtual ~SingleSectionDispatcher();
	virtual void Subscribe(Agent* _agent, const Query& _query);
	virtual bool Unsubscribe(Agent* _agent); //no throw return false on failure
	virtual void SendEvent(const Event _event);
	
protected:
	/* data */
	map<Agent*, EventListener*> m_eventListeners;
	ProtectedQueue<Event> m_events;
	
	virtual void Notify(const Event _event);
	virtual void EventsDispatcher();
	
private:
	static void* DispatcherThread(SingleSectionDispatcher* _hub); // calls EventsDispatcher
	
private:
	pthread_t m_reciverThread;
};

}

#endif /* __SINGLE_SECTION_DISPATCHER__ */
