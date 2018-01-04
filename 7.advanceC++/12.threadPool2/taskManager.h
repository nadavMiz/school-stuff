#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include "task.h"
#include "nPrioretyQueue.h"
#include "threadable.h"
#include "nthread.h"
#include "Nmutex.h"

namespace advcpp
{

typedef std::tr1::shared_ptr<Task> taskPtr;

class TaskManager
{

private:
    class threadRunner
    {
    friend class TaskManager;
    
    public:
        threadRunner(nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& _queue);
        //~threadRunner();
        void Run();
        void RunThread();
    
    private:
        void(threadRunner::*RunFunction)(void);
        void RunTask();
        void RunTaskUntillDone();
    
    private:
        bool m_isRunning;
        nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& m_taskQueue;
    };

public:
    TaskManager(nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& _queue);
    ~TaskManager();
    
    inline void EndThreadSafely();
    inline void EndThreadFullySafely();
    inline void CancelThread();
    inline void JoinThread(); 

private:
    /* data */
    std::tr1::shared_ptr<TaskManager::threadRunner> m_taskManager;
    Nthread<TaskManager::threadRunner> m_thread;
};

inline void TaskManager::EndThreadSafely()
{
    __sync_bool_compare_and_swap(&(m_taskManager->m_isRunning), 1, 0);
}

inline void TaskManager::EndThreadFullySafely()
{
    m_taskManager->RunFunction = &threadRunner::RunTaskUntillDone;
}

inline void TaskManager::CancelThread()
{
    m_thread.Cancel();
}

inline void TaskManager::JoinThread()
{
    m_thread.Join();
} 

}

#endif /* TASK_RUNNER_H */

