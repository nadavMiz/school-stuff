#include <tr1/memory>

#include "guard.h"
#include "taskManager.h"
#include "voidTask.h"

namespace advcpp
{

TaskManager::TaskManager(nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& _queue):
     m_taskManager(new TaskManager::threadRunner(_queue))
,    m_thread(m_taskManager, &TaskManager::threadRunner::RunThread){}

TaskManager::~TaskManager(){}

TaskManager::threadRunner::threadRunner(nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& _queue):
     RunFunction(&TaskManager::threadRunner::RunTask)
,    m_isRunning(true)
,    m_taskQueue(_queue){}

/*--------------------------------------------------------------------------------------------------------------------*/

void TaskManager::threadRunner::RunTask()
{
    std::tr1::shared_ptr<Task> task(new VoidTask(0));
    
    m_taskQueue.Pop(task);
    task->RunThread();
}

void TaskManager::threadRunner::RunTaskUntillDone()
{
    std::tr1::shared_ptr<Task> task(new VoidTask(0));
    
    if(true == m_taskQueue.TryPop(task))
    {
        task->RunThread();
    }
    else
    {
        __sync_bool_compare_and_swap(&m_isRunning, 1, 0);
        // wake up the next thread so it can exit (in case it stuck on RunTask function)
        m_taskQueue.Push(std::tr1::shared_ptr<Task>(new VoidTask(0)));
    }
}

void TaskManager::threadRunner::RunThread()
{
    while(__sync_bool_compare_and_swap(&m_isRunning, 1, 1))
    {
        (this->*RunFunction)();
    }
}

}
