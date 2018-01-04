#ifndef Nmutex_H
#define Nmutex_H

#include <pthread.h>

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
    pthread_mutex_t m_mutex;
    
private:
    Nmutex(const Nmutex& _nmutex);
    Nmutex& operator=(const Nmutex& _nmutex);
    
    pthread_mutex_t* GetMutex();
        
};

}

#endif /* Nmutex_H */

