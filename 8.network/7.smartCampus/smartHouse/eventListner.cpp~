#include <pthread.h>

#include "eventListener.h"
#include "protectedQueue.h"
#include "eventImp.h"
#include "event.h"

EventListener::EventListener(const Agent* _agent): m_eventQueue(1000)
{
	if(0 == _agent)
	{
		throw "null_pointer";
	}
	
	m_agent = (Agent*)_agent;
	
	if(pthread_create(&m_thread, NULL, (void * (*)(void *))EventListener::EventListnerFunc, this) != 0)
	{
		throw "thread error";
	}
}

EventListener::~EventListener()
{
	pthread_cancel(m_thread);
	pthread_join(m_thread, NULL);
}

void EventListener::SendEvent(const Event _event)
{
	m_eventQueue.Push(_event);
}

void EventListener::ListenToEvent()
{
	Event event(new EventImp);
	while(true)
	{
		m_eventQueue.Pop(event);
		m_agent->ReciveEvent(event);
	}
}

void* EventListener::EventListnerFunc(EventListener* _listener)
{
	_listener->ListenToEvent();
	
	pthread_exit(0);
}

