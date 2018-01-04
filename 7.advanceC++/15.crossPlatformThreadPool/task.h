#ifndef TASK_H
#define TASK_H
#ifdef __linux__
#include <tr1/memory>
#elif defined WIN32
#include <memory>
#endif
#include <iostream>

namespace advcpp
{

class Task
{
public:
    Task(std::size_t m_priority);
    virtual ~Task() = 0;
    //Task(const Task& _task); default copy DTOR
    //Task& operator=(const Task& _task); default operator=
    bool operator<(const Task& _task) const;
    virtual void RunThread() = 0;
    
    unsigned int GetPriority();

private:
    /* data */
    std::size_t m_priority;
    
public:
    class CompareSharedPtr
    {
    public:
        bool operator()(std::tr1::shared_ptr<Task> _a, std::tr1::shared_ptr<Task> _b) const;
    };
};

inline Task::Task(std::size_t m_priority): m_priority(m_priority){}

inline Task::~Task(){}

inline unsigned int Task::GetPriority()
{
    return m_priority;
}

inline bool Task::operator<(const Task& _task) const
{
    return m_priority < _task.m_priority;
}

inline bool Task::CompareSharedPtr::operator()(std::tr1::shared_ptr<Task> _a, std::tr1::shared_ptr<Task> _b) const
{
    return *_a < *_b;
}


}
#endif /* TASK_H */

