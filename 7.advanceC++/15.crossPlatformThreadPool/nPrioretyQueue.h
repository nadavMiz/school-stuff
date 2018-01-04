#ifndef N_PRIORETY_QUEUE_H
#define N_PRIORETY_QUEUE_H

#include <vector>
#include <queue>

#include "guard.h"
#include "Nmutex.h"
#include "ncond.h"

namespace advcpp
{

template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
class nPrioretyQueue
{
public:
    //nPrioretyQueue(); default CTOR
    //~nPrioretyQueue(); default DTOR
    
    std::size_t Size();
    void Push(const T& _item);
    void Pop(T& _item);
    bool TryPop(T& _item);

private:
    /* data */
    std::priority_queue<T, Container, Compare> m_queue;
    Nmutex m_mutex;
    Ncond m_cond;
};

template <class T, class Container,  class Compare >
void nPrioretyQueue<T, Container, Compare>::Push(const T& _item)
{
    {
        Guard quard(m_mutex);
        m_queue.push(_item);
        
        m_cond.Signal();
    }
}

template <class T, class Container,  class Compare >
void nPrioretyQueue<T, Container, Compare>::Pop(T& _item)
{
    Guard guard(m_mutex);
    
    while(m_queue.empty())
    {
        m_cond.Wait(m_mutex);
    }
    
    _item = m_queue.top();
    m_queue.pop();
        
}

template <class T, class Container,  class Compare >
bool nPrioretyQueue<T, Container, Compare>::TryPop(T& _item)
{
    Guard guard(m_mutex);
    
    if(m_queue.empty())
    {
        return false;
    }
    _item = m_queue.top();
    m_queue.pop();
    
    return true;
}

template <class T, class Container,  class Compare >
std::size_t nPrioretyQueue<T, Container, Compare>::Size()
{
    {
        Guard nadav(m_mutex);
        return m_queue.size();
    }
}

}
#endif /* N_PRIORETY_QUEUE_H */

