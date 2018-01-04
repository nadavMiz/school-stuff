#ifndef __SIGNAL_FIRE_SENSOR_H__
#define __SIGNAL_FIRE_SENSOR_H__

#include <pthread.h>
#include <signal.h>
#include <vector>

#include "agent.h"

class SignalFireSensor: public Agent
{
public:
	SignalFireSensor(const AgentData& _data, Hub* _hub);
	virtual ~SignalFireSensor() {}
	
private:
	
	static void SignalHandler(int _param);
	
	static void* SignalFireSensorRoutine(SignalFireSensor* _sensor); //calls SenseFire
	
	virtual void SenseFire();
	virtual void StartFire();
	virtual void PutOutFire();
	Event CreateEvent(int type);
	
	SignalFireSensor(const SignalFireSensor& _sensor);
	SignalFireSensor& operator=(const SignalFireSensor* _sensor);
	
private:
	/* data */
	bool m_isFire;
	pthread_t m_thread;
	
	static bool IsFirstSignalFireSensor;
	static sig_atomic_t m_isSignaled;
};

#endif /* __SIGNAL_FIRE_SENSOR_H__ */

