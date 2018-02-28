#ifndef __FIRE_SENSOR_H__
#define __FIRE_SENSOR_H__

#include <pthread.h>
#include <signal.h>

#include "agent.h"
#include "event.h"

class FireSensor: public Agent
{
public:
	FireSensor(const AgentData& _data, Hub* _hub);
	virtual ~FireSensor();
	
private:
	
	static void SignalHandler(int _param);
	
	static void* FireSensorRoutine(FireSensor* _sensor); //calls SenseFire
	
	virtual void SenseFire();
	virtual void StartFire();
	virtual void PutOutFire();
	
	FireSensor(const FireSensor& _sensor);
	FireSensor& operator=(const FireSensor* _sensor);
	
private:
	Event CreateEvent(int type);

private:
	/* data */
	bool m_isFire;
	pthread_t m_thread;
};

#endif /* __FIRE_SENSOR_H__ */

