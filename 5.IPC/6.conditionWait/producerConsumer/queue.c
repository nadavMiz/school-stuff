#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "queue.h"
#include "ADTErr.h"

#define MAGIC_NAUMBER 0XCBFAA23A


struct Queue
{
	void** m_vec;
	size_t m_tail;
	size_t m_head;
	size_t m_size;
	size_t m_nItems;
	pthread_cond_t m_full;
	pthread_cond_t m_empty;
	pthread_mutex_t m_mutex;
	pthread_mutex_t m_dummy;
	size_t m_magicNumber;
};


Queue* QueueCreate(size_t _size)
{
	/* make queue */
	Queue* myQueue;
	if(_size < 1)
	{
		return NULL;
	}
	
	myQueue = malloc(sizeof(Queue));
	if(NULL == myQueue)
	{
		return NULL;
	}
	
	/*initialize semaphore*/
	if(pthread_mutex_init(&(myQueue->m_dummy), NULL) < 0)
	{
		free(myQueue);
		return NULL;
	}
	
	if(pthread_cond_init(&(myQueue->m_full), NULL) < 0)
	{
		pthread_mutex_destroy(&(myQueue->m_dummy));
		free(myQueue);
		return NULL;
	}
	
	if(pthread_cond_init(&(myQueue->m_empty), NULL) < 0)
	{
		pthread_mutex_destroy(&(myQueue->m_dummy));
		pthread_cond_destroy(&(myQueue->m_full));
		free(myQueue);
		return NULL;
	}
	
	if(pthread_mutex_init(&(myQueue->m_mutex), NULL))
	{
		pthread_mutex_destroy(&(myQueue->m_dummy));
		pthread_cond_destroy(&(myQueue->m_full));
		pthread_cond_destroy(&(myQueue->m_empty));
		free(myQueue);
		return NULL;
	}
	
	/* make array */
	(*myQueue).m_vec = malloc(_size * sizeof(void*));
	if(NULL == (*myQueue).m_vec)
	{
		pthread_mutex_destroy(&(myQueue->m_dummy));
		pthread_cond_destroy(&(myQueue->m_full));
		pthread_cond_destroy(&(myQueue->m_empty));
		free(myQueue);
		return NULL;
	}
	/* define stuff */
	(*myQueue).m_tail = 0;
	(*myQueue).m_head = 0;
	(*myQueue).m_size = _size;
	(*myQueue).m_nItems = 0;
	(*myQueue).m_magicNumber = MAGIC_NAUMBER;
	return myQueue;
	
}


void QueueDestroy(Queue* _queue)
{
	if(NULL == _queue);
	{
		return;
	}
	free((*_queue).m_vec);
	pthread_mutex_destroy(&(_queue->m_dummy));
	pthread_cond_destroy(&(_queue->m_full));
	pthread_cond_destroy(&(_queue->m_empty));
	pthread_mutex_destroy(&(_queue->m_mutex));
	free(_queue);
}


ADTErr QueueInsert(Queue* _queue, void* _item)
{
	if(NULL == _queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	while(_queue->m_size == _queue->m_nItems)
	{
		pthread_cond_wait(&(_queue->m_full), &(_queue->m_dummy));
	}
	pthread_mutex_lock(&(_queue->m_mutex));
	
	/* enter the item to the head */
	(*_queue).m_vec[(*_queue).m_head] = _item;
	
	/* advance the head and increase number of items*/
	(*_queue).m_head = (1 + (*_queue).m_head) % (*_queue).m_size;
	++(*_queue).m_nItems;
	
	pthread_mutex_unlock(&(_queue->m_mutex));
	pthread_cond_signal(&(_queue->m_empty));
	return ERR_OK;
}


ADTErr QueueRemove(Queue* _queue, void** _item)
{
	if(NULL == _queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	while(0 == _queue->m_nItems)
	{
		pthread_cond_wait((&(_queue->m_empty)), &(_queue->m_dummy));
	}
	
	pthread_mutex_lock(&(_queue->m_mutex));
	
	/* get the item from the tail */
	if(NULL != _item)
	{
		*_item = (*_queue).m_vec[(*_queue).m_tail];
	}
	/* advance the tail and reduce number of elements */
	(*_queue).m_tail = (1 + (*_queue).m_tail) % (*_queue).m_size;
	--(*_queue).m_nItems;
	
	pthread_mutex_unlock(&(_queue->m_mutex));
	pthread_cond_signal(&(_queue->m_full)); 
	return ERR_OK;
}


int QueueIsEmpty(Queue* _queue)
{
	if(NULL == _queue || 0 == (*_queue).m_nItems)
	{
		return 1;
	}
	return 0;
}

