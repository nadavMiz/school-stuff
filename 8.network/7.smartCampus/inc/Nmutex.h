#ifndef Nmutex_H
#define Nmutex_H

#ifdef __linux__
#include <pthread.h>

typedef pthread_mutex_t mutex_t;

#elif defined _WIN32
#include <windows.h>

typedef LPCRITICAL_SECTION mutex_t;


#endif /* __OS__ */

class Ncond;

namespace advcpp
{

class Nmutex
{

friend class Ncond;

public:
    Nmutex();
    ~Nmutex();
    
    void Lock();
    void Unlock();
    bool TryLock();

private:
    /* data */
    mutex_t m_mutex;
    
private:
    Nmutex(const Nmutex& _nmutex);
    Nmutex& operator=(const Nmutex& _nmutex);
    
    mutex_t* GetMutex();
        
};

}

#endif /* Nmutex_H */

