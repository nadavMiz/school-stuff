#include <iostream>
#include <sstream>

#include "hvac.h"
#include "event.h"
#include "intEvent.h"
#include "hub.h"
#include "agentData.h"


Hvac::Hvac(const AgentData& _data, Hub* _hub): Agent(_data, _hub)
{
	m_isActivated = false;
	m_isFire = false;
	
	std::stringstream conf;
	conf.str(m_config);
	string type;
	
	for(int i = 0; i < 2; ++i)
	{
		conf >> type;
		if("low:" == type)
		{
			conf >> m_lowTmp;	
		}
		else if("high:" == type)
		{
			conf >> m_highTmp;
		}
	}
	
	m_hub->Subscribe(this);
}

Hvac::~Hvac()
{
	m_hub->Unsubscribe(this);
}

bool Hvac::IsRelevantEvent(const Event& _event) const
{
	return ( "tmp" == _event.GetType() || "fire" == _event.GetType());
}

void Hvac::ReciveEvent(const Event& _event)
{
	IntEvent* payload = (IntEvent*)_event.GetEventImp();
	
	if("fire" == _event.GetType())
	{
		FireHandler(payload->GetData());
	}
	else if(!m_isFire && ("tmp" == _event.GetType()))
	{
		TmpHandler(payload->GetData());
	}
}

void Hvac::FireHandler(int _type)
{
	if(0 == _type)
	{
		m_isFire = false;
	}
	else
	{
		m_isFire = true;
		m_isActivated = false;
		m_log->write("fire detected. turning off HVAC", m_id);
	}
}

void Hvac::TmpHandler(int _tmp)
{
	if(m_isActivated && IsInRange(_tmp))
	{
		m_isActivated = false;
		
		stringstream str;
		str << "tmp is: " << _tmp << ". turning off HVAC";
		m_log->write(str.str(), m_id);
	}
	
	else if(!m_isActivated && !IsInRange(_tmp))
	{
		m_isActivated = true;
		
		stringstream str;
		str << "tmp is: " << _tmp << ". turning on HVAC";
		m_log->write(str.str(), m_id);
	}
}
