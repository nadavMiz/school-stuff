#ifndef __THREADS_CONTAINER_H__
#define __THREADS_CONTAINER_H__

#include <set>
#include <cstddef>
#include "taskManager.h"

class ThreadsContainer
{
	public:
		ThreadsContainer(std::size_t _size);
		~ThreadsContainer();
		
		std::tr1::shared_ptr<TaskManager> GetTaskManager(ThreadId _id);
		
		template<class T>
		void ForEach(T Function);
		template<void(TaskManager::*Func)(void)>
		void ForEach();

	private:
		/* data */
		std::set<std::tr1::shared_ptr<TaskManager> >
};

template<void (TaskManager::*Func)(void)>
class MemberFunctor
{
public:
	operator()(std::tr1::shared_ptr<TaskManager>& _taskManager)
	{
		(*_taskManager).*Func;
	}
	
}

#endif /* __THREADS_CONTAINER_H__ */

