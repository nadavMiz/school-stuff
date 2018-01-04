#include <stdlib.h>
#include <string.h>

#include "Scheduler.h"
#include "heap.h"
#include "Task.h"
#include "genericVector.h"

#define MAGIC_NUMBER 0XCBA1234A
#define VEC_SIZE 10
#define VEC_BLOCK_SIZE 10

#define IS_SCHEDULER(S) ((NULL != S) && (MAGIC_NUMBER == (S)->m_magicNumber))

struct PeriodicExecutor
{
	char*			m_name;
	Heap*	        m_priorityQ;
	size_t		    m_runCycles;
	int		        m_isPaused;
	clockid_t		m_clockID;
	size_t 			m_magicNumber;
};

Vector* g_vec;

PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clk_id)
{
	PeriodicExecutor* newExecutor = malloc(sizeof(PeriodicExecutor));
	if(NULL == newExecutor)
	{
		return NULL;
	}
	
	newExecutor->m_name = malloc(sizeof(char) * (strlen(_name) + 1));
	if(NULL == newExecutor->m_name)
	{
		free(newExecutor);
		return NULL;
	}
	strcpy(newExecutor->m_name, _name);
	
	g_vec = VectorCreate(VEC_SIZE, VEC_BLOCK_SIZE);
	if(NULL == g_vec)
	{
		free(newExecutor->m_name);
		free(newExecutor);
		return NULL;
	}
	
	newExecutor->m_priorityQ = Heap_Build(g_vec, (LessThanComparator)TaskLessThan);
	if(NULL == newExecutor->m_priorityQ)
	{
		free(newExecutor->m_name);
		free(newExecutor);
		VectorDestroy(&g_vec, (UserInputFunc)TaskDestroy);
	}
	
	newExecutor->m_runCycles = 0;
	newExecutor->m_isPaused = 1;
	newExecutor->m_clockID = _clk_id;
	newExecutor->m_magicNumber = MAGIC_NUMBER;
	
	return newExecutor;
}

void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{
	if(!IS_SCHEDULER(_executor))
	{
		return;
	}
	
	_executor->m_magicNumber = 0;
	
	free(_executor->m_name);
	Heap_Destroy(&(_executor->m_priorityQ));
	free(_executor);
	VectorDestroy(&g_vec, (UserInputFunc)TaskDestroy);
}

size_t PeriodicExccutorRun(PeriodicExecutor* _executor)
{
	Task* currentTask;
	
	if(!IS_SCHEDULER(_executor))
	{
		return 0;
	}
	
	_executor->m_isPaused = 0;
	while(0 != Heap_Size(_executor->m_priorityQ) && !_executor->m_isPaused)
	{
		currentTask = Heap_Extract(_executor->m_priorityQ);
		if(0 == TaskExecute(currentTask, _executor->m_clockID))
		{
			TaskCalculateNext(currentTask, 0);
			Heap_Insert(_executor->m_priorityQ, currentTask);
		}
		++(_executor->m_runCycles);
	}
	return _executor->m_runCycles;
}

size_t PeriodicExccutorPause(PeriodicExecutor* _executor)
{
	if(!IS_SCHEDULER(_executor))
	{
		return 0;
	}
	
	_executor->m_isPaused = 1;
	return Heap_Size(_executor->m_priorityQ);
}

int PeriodicExccutorAdd(PeriodicExecutor* _executor, TaskFunction _taskFunction, void* _context, size_t _period_ms)
{
	Task* newTask;
	
	if(!IS_SCHEDULER(_executor))
	{
		return 0;
	}
	
	newTask = TaskCreate(_taskFunction, _context, _period_ms, _executor->m_clockID);
	if(NULL == newTask)
	{
		return 0;
	}
	Heap_Insert(_executor->m_priorityQ, newTask);
	return 1;
}

