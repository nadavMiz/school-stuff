#include <tr1/memory>

#include "guard.h"
#include "taskManager.h"

namespace advcpp
{

TaskManager::TaskManager(nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& _queue):
     m_taskQueue(_queue)
,    m_isRunning(true)
,    m_thread(*this){}

TaskManager::~TaskManager()
{
    EndThread();
    
    m_thread.Join();
}

bool TaskManager::IsRunning()
{
    Guard guard(m_mutex);
    return m_isRunning;
}

void TaskManager::EndThread()
{
    Guard guard(m_mutex);
    m_isRunning = false;
}

void TaskManager::RunThread()
{
    std::tr1::shared_ptr<Task> task(new Task(0, 1));
    
    while(IsRunning())
    {
        task = m_taskQueue.Pop();
        task->RunThread();
    }
}

}
