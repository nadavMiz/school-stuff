#ifndef __NCOND_H__
#define __NCOND_H__

#ifdef __linux__

#include <pthread.h>
typedef pthread_cond_t cond_t;

#elif defined WIN32

#include <Windows.h>
typedef PCONDITION_VARIABLE cond_t;

#endif

namespace advcpp
{

class Nmutex;

class Ncond
{
	public:
		Ncond();
		~Ncond();
		
		void Wait(Nmutex& _mutex);
		void Signal();
		void Broadcast();

	private:
		/* data */
		cond_t m_cond;
};

}

#endif /* __NCOND_H__ */

