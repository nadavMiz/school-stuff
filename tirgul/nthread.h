#ifndef __NTHREAD_H__
#define __NTHREAD_H__

#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno
#include <cstdlib> //abort

#ifdef __linux__
#include <tr1/memory> //shared_ptr
#include <tr1/functional> //function and bind

#elif defined WIN32
#include <memory> //shared_ptr

#endif /* os */

#include "atomicOperations.h"

#ifdef __linux__

#include <pthread.h>

typedef pthread_t thread_t;

#elif defined WIN32

typedef HANDLE thread_t;

#include <Windows.h>

#endif /* OS */

namespace advcpp
{

namespace sync
{

class Nthread
{
public:
	template<class Function, class Context>
	Nthread(Function _func, Context& _context);
	~Nthread();

	void Join();
	void Detach();
	void Cancel();

private:
#ifdef __linux__
	static void* RunThread(Nthread* _nthread);
#elif defined WIN32
	static DWORD RunThread(Nthread<T>* _nthread);
#endif

private:
	/* data */
	std::tr1::function<void()> m_threadFunc;
	pthread_t m_thread;
	int m_isSafeExit;
};

#ifdef __linux__

template<class Function, class Context>
Nthread::Nthread(Function _func, Context& _context):
    m_threadFunc(std::tr1::bind(_func, _context))
{
	if(pthread_create(&m_thread, 0, (void*(*)(void *))RunThread, this) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

#elif defined WIN32

template<class T>
Nthread<T>::Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void)): 
    m_obj(_obj)
,	m_runFunc(Func)
,   m_isSafeExit(false)
{
	
	m_thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RunThread, this, 0, 0);
	
	if(0 == m_thread)
	{
		throw std::runtime_error("thread creation failed");
	}
}

template<class T>
Nthread<T>::Nthread(void(*Func)(T*), T* _context):
    m_obj(_obj)
,	m_runFunc(Func)
,   m_isSafeExit(false)
{
	
	m_thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Func, _context, 0, 0);
	
	if(0 == m_thread)
	{
		throw std::runtime_error("thread creation failed");
	}
}

#endif /* OS: Nthread<T>::Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void))*/

Nthread::~Nthread()
{
    if(!m_isSafeExit)
    {
        std::abort();
    }
}

#ifdef __linux__

void* Nthread::RunThread(Nthread* _nthread)
{
	_nthread->m_threadFunc();
	
	return 0;
}

#elif defined WIN32

template<class T>
DWORD Nthread<T>::RunThread(Nthread<T>* _nthread)
{
	((*_nthread->m_obj).*(_nthread->m_runFunc))();
	
	return 0;
}

#endif

#ifdef __linux__

void Nthread::Join()
{
	if(pthread_join(m_thread, 0) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#elif defined WIN32

template<class T>
void Nthread<T>::Join()
{
	WaitForSingleObject(m_thread, INFINITE);

	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#endif

#ifdef __linux__

void Nthread::Detach()
{
	if(pthread_detach(m_thread) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#elif defined WIN32

template<class T>
void Nthread<T>::Detach()
{
	if(0 == CloseHandle(m_thread))
	{
		throw std::runtime_error("cant close thread");
	}
	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#endif

#ifdef __linux__

void Nthread::Cancel()
{
    pthread_cancel(m_thread);
}
#elif defined WIN32

#endif /* os: Nthread<T>::Cancel()*/

}

}

#endif /* __NTHREAD_H__ */

