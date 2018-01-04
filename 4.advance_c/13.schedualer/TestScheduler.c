#include <stdio.h>
#include <stdlib.h>

#include "mu_test.h"
#include "Scheduler.h"
#include "genericVector.h"

#define LOG_SIZE 10

/*-------------test task-----------*/
typedef struct
{
	int    m_taskNumber;
	size_t m_count;
	size_t m_numIteration;
	
	Vector*   m_taskLog;
} countStruct;

int countFunc(countStruct* _count)
{
	int* logMark;
	
	++_count->m_count;
	
	logMark = malloc(sizeof(int));
	*logMark = _count->m_taskNumber;
	VectorAdd(_count->m_taskLog, logMark);
	
	return (_count->m_count == _count->m_numIteration);
}

countStruct* buildCount(size_t _numIterations, int taskNumber, Vector* _taskLog)
{
	countStruct* newCount = malloc(sizeof(countStruct));
	
	newCount->m_taskNumber = taskNumber;
	newCount->m_count = 0;
	newCount->m_numIteration = _numIterations;
	newCount->m_taskLog = _taskLog;
	
	return newCount;
}

int DestroyInt(void* _elementPtr, void* _dummy)
{
	free(_elementPtr);
	return 1;
}

/*--------------helper functions------------*/

int CheckLog(Vector*
 _taskLog, int* _compareArray, size_t _compareLength)
{
	size_t i;
	int* elem;
	for(i = 0; i < _compareLength; ++i)
	{
		VectorGet(_taskLog, i, (void**)(&elem));
		if(_compareArray[i] != *elem)
		{
			return 0;
		}
	}
	return 1;
}

/*-----------main test functions------------*/

UNIT(CreateScheduler)
	PeriodicExecutor* scheduler = PeriodicExecutorCreate("nadav", 0);
	ASSERT_THAT(NULL != scheduler);
	PeriodicExecutorDestroy(scheduler);
END_UNIT

UNIT(addTask)
	PeriodicExecutor* scheduler;
	
	scheduler = PeriodicExecutorCreate("nadav", 0);
	
	ASSERT_THAT(1 == PeriodicExccutorAdd(scheduler, (TaskFunction)countFunc, NULL, 20));
	PeriodicExecutorDestroy(scheduler);
END_UNIT

UNIT(addTaskNullFunction)
	PeriodicExecutor* scheduler;
	
	scheduler = PeriodicExecutorCreate("nadav", 0);
	
	ASSERT_THAT(0 == PeriodicExccutorAdd(scheduler, NULL, NULL, 20));
	PeriodicExecutorDestroy(scheduler);
END_UNIT

UNIT(addTaskNullSchedueler)
	ASSERT_THAT(0 == PeriodicExccutorAdd(NULL, (TaskFunction)countFunc, NULL, 20));
END_UNIT

UNIT(runSchedulerSingleTask)
	PeriodicExecutor* scheduler;
	Vector* taskLog;
	countStruct* context;
	size_t iterations = 3;
	size_t realIterations;
	
	taskLog = VectorCreate(5, 5);
	context = buildCount(iterations, 1, taskLog);
	scheduler = PeriodicExecutorCreate("nadav", 0);
	
	PeriodicExccutorAdd(scheduler, (TaskFunction)countFunc, context, 20);
	
	PeriodicExccutorRun(scheduler);
	VectorItemsNum(taskLog, &realIterations);
	ASSERT_THAT(iterations == realIterations);
	
	VectorDestroy(&taskLog, DestroyInt);
	PeriodicExecutorDestroy(scheduler);
	free(context);
END_UNIT

UNIT(runSchedulerMultipleTasks)
	PeriodicExecutor* scheduler;
	Vector* taskLog;
	countStruct *context1, *context2, *context3;
	int resultLog[] = {1,2,1,3,1,2,3,2};
	
	scheduler = PeriodicExecutorCreate("nadav", 0);
	taskLog = VectorCreate(5, 5);
	
	/*build functions*/
	context1 = buildCount(3, 1, taskLog);
	PeriodicExccutorAdd(scheduler, (TaskFunction)countFunc, context1, 10);
	
	context2 = buildCount(3, 2, taskLog);
	PeriodicExccutorAdd(scheduler, (TaskFunction)countFunc, context2, 20);
	
	context3 = buildCount(2, 3, taskLog);
	PeriodicExccutorAdd(scheduler, (TaskFunction)countFunc, context3, 30);
	
	/*run the executer*/
	ASSERT_THAT((sizeof(resultLog)/sizeof(int)) == PeriodicExccutorRun(scheduler));
	ASSERT_THAT(CheckLog(taskLog, resultLog, sizeof(resultLog)/sizeof(int)));
	
	/*free all malocs*/
	VectorDestroy(&taskLog, DestroyInt);
	PeriodicExecutorDestroy(scheduler);
	free(context1);
	free(context2);
	free(context3);
END_UNIT

UNIT(runNullScheduler)
	ASSERT_THAT(0 == PeriodicExccutorRun(NULL));
END_UNIT

UNIT(pauseScheduler)
	PeriodicExecutor* scheduler;
	countStruct *context;
	
	scheduler = PeriodicExecutorCreate("nadav", 0);
	
	/*add functions*/
	context = buildCount(5, 1, NULL);
	PeriodicExccutorAdd(scheduler, (TaskFunction)countFunc, context, 10);
	
	PeriodicExccutorAdd(scheduler, (TaskFunction)PeriodicExccutorPause, scheduler, 25);
	
	/*run the executer*/
	ASSERT_THAT(3 == PeriodicExccutorRun(scheduler));
	ASSERT_THAT(1 == PeriodicExccutorPause(scheduler));
	ASSERT_THAT(6 == PeriodicExccutorRun(scheduler));
	
	/*free all malocs*/
	PeriodicExecutorDestroy(scheduler);
	free(context);
END_UNIT

UNIT(pauseNullScheduler)
	ASSERT_THAT(0 == PeriodicExccutorPause(NULL));
END_UNIT

TEST_SUITE(scheduler test)
	TEST(CreateScheduler)
	
	TEST(addTask)
	TEST(addTaskNullFunction)
	TEST(addTaskNullSchedueler)
	
	TEST(runSchedulerSingleTask)
	TEST(runSchedulerMultipleTasks)
	TEST(runNullScheduler)
	
	TEST(pauseScheduler)
	TEST(pauseNullScheduler)
	
END_SUITE
