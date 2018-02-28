#include "guard.h"

Guard::Guard(const pthread_mutex_t* _mutex)
{
	if(0 == _mutex)
	{
		throw new std::exception;
	}
	
	m_mutex = (pthread_mutex_t*)_mutex;
	
	if(0 != pthread_mutex_lock(m_mutex))
	{
		throw new std::exception;
	}
}

Guard::~Guard()
{
	pthread_mutex_unlock(m_mutex);
}
