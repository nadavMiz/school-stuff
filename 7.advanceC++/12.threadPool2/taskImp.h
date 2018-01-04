#ifndef TASK_IMP_H
#define TASK_IMP_H

#include "task.h"

namespace advcpp
{

template <class T>
class TaskImp: public Task
{
    public:
        TaskImp(std::tr1::shared_ptr<T> _obj, void(T::*Run)(void), std::size_t priority);
        virtual ~TaskImp();
        virtual void RunThread();

    private:
        /* data */
        std::tr1::shared_ptr<T> m_obj;
        void(T::*m_runFunc)(void);
        //std::size_t m_priority;
};

template <class T>
TaskImp<T>::TaskImp(std::tr1::shared_ptr<T> _obj, void(T::*Run)(void), std::size_t _priority):
    Task(_priority)
,   m_obj(_obj)
,   m_runFunc(Run){}

template <class T>
TaskImp<T>::~TaskImp(){}

template <class T>
void TaskImp<T>::RunThread()
{
    ((*m_obj).*(m_runFunc))();
}

}
#endif /* TASK_IMP_H */

