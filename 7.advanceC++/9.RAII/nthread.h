#ifndef __NTHREAD_H__
#define __NTHREAD_H__

#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno

#include "threadable.h"

namespace advcpp
{

class Nthread
{
public:
	Nthread(Threadable& _obj);

	void Join();
	void Detach();

private:
	static void* RunThread(Threadable* _obj);

private:
	/* data */
	pthread_t m_thread;
};

}

#endif /* __NTHREAD_H__ */

