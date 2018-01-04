#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno
#include "Nmutex.h"

namespace advcpp
{

#ifdef __linux__

Nmutex::Nmutex()
{
    if(pthread_mutex_init(&m_mutex, 0) != 0)
    {
        throw std::runtime_error(strerror(errno));
    }
}
#elif defined WIN32

Nmutex::Nmutex()
{
	InitializeCriticalSection(&m_mutex);
}

#endif /* OS: Nmutex::Nmutex() */

#ifdef __linux__

Nmutex::~Nmutex()
{
     pthread_mutex_destroy(&m_mutex);
}

#elif defined WIN32

Nmutex::~Nmutex()
{
	DeleteCriticalSection(&m_mutex);
}

#endif /* OS Nmutex::~mutex() */

#ifdef __linux__

void Nmutex::Lock()
{
    if(pthread_mutex_lock(&m_mutex) != 0)
    {
        throw std::runtime_error(strerror(errno));
    }
}

#elif defined WIN32

void Nmutex::Lock()
{
	EnterCriticalSection(&m_mutex);
}

#endif /* OS: Nmutex::Lock() */

#ifdef __linux__

void Nmutex::Unlock()
{
    if(pthread_mutex_unlock(&m_mutex) != 0)
    {
        throw std::runtime_error(strerror(errno));
    }
}

#elif defined WIN32

void Nmutex::Unlock()
{
	LeaveCriticalSection(&m_mutex);
}

#endif /* OS:  Nmutex::Unlock()*/

#ifdef __linux__

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

#elif defined WIN32

bool Nmutex::TryLock()
{
	if(0 == TryEnterCriticalSection(&m_mutex))
	{
		return false;
	}
	else
	{
		return true;
	}
}

#endif /*OS: Nmutex::TryLock()*/

mutex_t* Nmutex::GetMutex()
{
	return &m_mutex;
}

}
