#include <iostream>
#include <pthread.h>
#include <exception>
#include <unistd.h>

#include "agent.h"
#include "fireSensor.h"
#include "intEvent.h"
#include "hub.h"
#include "nlog.h"


FireSensor::FireSensor(const AgentData& _data, Hub* _hub): Agent(_data, _hub)
{
	m_isFire = false;
	
	_hub->Subscribe(this);
	
	if(0 != pthread_create(&m_thread, 0, (void* (*) (void*))FireSensorRoutine, this))
	{
		throw new std::exception;
	}
}

FireSensor::~FireSensor()
{	
	pthread_cancel(m_thread);
	pthread_join(m_thread, 0);
}

void* FireSensor::FireSensorRoutine(FireSensor* _sensor)
{
	if(0 != _sensor)
	{
		_sensor->SenseFire();
	}
	
	pthread_exit(0);
}

void FireSensor::SenseFire()
{
	while(true)
	{
		sleep(3);
		
		m_isFire = !m_isFire;
	
		if(m_isFire)
		{
			StartFire();
		}
		else
		{
			PutOutFire();
		}
	}
}

void FireSensor::StartFire()
{	
	try
	{
		Event event = CreateEvent(1);
		m_hub->SendEvent(event);
		
		m_log->write("fire! fire!", m_id);
	}
	catch(std::bad_alloc& _er)
	{
		m_log->write("cant write event", m_id);
		return;
	}
}

void FireSensor::PutOutFire()
{
	
	try
	{
		Event event = CreateEvent(0);
		m_hub->SendEvent(event);
		
		m_log->write("fire was put out", m_id);
	}
	catch(std::bad_alloc& _er)
	{
		m_log->write("cant write event", m_id);
		return;
	}
}

Event FireSensor::CreateEvent(int type)
{
	IntEvent* payload = new IntEvent(type);
	payload->m_type = "fire";
	payload->m_room = m_room;
	payload->m_floor = m_floor;
	
	return Event(payload);
}
