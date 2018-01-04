#include <stdlib.h>
#include <time.h>

#include "myTime.h"
#include "Task.h"

void TaskCalculateNext(Task* _task, const clockid_t m_clockID)
{
	TimeGetCurrent(m_clockID, _task->m_nextTime);
	TimeAdd(_task->m_nextTime, _task->m_interval);
}

Task* TaskCreate(TaskFunction _taskfunc, void* _context, size_t _period_ms, const clockid_t clockID)
{
	Task* mytask;
	
	if(NULL == _taskfunc)
	{
		return NULL;
	}
	
	mytask = malloc(sizeof(Task));
	if(NULL == mytask)
	{
		return NULL;
	}
	
	mytask->m_task = _taskfunc;
	mytask->m_context = _context;
	mytask->m_interval = TimeCreate((int)_period_ms);
	mytask->m_nextTime = TimeCreate(0);
	TaskCalculateNext(mytask, clockID);
	return mytask;
}

void TaskDestroy(Task* _task)
{
	TimeDestroy(_task->m_interval);
	TimeDestroy(_task->m_nextTime);
	free(_task);
}

int	TaskExecute(Task* _task, const clockid_t m_clockID)
{
	TimeSleepUntil(_task->m_nextTime, m_clockID);
	return _task->m_task(_task->m_context);
}

int	TaskLessThan(Task* _a, Task* _b)
{
	return TimeLessThan(_b->m_nextTime, _a->m_nextTime);
}
