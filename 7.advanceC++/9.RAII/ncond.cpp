#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno

#include "ncond.h"
#include "Nmutex.h"

namespace advcpp
{

Ncond::Ncond()
{
	if(pthread_cond_init(&m_cond, 0) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

Ncond::~Ncond()
{
	pthread_cond_destroy(&m_cond);
}

void Ncond::Wait(Nmutex& _mutex)
{
	if(pthread_cond_wait(&m_cond, _mutex.GetMutex()) != 0)
	{
		throw std::runtime_error(strerror(errno));
	} 
}

void Ncond::Signal()
{
	if(pthread_cond_signal(&m_cond) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

void Ncond::Broadcast()
{
	if(pthread_cond_broadcast(&m_cond) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

}
