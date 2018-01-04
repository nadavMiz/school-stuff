#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "consumer.h"
#include "queue.h"

#define SECOND 1000000
#define EOW -1

struct Consumers
{
	Queue* m_queue;
	pthread_t* m_consumers;
	size_t m_size;
};

/*----------------------------------------------*/

void* ConsumerFunction(void* _queue)
{
	int item;
	for(;;)
	{
		QueueRemove((Queue*)_queue, (void**)(&item));
		if(EOW == item)
		{
			QueueInsert((Queue*)_queue, (void*)EOW);
			pthread_exit(NULL);
		}
		printf("thread got item inserted by producer: %d\n", item);
	}
}

/*----------------------------------------------*/

Consumers* CreateConsumers(size_t _size, Queue* _queue)
{
	size_t i;
	Consumers* newConsumers = malloc(sizeof(Consumers));
	if(NULL == newConsumers)
	{
		return NULL;
	}
	
	newConsumers->m_queue = _queue;
	newConsumers->m_size = _size;
	newConsumers->m_consumers = malloc(_size * sizeof(pthread_t*));
	if(NULL == newConsumers->m_consumers)
	{
		free(newConsumers);
		return NULL;
	}
	
	for(i = 0; i < _size; ++i)
	{
		if(0 != pthread_create(&(newConsumers->m_consumers[i]), NULL, ConsumerFunction, _queue))
		{
			perror("thread create");
		}
	}
	
	return newConsumers;
}

/*--------------------------------------------*/

void DestroyConsumers(Consumers* _consumers)
{
	free(_consumers->m_consumers);
	free(_consumers);
}

/*--------------------------------------------*/

void ConsumersJoin(Consumers* _consumers)
{
	size_t i;
	int status;
	
	for(i = 0; i < _consumers->m_size; ++i)
	{
		status = pthread_join(_consumers->m_consumers[i] ,NULL);
		if(status != 0)
		{
			printf("%d thread join failed\n", status);
		}
	}
}

/*---------------------------------------------*/

void SignalEndConsumeCycle(Consumers* _consumers)
{
	QueueInsert(_consumers->m_queue, (void*)EOW);
}

