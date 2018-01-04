#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <pthread.h> /* get thread id */

#include "producer.h"
#include "queue.h"

#define MAX_ITERATIONS 10

struct Producers
{
	pthread_t* m_producers;
	size_t m_size;
};

typedef struct
{
	size_t m_numIterations;
	Queue* m_queue;
} Context;

/*-------------------------------------*/

void* ProducerFunction(Context* _context)
{
	size_t i;
	
	for(i = 0; i < _context->m_numIterations; ++i)
	{
		QueueInsert(_context->m_queue, (void*)4);
	}
	
	free(_context);
	pthread_exit(NULL);
}

/*---------------------------------------*/

static Context* BuildContext(size_t _iterations, Queue* _queue)
{
	Context* newContext = malloc(sizeof(Context));
	if(NULL == newContext)
	{
		return NULL;
	}
	
	newContext->m_numIterations = _iterations;
	newContext->m_queue = _queue;
	
	return newContext;
}

Producers* CreateProducers(size_t _size, Queue* _queue)
{
	size_t i;
	Context* context;
	
	Producers* newProducers = malloc(sizeof(Producers));
	if(NULL == newProducers)
	{
		return NULL;
	}
	
	newProducers->m_size = _size;
	newProducers->m_producers = malloc(_size * sizeof(pthread_t));
	if(NULL == newProducers->m_producers)
	{
		free(newProducers);
		return NULL;
	}
	
	for(i = 0; i < _size; ++i)
	{
		context = BuildContext(3, _queue);
		
		if(0 != pthread_create(&(newProducers->m_producers[i]), NULL, (void * (*)(void *))ProducerFunction, (void*)context))
		{
			perror("thread create");
		}
	}
	
	return newProducers;
}

/*---------------------------------------*/

void DestroyProducers(Producers* _producers)
{
	if(NULL == _producers)
	{
		return;
	}
	free(_producers->m_producers);
	free(_producers);
}

/*----------------------------------------*/

void ProducerJoin(Producers* _producers)
{
	size_t i;
	int status;
	
	for(i = 0; i < _producers->m_size; ++i)
	{
		status = pthread_join(_producers->m_producers[i] ,NULL);
		if(status != 0)
		{
			printf("%d thread join failed\n", status);
		}
	}
}
