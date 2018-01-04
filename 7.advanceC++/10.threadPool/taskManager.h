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

class TaskManager: public Threadable
{
public:
    TaskManager(nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& _queue);
    ~TaskManager();

    virtual void RunThread();
    void EndThread();
    
private:
    bool IsRunning();

private:
    /* data */
    Nmutex m_mutex;
    nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& m_taskQueue;
    bool m_isRunning;
    Nthread m_thread;
};

}

#endif /* TASK_RUNNER_H */

