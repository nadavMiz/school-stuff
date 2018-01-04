#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>

#include "barrier.h"

#define NUM_COUNTERS 10
#define NUM_ITERATIONS 5
#define NUM_LOOPS 5
#define COUNTER_MAX_WAIT_TIME 200000

typedef struct
{
	size_t* m_counterPtr;
	size_t m_iterations;
	size_t m_numLoops;
	Barrier* m_barrier;
	sem_t* m_sumaraizerSem;
	
} CountContext;

typedef struct
{
	size_t m_numCounters;
	size_t* m_counterArr;
	size_t* m_result;
	Barrier* m_barrier;
	sem_t* m_sumaraizerSem;
} SumContext;

void* CounterFunc(CountContext* _context)
{
	size_t i, j;
	
	for(j = 0; j < _context->m_numLoops; ++j)
	{
		*(_context->m_counterPtr) = 0;
		
		for(i = 0; i < _context->m_iterations; ++i)
		{
			++(*(_context->m_counterPtr));
			usleep((__useconds_t)rand()%COUNTER_MAX_WAIT_TIME);
		}
	
		sem_post(_context->m_sumaraizerSem);
		printf("counter finished incrementing sum is: %d\n", *(_context->m_counterPtr));
		BarrierWait(_context->m_barrier);
	}
	pthread_exit(NULL);
}

/*------------------------------*/

static void waitNSemaphore(sem_t* _sem, size_t _waitNum)
{
	size_t i;
	
	for(i = 0; i < _waitNum; ++i)
	{
		sem_wait(_sem);
	}
}

void* SumerizerFunc(SumContext* _context)
{
	size_t i;
	
	waitNSemaphore(_context->m_sumaraizerSem, _context->m_numCounters);
	
	for(i = 0; i < _context->m_numCounters; ++i)
	{
		*(_context->m_result) += _context->m_counterArr[i];
	}
	
	BarrierWait(_context->m_barrier);
	printf("summerizer finished: %d\n", *(_context->m_result));
	pthread_exit(NULL);
}

/*-----------------------------*/

static CountContext* BuildCounterContext(size_t* _counterPtr, Barrier* _barrier, sem_t* _sumaraizerSem)
{
	CountContext* newContext = malloc(sizeof(CountContext));
	if(NULL == newContext)
	{
		return NULL;
	}
	
	*_counterPtr = 0;
	
	newContext->m_counterPtr = _counterPtr;
	newContext->m_iterations = NUM_ITERATIONS;
	newContext->m_barrier = _barrier;
	newContext->m_numLoops = NUM_LOOPS;
	newContext->m_sumaraizerSem = _sumaraizerSem;
	
	return newContext;
}

static SumContext* BuildSumContext(size_t* _counterArr, size_t _numCounters,
										 Barrier* _barrier, sem_t* _sumaraizerSem, size_t* _counterSum)
{
	SumContext* context = malloc(sizeof(SumContext));
	if(NULL == context)
	{
		printf("sumerize context creation failed\n");
		return NULL;
	}
	
	context->m_numCounters = _numCounters;
	context->m_counterArr = _counterArr;
	context->m_result = _counterSum;
	context->m_barrier = _barrier;
	context->m_sumaraizerSem = _sumaraizerSem;
	
	return context;
}

/*-----------------------------*/

static pthread_t* BuildCounters(size_t _numThreads, size_t* _counts, sem_t* _summarizerSem, Barrier* _barrier)
{
	CountContext* context;
	size_t i;
	pthread_t* threads = NULL;
	
	threads = malloc(_numThreads * sizeof(int));
	if(NULL == threads)
	{
		return NULL;
	}
	
	/*create threads*/
	for(i = 0; i < _numThreads; ++i)
	{
		context = BuildCounterContext(&(_counts[i]), _barrier, _summarizerSem);
		if(NULL == context)
		{
			printf("build counter context failed\n");
			continue;
		}
		
		if(0 != pthread_create(&(threads[i]), NULL, (void * (*)(void *))CounterFunc, (void*)context))
		{
			perror("thread create");
		}
	}
	
	return threads;
}

/*-----------------------------*/

static pthread_t BuildSummerizer(size_t _numThreads, size_t* _counts, Barrier* _barrier,
							 sem_t* _summarizerSem, size_t* _counterSum)
{
	 SumContext* context;
	 pthread_t summerizer;
	
	*_counterSum = 0;
	context = BuildSumContext(_counts, _numThreads, _barrier, _summarizerSem, _counterSum);
	if(NULL == context)
	{
		return 0;
	}
	
	if(0 != pthread_create(&summerizer, NULL, (void * (*)(void *))SumerizerFunc, context))
	{
		perror("thread create");
	}
	return summerizer;
}

/*-----------------------------*/

static void JoinCounters(pthread_t* _counters, size_t _numCounters)
{
	size_t i;
	int status;
	
	for(i = 0; i < _numCounters; ++i)
	{
		status = pthread_join(_counters[i] ,NULL);
		if(status != 0)
		{
			printf("%d thread join failed\n", status);
		}
	}
}

/*-----------------------------*/

static void JoinSummerizer(pthread_t _summerizer)
{
	if(0 != pthread_join(_summerizer ,NULL))
	{
		printf("thread join failed\n");
	}
}

/*-----------------------------*/

int main()
{
	size_t i, counterSum;
	size_t counts[NUM_COUNTERS] = {0};
	pthread_t* counters;
	pthread_t summerizer;
	sem_t SummerizerSem;
	Barrier* barrier;
	
	/*initialize stuff*/
	barrier = BarrierCreate(NUM_COUNTERS + 1);
	if(NULL == barrier)
	{
		printf("barrier creation failed\n");
		return 0;
	}
	
	if(sem_init(&SummerizerSem, 0, 0) < 0)
	{
		perror("sem init");
		BarrierDestroy(barrier);
		return 0;
	}
	
	/*run the program*/
	counters = BuildCounters(NUM_COUNTERS, counts, &SummerizerSem, barrier);
	
	for(i = 0; i < NUM_LOOPS; ++i)
	{
		summerizer = BuildSummerizer(NUM_COUNTERS, counts, barrier, &SummerizerSem, &counterSum);
		JoinSummerizer(summerizer);
	}
	
	JoinCounters(counters, NUM_COUNTERS);
	
	/*destroy all stuff*/
	
	
	return 1;
}
	
