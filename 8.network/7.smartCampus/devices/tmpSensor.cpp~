#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <sstream>
#include <iostream>
#include <new>
#include <sstream>

#include "hub.h"
#include "tmpSensor.h"
#include "agent.h"
#include "agentData.h"
#include "intEvent.h"

TmpSensor::TmpSensor(const AgentData& _data, Hub* _hub): Agent(_data, _hub)
{		
	ParseConfig();
	
	std::srand(std::time(0));
	
	if(pthread_create(&m_thread, 0, (void * (*)(void *))TmpSensor::threadFunc, this) != 0)
	{
		throw "thread error";
	}
}

void TmpSensor::ParseConfig()
{
	std::stringstream conf;
	conf.str(m_config);
	string type;
	
	for(int i = 0; i < 3; ++i)
	{
		conf >> type;
		if("lower:" == type)
		{
			conf >> m_lower;	
		}
		else if("upper:" == type)
		{
			conf >> m_upper;
		}
		else if("period:" == type)
		{
			conf >> m_period;
		}
	}
}

TmpSensor::~TmpSensor()
{
	pthread_cancel(m_thread);
	pthread_join(m_thread, 0);
}

void* TmpSensor::threadFunc(TmpSensor* _sensor)
{
	if(0 != _sensor)
	{
		_sensor->SensorRoutine();
	}
	
	pthread_exit(0);
}

void TmpSensor::SensorRoutine()
{
	while(true)
	{
		sleep(m_period);
		
		SenseTempreture();
	}
}

void TmpSensor::SenseTempreture()
{	
	int tmp = (std::rand() % (m_lower + m_upper)) +  m_lower;
	try
	{	
		Event event = CreateEvent(tmp);
		m_hub->SendEvent(event);
		
		stringstream str;
		str << "sensor: tmp is: " << tmp;
		m_log->write(str.str(), m_id);
	}
	catch(std::bad_alloc& _er)
	{
		m_log->write("can't send event", m_id);
		return;
	}
}

Event TmpSensor::CreateEvent(int _tmp)
{
	IntEvent* payload = new IntEvent(_tmp);
	payload->m_type = "tmp";
	payload->m_room = m_room;
	payload->m_floor = m_floor;
	
	return Event(payload);
}

extern "C" Agent* CreateAgent(const string& _deviceName, const AgentData& _data, Hub* _hub)
{
	return new TmpSensor(_data, _hub);
}
