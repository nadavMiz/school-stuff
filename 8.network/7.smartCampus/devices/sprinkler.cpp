#include "sprinkler.h"
#include "hub.h"
#include "intEvent.h"
#include "nlog.h"
#include "query.h"

Sprinkler::Sprinkler(const AgentData& _data, Hub* _hub): Agent(_data, _hub), m_isActive(false)
{
	m_hub->Subscribe(this, (smartCampus::Query()));
}

Sprinkler::~Sprinkler()
{
	m_hub->Unsubscribe(this);
}

bool Sprinkler::IsRelevantEvent(const Event& _event) const
{
	return ("fire" == _event->m_type);
}

void Sprinkler::ReciveEvent(const Event& _event)
{
	int type = ((IntEvent*)_event.GetEventImp())->GetData();

	if(0 == type && m_isActive)
	{
		m_isActive = false;
		m_log->write("fire put out. turning off sprinkler", m_id);
	}
	else if(0 != type && !m_isActive)
	{
		m_isActive = true;
		m_log->write("fire detected. starting sprinkler", m_id);
	}
}
