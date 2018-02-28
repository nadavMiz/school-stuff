#include <new>

#include "agent.h"
#include "myHub.h"
#include "event.h"
#include "eventImp.h"
#include "eventListener.h"


MyHub::MyHub(): m_events(1000)
{
	if(pthread_create(&m_reciverThread, NULL, (void * (*)(void *))MyHub::DispatcherThread, this) != 0)
	{
		throw runtime_error("thread create");
	}
}

MyHub::~MyHub()
{
	pthread_cancel(m_reciverThread);
	pthread_join(m_reciverThread, NULL);

	map<Agent*, EventListener*>::iterator itr;
	for(itr = m_eventListeners.begin(); itr != m_eventListeners.end(); ++itr)
	{
		delete itr->second;
	}
}


void* MyHub::DispatcherThread(MyHub* _MyHub)
{
	_MyHub->EventsDispatcher();
	
	pthread_exit(NULL);
}

bool MyHub::Subscribe(Agent* _agent)
{
	if(0 == _agent)
	{
		return false;
	}
	
	if(m_eventListeners.find(_agent) !=  m_eventListeners.end())
	{
		return false;
	}
	
	try
	{
		EventListener* eventListener = new EventListener(_agent);
		m_eventListeners.insert(std::pair<Agent*, EventListener*>(_agent, eventListener));
		return true;
	}
	catch(exception& _err)
	{
		return false;
	}
}

bool MyHub::Unsubscribe(Agent* _agent)
{
	if(0 == _agent)
	{
		return false;
	}
	
	map<Agent*, EventListener*>::iterator itr;
	if((itr = m_eventListeners.find(_agent)) ==  m_eventListeners.end())
	{
		return false;
	}
	
	delete itr->second;
	m_eventListeners.erase(itr);
	
	return true;
}

void MyHub::Notify(const Event _event)
{
	map<Agent*, EventListener*>::iterator itr;
	for(itr = m_eventListeners.begin(); itr != m_eventListeners.end(); ++itr)
	{
		if(itr->second->IsRelevantEvent(_event))
		{
			itr->second->SendEvent(_event);
		}
	}
}

void MyHub::EventsDispatcher()
{
	Event event(new EventImp("","",0));
	while(true)
	{
		m_events.Pop(event);
		Notify(event);
	}
}

void MyHub::SendEvent(const Event _event)
{
	m_events.Push(_event);
}
