#ifndef __NCOND_H__
#define __NCOND_H__

#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno
#include <pthread.h>
#include "Nmutex.h"

namespace advcpp
{

class Ncond
{
	public:
		Ncond();
		~Ncond();
		
		void Wait(Nmutex& _mutex);
		template < class Predicate >
		void Wait(Nmutex& _mutex, Predicate _pred);
		void Signal();
		void Broadcast();

	private:
		/* data */
		pthread_cond_t m_cond;
};

template < class Predicate >
void Ncond::Wait(Nmutex& _mutex, Predicate _isWait)
{
    while(_isWait)
    {
        if(pthread_cond_wait(&m_cond, _mutex.GetMutex()) != 0)
	    {
		    throw std::runtime_error(strerror(errno));
	    }
    }
}

}

#endif /* __NCOND_H__ */

