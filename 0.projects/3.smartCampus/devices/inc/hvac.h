#ifndef __HVAC_H__
#define __HVAC_H__

#include "agent.h"

class AgentData;
class Hub;

class Hvac: public Agent
{
public:
	Hvac(const AgentData& _data, Hub* _hub);
	virtual ~Hvac();
	
	virtual bool IsRelevantEvent(const Event& _event) const;
	virtual void ReciveEvent(const Event& _event);

protected:
	bool IsInRange(int _tmp) const {return (_tmp < m_highTmp && _tmp > m_lowTmp);}
	
	virtual void FireHandler(int _type);
	virtual void TmpHandler(int _tmp);

protected:
	/* data */
	bool m_isFire;
	bool m_isActivated;
	int m_lowTmp;
	int m_highTmp;
	
private:
	Hvac(const Hvac& _hvac);
	Hvac& operator=(const Hvac& _hvac);
		
};

extern "C" Agent* CreateAgent(const string&, const AgentData& _data, Hub* _hub);

#endif /* __HVAC_H__ */

