#ifndef __MY_HUB_H__
#define __MY_HUB_H__

#include <map>
#include <pthread.h>

#include "hub.h"
#include "protectedQueue.h"

using namespace std;

class Agent;
class EventListener;
class Event;

class MyHub: public Hub
{
public:
	MyHub();
	virtual ~MyHub();
	virtual bool Subscribe(Agent* _agent);
	virtual bool Unsubscribe(Agent* _agent);
	virtual void SendEvent(const Event _event);

protected:
	/* data */
	map<Agent*, EventListener*> m_eventListeners;
	ProtectedQueue<Event> m_events;
	
	virtual void Notify(const Event _event);
	virtual void EventsDispatcher();
	
private:
	static void* DispatcherThread(MyHub* _hub); // calls EventsDispatcher
	
	MyHub(const MyHub& _hub);
	MyHub& operator=(const MyHub& _hub);
	
private:
	pthread_t m_reciverThread;
};

#endif /* __HUB_H__ */

