#ifndef __NTHREAD_H__
#define __NTHREAD_H__

#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno
#include <cstdlib> //abort

#ifdef __linux__
#include <tr1/memory> //shared_ptr

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

template<class T>
class Nthread
{
public:
	Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void));
	Nthread(void(*Func)(T*), T* _context);
	~Nthread();

	void Join();
	void Detach();
	void Cancel();

private:
#ifdef __linux__
	static void* RunThread(Nthread<T>* _nthread);
#elif defined WIN32
	static DWORD RunThread(Nthread<T>* _nthread);
#endif

private:
	union RunFunc
	{
		void(T::*member)(void);
		void(*global)(std::tr1::shared_ptr<T>);
	};

private:
	/* data */
	thread_t m_thread;
	std::tr1::shared_ptr<T> m_obj;
	void(T::*m_runFunc)(void);
	int m_isSafeExit;
};

#ifdef __linux__

template<class T>
Nthread<T>::Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void)): 
    m_obj(_obj)
,	m_runFunc(Func)
,   m_isSafeExit(false)
{
	if(pthread_create(&m_thread, 0, (void*(*)(void *))RunThread, this) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

template<class T>
Nthread<T>::Nthread(void(*Func)(T*), T* _context):
	m_runFunc(Func)
,   m_isSafeExit(false)
{
	if(pthread_create(&m_thread, 0, (void*(*)(void *))Func, _context) != 0)
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

template<class T>
Nthread<T>::~Nthread()
{
    if(!m_isSafeExit)
    {
        std::abort();
    }
}

#ifdef __linux__

template<class T>
void* Nthread<T>::RunThread(Nthread<T>* _nthread)
{
	((*_nthread->m_obj).*(_nthread->m_runFunc))();
	
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

template<class T>
void Nthread<T>::Join()
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

template<class T>
void Nthread<T>::Detach()
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
		throw std::runtime_error("cant clos thread");
	}
	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#endif

#ifdef __linux__

template<class T>
void Nthread<T>::Cancel()
{
    pthread_cancel(m_thread);
}
#elif defined WIN32

#endif /* os: Nthread<T>::Cancel()*/

}

}

#endif /* __NTHREAD_H__ */

