#include "threadPool.h"

namespace advcpp
{

ThreadPool::ThreadPool(unsigned int _size)
{
    for(unsigned int i = 0; i < _size; ++i)
    {
        m_taskManagers.push_back(new TaskManager(m_taskQueue));
    }
}

ThreadPool::~ThreadPool()
{
    ShutDown();
}

void ThreadPool::AddTask(taskPtr _task)
{
    m_taskQueue.Push(_task);
}

void ThreadPool::ShutDown()
{
    ThreadPool::VoidTask voidTask;
    std::tr1::shared_ptr<Task> endThreadTask(new Task(&voidTask));
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskManagers[i]->EndThread();
    }
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        m_taskQueue.Push(endThreadTask);
    }
    for(unsigned int i = 0; i < m_taskManagers.size(); ++i)
    {
        delete m_taskManagers[i];
    }
}

}
