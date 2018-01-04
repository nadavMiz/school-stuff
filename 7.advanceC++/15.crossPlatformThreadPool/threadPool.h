#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#ifdef __linux__
#include <tr1/memory>
#elif WIN32
#include <memory>
#endif/* os */
#include <vector>

#include "nPrioretyQueue.h"
#include "taskManager.h"
#include "task.h"
#include "taskImp.h"

namespace advcpp
{

typedef std::tr1::shared_ptr<Task> taskPtr;

class ThreadPool
{
public:
    ThreadPool(unsigned int _size = 10);
    ~ThreadPool();
    
    template <class T>
    void AddTask(std::tr1::shared_ptr<T> _obj, void(T::*Run)(void), std::size_t priority);
    
    void FullyGracefullShutDown();
    void GracefullShutDown();
    void BruteShutDown();
    
    void Resize(std::size_t _newSize);

public:
    nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& GetQueue(){return m_taskQueue;}

private:
    /* data */
    nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr> m_taskQueue;
    std::vector<TaskManager*> m_taskManagers;
    int m_isRunning;

private:
    void FlushThreads();
    void JoinAllThreads();
    
};

template <class T>
void ThreadPool::AddTask(std::tr1::shared_ptr<T> _obj, void(T::*Run)(void), std::size_t priority)
{
    if(!m_isRunning)
    {
        throw std::runtime_error("trying to add task to closed ThreadPool");
    }
    
    std::tr1::shared_ptr<Task> task(new TaskImp<T>(_obj, Run, priority));
    m_taskQueue.Push(task);
}

}
#endif /* THREAD_POOL_H */

