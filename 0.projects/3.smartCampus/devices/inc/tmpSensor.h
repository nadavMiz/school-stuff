#ifndef __TMP_SENSOR_H__
#define __TMP_SENSOR_H__

#include "agent.h"

class TmpSensor: public Agent
{
public:
	TmpSensor(const AgentData& _data, Hub* _hub);
	virtual ~TmpSensor();

protected:
	virtual void ParseConfig();
	virtual void SensorRoutine();
	virtual void SenseTempreture();

private:
	static void* threadFunc(TmpSensor* _sensor); //calls SenseTempreture
	
	TmpSensor(const TmpSensor& _sensor);
	TmpSensor& operator=(const TmpSensor& _sensor);
	
	Event CreateEvent(int type);

protected:
	/* data */
	int m_lower;
	int m_upper;
	unsigned int m_period;
	pthread_t m_thread;
};

#endif /* __TMP_SENSOR_H__ */

