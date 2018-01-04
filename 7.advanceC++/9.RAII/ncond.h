#ifndef __NCOND_H__
#define __NCOND_H__

#include <pthread.h>

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
		pthread_cond_t m_cond;
};

}

#endif /* __NCOND_H__ */

