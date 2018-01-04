#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno

#include "ncond.h"
#include "Nmutex.h"

namespace advcpp
{

#ifdef __linux__
Ncond::Ncond()
{
	if(pthread_cond_init(&m_cond, 0) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

#elif defined WIN32

Ncond::Ncond()
{
	InitializeConditionVariable(m_cond);
}

#endif

#ifdef __linux__

Ncond::~Ncond()
{
	pthread_cond_destroy(&m_cond);
}

#elif defined WIN32

Ncond::~Ncond()
{}

#endif

#ifdef __linux__

void Ncond::Wait(Nmutex& _mutex)
{
	if(pthread_cond_wait(&m_cond, _mutex.GetMutex()) != 0)
	{
		throw std::runtime_error(strerror(errno));
	} 
}

#elif defined WIN32
void Ncond::Wait(Nmutex& _mutex)
{
	SleepConditionVariableCS(m_cond, *(_mutex.GetMutex()), 0);
}
#endif

#ifdef __linux__

void Ncond::Signal()
{
	if(pthread_cond_signal(&m_cond) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

#elif defined WIN32

void Ncond::Signal()
{
	WakeConditionVariable(m_cond);
}

#endif

#ifdef __linux__

void Ncond::Broadcast()
{
	if(pthread_cond_broadcast(&m_cond) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

#elif defined WIN32

void Ncond::Broadcast()
{
	WakeAllConditionVariable(m_cond);
}

#endif

}
