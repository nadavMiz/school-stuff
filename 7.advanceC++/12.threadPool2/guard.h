#ifndef GUARD_H
#define GUARD_H

#include <pthread.h>

#include "Nmutex.h"

namespace advcpp
{

class Guard
{
public:
    Guard(Nmutex& _mutex);
    ~Guard();

private:
    /* data */
    Nmutex& m_mutex;
    
private:
    Guard(const Guard&);
    Guard& operator=(const Guard&);
};

}
#endif /* GUARD_H */

