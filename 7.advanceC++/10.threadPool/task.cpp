#include "task.h"

namespace advcpp
{

Task::Task(Threadable* _threadable , unsigned int _priority):
    m_threadable(_threadable)
,   m_priority(_priority){}


bool Task::operator<(const Task& _task) const
{
    return m_priority < _task.m_priority;
}

bool Task::CompareSharedPtr::operator()(std::tr1::shared_ptr<Task> _a, std::tr1::shared_ptr<Task> _b) const
{
    return *_a < *_b;
}

}
