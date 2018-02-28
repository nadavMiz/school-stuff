#ifndef __SINGLE_SECTION_DISPATCHER__
#define __SINGLE_SECTION_DISPATCHER__

#include <map>
#include <pthread.h>
#include <tr1/memory>

#include "eventDispatcher.h"
#include "protectedQueue.h"
#include "registrationTable.h"

using namespace std;

class Agent;
class EventListener;
class Event;

namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrationTable>  RegistrationTablePtr;

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
	RegistrationTablePtr m_registrationTable;
	ProtectedQueue<Event> m_events;
	
	virtual void Notify(const Event& _event);
	virtual void EventsDispatcher();
	
private:
	static void* DispatcherThread(SingleSectionDispatcher* _hub); // calls EventsDispatcher
	void NotifySingleEvent(Agent* _agent, const Event& _event);
	void AddEventListener(Agent* _agent);
	
private:
	pthread_t m_reciverThread;
};

}

#endif /* __SINGLE_SECTION_DISPATCHER__ */

