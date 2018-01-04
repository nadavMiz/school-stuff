#ifndef __NTHREAD_H__
#define __NTHREAD_H__

#include <stdexcept> //runtime_error
#include <cstring> //stderror
#include <errno.h> //errno
#include <cstdlib> //abort

#ifdef __LINUX__

#include <pthread.h>

typedef pthread_t thread_t;

#else ifdef WIN32

typedef HANDLE thread_t;

#include <Windows.h>

#endif /* OS */

namespace advcpp
{

template<class T>
class Nthread
{
public:
	Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void));
	~Nthread();

	void Join();
	void Detach();
	void Cancel();

private:
#ifdef __LINUX__
	static void* RunThread(Nthread<T>* _nthread);
#else ifdef WIN32
	static DWORD RunThread(Nthread<T>* _nthread);
#endif

private:
	/* data */
	thread_t m_thread;
	std::tr1::shared_ptr<T> m_obj;
	void(T::*m_runFunc)(void);
	bool m_isSafeExit;
};

#ifdef __LINUX__

template<class T>
Nthread<T>::Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void)): 
    m_obj(_obj)
,   m_runFunc(Func)
,   m_isSafeExit(false)
{
	if(pthread_create(&m_thread, 0, (void*(*)(void *))RunThread, this) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
}

#else ifdef WIN32

template<class T>
Nthread<T>::Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void)): 
    m_obj(_obj)
,   m_runFunc(Func)
,   m_isSafeExit(false)
{
	m_thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RunThread, this, 0, 0)
	
	if(0 == m_thread)
	{
		throw std::runtime_error("thread creation failed");
	}
}

#endif /* OS: Nthread<T>::Nthread(std::tr1::shared_ptr<T> _obj, void(T::*Func)(void))*/

template<class T>
Nthread<T>::~Nthread()
{
    if(!m_isSafeExit))
    {
        std::abort();
    }
}

#ifdef __LINUX__

template<class T>
void* Nthread<T>::RunThread(Nthread<T>* _nthread)
{
	((*_nthread->m_obj).*(_nthread->m_runFunc))();
	
	return 0;
}

#else ifdef WIN32

template<class T>
DWORD Nthread<T>::RunThread(Nthread<T>* _nthread)
{
	((*_nthread->m_obj).*(_nthread->m_runFunc))();
	
	return 0;
}

#endif

#ifdef __LINUX__

template<class T>
void Nthread<T>::Join()
{
	if(pthread_join(m_thread, 0) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#else ifdef WIN32

template<class T>
void Nthread<T>::Join()
{
	WaitForSingleObject(m_thread, INFINITE);

	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#endif

#ifdef __LINUX__

template<class T>
void Nthread<T>::Detach()
{
	if(pthread_detach(m_thread) != 0)
	{
		throw std::runtime_error(strerror(errno));
	}
	AtomicCompareAndExchange(m_isSafeExit, 0, 1);
}

#else ifdef WIN32

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

template<class T>
void Nthread<T>::Cancel()
{
    pthread_cancel(m_thread);
}

}

#endif /* __NTHREAD_H__ */

