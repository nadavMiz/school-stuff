#ifndef __SPRINKLER_H__
#define __SPRINKLER_H__

#include <iostream>

#include "agent.h"

class Sprinkler: public Agent
{
public:
	Sprinkler(const AgentData& _data, Hub* _hub);
	virtual ~Sprinkler();
	
	virtual bool IsRelevantEvent(const Event& _event) const;
	virtual void ReciveEvent(const Event& _event);

private:
	/* data */
	bool m_isActive;
	
private:
	Sprinkler(const Sprinkler& _sprinkler);
	Sprinkler& operator=(const Sprinkler& _sprinkler);
};

#endif /* __SPRINKLER_H__ */

