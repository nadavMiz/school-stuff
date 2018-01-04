#ifndef TASK_H
#define TASK_H
#include <tr1/memory>
#include <iostream>

#include "threadable.h"

namespace advcpp
{

class Task
{
public:
    Task(Threadable* _threadable , unsigned int _priority = 0);
    //~Task();
    //Task(const Task& _task); default copy DTOR
    //Task& operator=(const Task& _task); default operator=
    bool operator<(const Task& _task) const;
    void RunThread();
    
    unsigned int GetPriority(){return m_priority;}

private:
    /* data */
    Threadable* m_threadable;
    unsigned int m_priority;
    
public:
    class CompareSharedPtr
    {
    public:
        bool operator()(std::tr1::shared_ptr<Task> _a, std::tr1::shared_ptr<Task> _b) const;
    };
};

inline void Task::RunThread()
{
    m_threadable->RunThread();
}

}
#endif /* TASK_H */

