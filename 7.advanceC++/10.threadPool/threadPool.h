#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <tr1/memory>
#include <vector>

#include "nPrioretyQueue.h"
#include "taskManager.h"
#include "task.h"

namespace advcpp
{

typedef std::tr1::shared_ptr<Task> taskPtr;

class ThreadPool
{
public:
    ThreadPool(unsigned int _size = 10);
    ~ThreadPool();
    
    void AddTask(taskPtr _task);
    void ShutDown();

public:
    nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr>& GetQueue(){return m_taskQueue;}

private:
    /* data */
    nPrioretyQueue<taskPtr, std::vector<taskPtr>, Task::CompareSharedPtr> m_taskQueue;
    std::vector<TaskManager*> m_taskManagers;
    
private:
    class VoidTask: public Threadable
    {
        public:
            virtual void RunThread(){}
    };
    
};

}
#endif /* THREAD_POOL_H */

