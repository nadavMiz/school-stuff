#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno
#include "Nmutex.h"

namespace advcpp
{

Nmutex::Nmutex()
{
    if(pthread_mutex_init(&m_mutex, 0) != 0)
    {
        throw std::runtime_error(strerror(errno));
    }
}

Nmutex::~Nmutex()
{
     pthread_mutex_destroy(&m_mutex);
}

void Nmutex::Lock()
{
    if(pthread_mutex_lock(&m_mutex) != 0)
    {
        throw std::runtime_error(strerror(errno));
    }
}

void Nmutex::Unlock()
{
    if(pthread_mutex_unlock(&m_mutex) != 0)
    {
        throw std::runtime_error(strerror(errno));
    }
}

bool Nmutex::TryLock()
{
	if(pthread_mutex_trylock(&m_mutex) != 0)
	{
		if(EBUSY == errno)
		{
			return false;
		}
		else
		{
			throw std::runtime_error(strerror(errno));
		}
	}
	
	return true;
}

pthread_mutex_t* Nmutex::GetMutex()
{
	return &m_mutex;
}

}
