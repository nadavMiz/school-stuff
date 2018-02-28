#include <pthread.h>

#include "event.h"
#include "eventImp.h"

Event::Event(const EventImp* _eventImp)
{	
	m_eventImp = (EventImp*)_eventImp;

	m_mutex = new pthread_mutex_t;
	if(pthread_mutex_init(m_mutex, 0) < 0)
	{
		throw "mutex init";
	}
	
	m_NumCopies = new unsigned int;
	*m_NumCopies = 1;
}

Event::~Event()
{
	DecreaseCopy();
}

void Event::CopyEvent(const Event& _event)
{	
	m_eventImp = _event.m_eventImp;
	m_mutex = _event.m_mutex;
	m_NumCopies = _event.m_NumCopies;
	
	pthread_mutex_lock(m_mutex);
	++(*_event.m_NumCopies);
	pthread_mutex_unlock(m_mutex);
}

Event::Event(const Event& _event)
{
	CopyEvent(_event);
}

Event& Event::operator=(const Event& _event)
{
	if(m_eventImp == _event.m_eventImp)
	{
		return *this;
	}
	
	DecreaseCopy();
	
	// copy the other event and increase its counter
	CopyEvent(_event);
	
	return *this;
}

void Event::DecreaseCopy()
{
	bool isLastEvent = false;
	
	pthread_mutex_lock(m_mutex);
	--(*m_NumCopies);
	if((*m_NumCopies) == 0)
	{
		isLastEvent = true;
	}
	pthread_mutex_unlock(m_mutex);
	
	if(isLastEvent)
	{
		pthread_mutex_destroy(m_mutex);
		delete m_mutex;
		delete m_NumCopies;
		delete m_eventImp;
	}
}

