#ifndef __EVENT_H__
#define __EVENT_H__

#include <pthread.h>
#include <string>

#include "eventImp.h"

using namespace std;

class Payload;

class Event
{
public:
	Event(const EventImp* _eventImp);
	~Event();
	Event(const Event& _event);
	Event& operator=(const Event& _event);
	
	const EventImp* GetEventImp() const;
	const EventImp& operator*() const;
	const EventImp* operator->() const;
	EventImp& operator*();
	EventImp* operator->();

private:
	void CopyEvent(const Event& _event);
	void DecreaseCopy();

private:
	/* data */
	EventImp* m_eventImp;
	unsigned int* m_NumCopies;
	pthread_mutex_t* m_mutex;
};

inline const EventImp* Event::GetEventImp() const
{
	return m_eventImp;
}

inline const EventImp& Event::operator*() const
{
	return *m_eventImp;
}

inline const EventImp* Event::operator->() const
{
	return m_eventImp;
}

inline EventImp& Event::operator*()
{
	return *m_eventImp;
}

inline EventImp* Event::operator->()
{
	return m_eventImp;
}

#endif /* __EVENT_H__ */

