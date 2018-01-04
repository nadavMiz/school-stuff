#ifndef VOID_TASK_H
#define VOID_TASK_H

#include "task.h"

namespace advcpp
{

class VoidTask: public Task
{
    public:
        VoidTask(std::size_t _priority);
        virtual ~VoidTask(){}
        virtual void RunThread(){}
};

inline VoidTask::VoidTask(std::size_t _priority): Task(_priority){}

}
#endif /* VOID_TASK_H */

