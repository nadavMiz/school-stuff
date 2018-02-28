#ifndef __Guard_H__
#define __Guard_H__

#include <pthread.h>
#include <exception>

class Guard
{
	public:
		Guard(const pthread_mutex_t* _mutex);
		virtual ~Guard();

	private:
		/* data */
		pthread_mutex_t* m_mutex;
};

#endif /* __Guard_H__ */

