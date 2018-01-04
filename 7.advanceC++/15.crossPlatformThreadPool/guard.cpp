#include "guard.h"
namespace advcpp
{

Guard::Guard(Nmutex& _mutex): m_mutex(_mutex)
{
    _mutex.Lock();
}

Guard::~Guard()
{
    m_mutex.Unlock();
}

}
