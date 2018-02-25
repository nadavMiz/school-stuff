#include <new>

#include "agent.h"
#include "query.h"
#include "singleSectionDispatcher.h"
#include "event.h"
#include "eventImp.h"
#include "eventListener.h"
#include "communicator.h"

namespace smartCampus
{

SingleSectionDispatcher::SingleSectionDispatcher(): m_events(1000)
{
	if(pthread_create(&m_reciverThread, NULL, (void * (*)(void *))SingleSectionDispatcher::DispatcherThread, this) != 0)
	{
		throw runtime_error("thread create");
	}
}

SingleSectionDispatcher::~SingleSectionDispatcher()
{
	pthread_cancel(m_reciverThread);
	pthread_join(m_reciverThread, NULL);

	map<Agent*, EventListener*>::iterator itr;
	for(itr = m_eventListeners.begin(); itr != m_eventListeners.end(); ++itr)
	{
		delete itr->second;
	}
}


void* SingleSectionDispatcher::DispatcherThread(SingleSectionDispatcher* _SingleSectionDispatcher)
{
	_SingleSectionDispatcher->EventsDispatcher();
	
	return 0;
}

void SingleSectionDispatcher::Subscribe(Agent* _agent, const Query& _query)
{	
	if(m_eventListeners.find(_agent) !=  m_eventListeners.end())
	{
		throw std::runtime_error("agent already exists");
	}
	
	EventListener* eventListener = new EventListener(_agent);
	try
	{
		m_eventListeners.insert(std::pair<Agent*, EventListener*>(_agent, eventListener));
	}
	catch(const std::exception& _err)
	{
		delete eventListener;
		throw;
	}
}

bool SingleSectionDispatcher::Unsubscribe(Agent* _agent)
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

void SingleSectionDispatcher::Notify(const Event _event)
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

void SingleSectionDispatcher::EventsDispatcher()
{
	Event event(new EventImp);
	while(true)
	{
		m_events.Pop(event);
		Notify(event);
	}
}

void SingleSectionDispatcher::SendEvent(const Event _event)
{
	m_events.Push(_event);
}

}
