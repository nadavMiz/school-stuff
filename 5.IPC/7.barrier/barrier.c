#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> /*perror*/

#include "barrier.h"

#define MAGIC_NUMBER 0XCDEF113A
#define IS_BARRIER(B) (NULL != (B) && MAGIC_NUMBER == (B)->m_magicNumber)

struct Barrier
{
	size_t m_magicNumber;
	unsigned int m_capacity;
	unsigned int m_nItems;
	pthread_cond_t m_barrier;
	pthread_mutex_t m_mutex;
};

Barrier* BarrierCreate(unsigned int _capacity)
{
	Barrier* newBarrier;
	
	newBarrier = malloc(sizeof(Barrier));
	if(NULL == newBarrier)
	{
		printf("barrier maloc failed\n");
		return NULL;
	}
	
	if(pthread_cond_init(&(newBarrier->m_barrier), NULL) < 0)
	{
		perror("cond init");
		free(newBarrier);
		return NULL;
	}
	
	if(pthread_mutex_init(&(newBarrier->m_mutex), NULL) < 0)
	{
		perror("mutex init");
		pthread_mutex_destroy(&(newBarrier->m_mutex));
		free(newBarrier);
		return NULL;
	}
	
	newBarrier->m_capacity = _capacity;
	newBarrier->m_magicNumber = MAGIC_NUMBER;
	
	return newBarrier;
}

void BarrierDestroy(Barrier* _barrier)
{
	_barrier->m_magicNumber = 0;
	
	/*relice all remaining threads and wait for them to exit*/
	if(0 != _barrier->m_nItems)
	{
		pthread_cond_broadcast(&(_barrier->m_barrier));
		pthread_cond_wait(&(_barrier->m_barrier), &(_barrier->m_mutex));
	}
	
	pthread_cond_destroy(&(_barrier->m_barrier));
	pthread_mutex_destroy(&(_barrier->m_mutex));
	free(_barrier);
}

int BarrierWait(Barrier* _barrier)
{
	if(!IS_BARRIER(_barrier))
	{
		return 0;
	}
	pthread_mutex_lock(&(_barrier->m_mutex));
	++_barrier->m_nItems;
	
	if(_barrier->m_nItems < _barrier->m_capacity && MAGIC_NUMBER == _barrier->m_magicNumber)
	{
		pthread_cond_wait(&(_barrier->m_barrier), &(_barrier->m_mutex));
	}
	else
	{
		pthread_cond_broadcast(&(_barrier->m_barrier));	
		_barrier->m_nItems = 0;
	}
	pthread_mutex_unlock(&(_barrier->m_mutex));
	
	/*if barrier was destroyed*/
	if(MAGIC_NUMBER != _barrier->m_magicNumber)
	{
		if(--_barrier->m_nItems == 0)
		{
			pthread_cond_signal(&(_barrier->m_barrier));	
		}
		return -1;
	}
	return 1;
}
