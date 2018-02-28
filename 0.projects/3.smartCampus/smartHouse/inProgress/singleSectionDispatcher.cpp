#include <new>
#include <tr1/functional>
#include <algorithm>

#include "agent.h"
#include "query.h"
#include "singleSectionDispatcher.h"
#include "event.h"
#include "eventImp.h"
#include "eventListener.h"
#include "communicator.h"
#include "vectorRegistrationTable.h"

namespace smartCampus
{

SingleSectionDispatcher::SingleSectionDispatcher():
	m_registrationTable(new VectorRegistrationTable) 
,	m_events(1000)
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

void SingleSectionDispatcher::AddEventListener(Agent* _agent)
{
	EventListener* eventListener = new EventListener(_agent);
	
	try
	{
		m_eventListeners.insert(std::pair<Agent*, EventListener* >(_agent, eventListener));
	}
	catch(const std::exception& _err)
	{
		delete eventListener;
		throw;
	}
}

void SingleSectionDispatcher::Subscribe(Agent* _agent, const Query& _query)
{	
	m_registrationTable->Insert(_agent, _query);
	
	try
	{
		map<Agent*, EventListener*>::iterator itr = m_eventListeners.find(_agent);
		if(m_eventListeners.end() == itr)
		{
			AddEventListener(_agent);
		}
	}
	catch(const std::exception& _err)
	{
		m_registrationTable->Remove(_agent, _query);
		throw;
	}
}

bool SingleSectionDispatcher::Unsubscribe(Agent* _agent)
{	
	map<Agent*, EventListener* >::iterator itr = m_eventListeners.find(_agent);
	if(itr ==  m_eventListeners.end())
	{
		return false;
	}
	
	delete itr->second;
	m_eventListeners.erase(itr);
	
	m_registrationTable->Remove(_agent);
	
	return true;
}

void SingleSectionDispatcher::Notify(const Event& _event)
{
	using namespace std::tr1::placeholders;
	
	std::vector<Agent*> agents = m_registrationTable->Find(_event);
	
	std::for_each(agents.begin(), agents.end(), std::tr1::bind(&SingleSectionDispatcher::NotifySingleEvent, this, _1, _event));
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

void SingleSectionDispatcher::NotifySingleEvent(Agent* _listner, const Event& _event)
{
	m_eventListeners[_listner]->SendEvent(_event);
}

}
