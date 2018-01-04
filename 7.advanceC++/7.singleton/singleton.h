#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "Guard.h"
#include <pthread.h>
#include <tr1/memory>

namespace advcpp

{
template <class T>
class Singleton
{
public:

	static Singleton* createObj ();

protected:

private: // data member;

	static std::tr1::shared_ptr<T> m_singleton;
	static pthread_mutex_t m_mutex;
    static volatile int m_flag;

private:

	Singleton<T> ();
	Singleton (const Singleton& _src);
	Singleton& operator=(const Singleton& _src);

};

template <class T>
pthread_mutex_t Singleton<T>::m_mutex = PTHREAD_MUTEX_INITIALIZER;


template <class T>
volatile int Singleton<T>::m_flag = 0;

template <class T>
std::tr1::shared_ptr<T> Singleton<T>::m_singleton;


template <class T>

Singleton<T>* Singleton<T>::createObj()

{
    if (!__sync_bool_compare_and_swap (&m_singleton, 0, 0))
    {
        Guard g(m_mutex);
        if (!m_flag)
        {
       	    m_singleton = std::tr1::shared_ptr<T>(new T);
       	    __sync_fetch_and_add(&m_flag,1);
		}
    }
    return m_singleton;
}



class Super_Dog

{

public:
    Super_Dog(){m_counter++;}
    Super_Dog (Super_Dog& _src);
    Super_Dog&operator=(const Super_Dog& _src);

private:

    /* data */
   int m_counter;

};

}//end of namespace advcpp 

#endif /* __SINGELTON_H */
