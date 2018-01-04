#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "myTime.h"

#define THOUSAND 1000
#define MILLION 1000000
#define BILION 1000000000


struct Time
{
	struct timespec	m_time;
}; 

Time* TimeCreate(int _milliSecs)
{
	Time* timePtr = NULL;
	
	timePtr = malloc(sizeof(Time));
	if(NULL == timePtr)
	{
		return NULL;
	}
	
	timePtr->m_time.tv_sec = _milliSecs / 1000;
	timePtr->m_time.tv_nsec = (_milliSecs % 1000) * MILLION;
	return timePtr;
}

void TimeGetCurrent(const clockid_t _clockID, Time* _time)
{
	if(NULL == _time)
	{
		return;
	}
	
	clock_gettime(_clockID, &(_time->m_time));
}

void TimeDestroy(Time* _time)
{
	free(_time);
}

int TimeLessThan(const Time* _a, const Time* _b)
{
	if(_a->m_time.tv_sec == _b->m_time.tv_sec)
	{
		return (_a->m_time.tv_nsec < _b->m_time.tv_nsec);
	}
	return (_a->m_time.tv_sec < _b->m_time.tv_sec);
}

void TimeSleepUntil(const Time* _taskTime, clockid_t _clockID)
{
	Time* currentTime;
	long timeDiff;
	
	currentTime = TimeCreate(0);
	TimeGetCurrent(_clockID, currentTime);
	
	timeDiff = (long)difftime(_taskTime->m_time.tv_sec, currentTime->m_time.tv_sec) * MILLION;
	timeDiff += (_taskTime->m_time.tv_nsec - currentTime->m_time.tv_nsec) / THOUSAND;
	
	if(timeDiff > 0)
	{
		usleep((unsigned int)timeDiff);
	}
	
	TimeDestroy(currentTime);
}

void TimeAdd(Time* _result, const Time* _added)
{
	_result->m_time.tv_sec += _added->m_time.tv_sec;
	_result->m_time.tv_nsec += _added->m_time.tv_nsec;
	_result->m_time.tv_sec += _result->m_time.tv_nsec / BILION;
	_result->m_time.tv_nsec %= BILION;
}

/*------------------testing functions----------------*/

long getMiliSec(Time* _time)
{
	return _time->m_time.tv_nsec;
}

time_t  GetSeconds(Time* _time)
{
	return _time->m_time.tv_sec;
}
