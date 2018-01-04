#include "eventImp.h"

EventImp::EventImp(const string& _type, const string& _room, unsigned int _floor):
			m_type(_type), m_room(_room), m_floor(_floor){}
			
EventImp::~EventImp(){}

EventImp::EventImp(EventImp& _event)
{
	m_type = _event.m_type;
	m_room = _event.m_room;
	m_floor = _event.m_floor;
}

EventImp& EventImp::operator=(EventImp& _event)
{
	m_type = _event.m_type;
	m_room = _event.m_room;
	m_floor = _event.m_floor;
	
	return *this;
}
