#include <tr1/memory>

#include "threadPool.h"
#include "voidTask.h"

namespace advcpp
{

ThreadPool::ThreadPool(unsigned int _size): m_isRunning(true)
{
    for(unsigned int i = 0; i < _size; ++i)
    {
        m_taskManagers.push_back(new TaskManager(m_taskQueue));
    }
}

ThreadPool::~ThreadPool()
{
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        delete m_taskManagers[i];
    }
}

void ThreadPool::FlushThreads()
{
    std::tr1::shared_ptr<Task> voidTask(new VoidTask(0));
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskQueue.Push(voidTask);
    }
}

void ThreadPool::JoinAllThreads()
{
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskManagers[i]->JoinThread();
    }
}

void ThreadPool::FullyGracefullShutDown()
{
    if(__sync_bool_compare_and_swap(&m_isRunning, 0, 0))
    {
        throw std::runtime_error("trying to add task to closed ThreadPool");
    }
    
    __sync_bool_compare_and_swap(&m_isRunning, 1, 0);
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskManagers[i]->EndThreadFullySafely();
    }
    
    // enter void task to ensure that atlist one thread wakes up(he we wake up the rest)
    std::tr1::shared_ptr<Task> voidTask(new VoidTask(0));
    m_taskQueue.Push(voidTask);
    
    JoinAllThreads();
}

void ThreadPool::GracefullShutDown()
{
    if(__sync_bool_compare_and_swap(&m_isRunning, 0, 0))
    {
        throw std::runtime_error("trying close closed ThreadPool");
    }
    
    __sync_bool_compare_and_swap(&m_isRunning, 1, 0);
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskManagers[i]->EndThreadSafely();
    }
    
    FlushThreads();
    
    JoinAllThreads();
}

void ThreadPool::BruteShutDown()
{
    if(__sync_bool_compare_and_swap(&m_isRunning, 0, 0))
    {
        throw std::runtime_error("trying to close closed ThreadPool");
    }
    
    __sync_bool_compare_and_swap(&m_isRunning, 1, 0);
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskManagers[i]->CancelThread();
    }
    
    FlushThreads();
    
    JoinAllThreads();
}

void ThreadPool::Resize(std::size_t _newSize)
{
    if(__sync_bool_compare_and_swap(&m_isRunning, 0, 0))
    {
        throw std::runtime_error("trying to resize closed ThreadPool");
    }
    
    if(_newSize > m_taskManagers.size())
    {
        return;
    }
}

}
