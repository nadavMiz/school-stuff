#include "nthread.h"

namespace advcpp
{

Nthread::Nthread(Threadable& _obj)
{
	if(pthread_create(&m_thread, 0, (void*(*)(void *))RunThread, &_obj) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

void* Nthread::RunThread(Threadable* _obj)
{
	_obj->RunThread();
	
	return 0;
}

void Nthread::Join()
{
	if(pthread_join(m_thread, 0) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

void Nthread::Detach()
{
	if(pthread_detach(m_thread) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

}
