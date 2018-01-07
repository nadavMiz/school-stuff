#include <iostream>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "agent.h"
#include "signalFireSensor.h"
#include "intEvent.h"
#include "hub.h"
#include "nlog.h"

bool SignalFireSensor::IsFirstSignalFireSensor = true;
sig_atomic_t SignalFireSensor::m_isSignaled = 0;

void SignalFireSensor::SignalHandler(int _param)
{
	++m_isSignaled;
}

SignalFireSensor::SignalFireSensor(const AgentData& _data, Hub* _hub): Agent(_data, _hub)
{
	if(IsFirstSignalFireSensor)
	{
		signal(SIGUSR2, SignalHandler);
		IsFirstSignalFireSensor = false;
	}
	
	m_isFire = false;
	_hub->Subscribe(this);
	
	if(0 != pthread_create(&m_thread, 0, (void* (*) (void*))SignalFireSensorRoutine, this))
	{
		throw new std::exception;
	}
}

void* SignalFireSensor::SignalFireSensorRoutine(SignalFireSensor* _sensor)
{
	if(0 != _sensor)
	{
		_sensor->SenseFire();
	}
	
	pthread_exit(0);
}

void SignalFireSensor::SenseFire()
{
	while(true)
	{
		while(!m_isSignaled)
		{
			sleep(1);
		}
		--m_isSignaled;
		
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

void SignalFireSensor::StartFire()
{	
	try
	{
		Event event = CreateEvent(1);
		m_hub->SendEvent(event);
		
		m_log->write("fire! fire!", m_id);
	}
	catch(std::exception& _er)
	{
		m_log->write("cant send msg", m_id);
		return;
	}
	
}

void SignalFireSensor::PutOutFire()
{	
	try
	{
		Event event = CreateEvent(0);
		m_hub->SendEvent(event);
		
		m_log->write("fire was put out", m_id);
	}
	catch(std::bad_alloc& _er)
	{
		m_log->write("cant send msg", m_id);
		return;
	}
}

Event SignalFireSensor::CreateEvent(int type)
{
	IntEvent* payload = new IntEvent(type);
	payload->m_type = "fire";
	payload->m_room = m_room;
	payload->m_floor = m_floor;
	
	return Event(payload);
}
