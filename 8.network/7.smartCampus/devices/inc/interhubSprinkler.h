#ifndef __INTERHUB_SPRINKLER_H__
#define __INTERHUB_SPRINKLER_H__

#include "sprinkler.h"
#include "hub.h"

class InterHubSprinkler: public Sprinkler
{
public:
	InterHubSprinkler(const AgentData& _data, Hub* _hub): Sprinkler(_data, _hub)
	{
		m_hub->Unsubscribe(this);
		
		smartCampus::Query query;
		query.m_topic = "fire";
		query.m_floor = "5";
		query.m_section = "mainHub";
		
		
		_hub->Subscribe(this, query, "otherHub");
	}
	
	~InterHubSprinkler()
	{	
		m_hub->Unsubscribe(this, smartCampus::Query(), "otherHub");
	}

private:
	/* data */
};

#endif /* __INTERHUB_SPRINKLER_H__ */

