#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "ADTErr.h"


struct Queue
{
	int* m_vec;
	size_t m_tail;
	size_t m_head;
	size_t m_size;
	size_t m_nItems;
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
	/* make array */
	(*myQueue).m_vec = malloc(_size * sizeof(int));
	if(NULL == (*myQueue).m_vec)
	{
		free(myQueue);
		return NULL;
	}
	/* define stuff */
	(*myQueue).m_tail = 0;
	(*myQueue).m_head = 0;
	(*myQueue).m_size = _size;
	(*myQueue).m_nItems = 0;
	return myQueue;
	
}


void QueueDestroy(Queue* _queue)
{
	if(NULL != _queue);
	{
		if(NULL != (*_queue).m_vec);
		{
			free((*_queue).m_vec);
		}
		free(_queue);
	}
}


ADTErr QueueInsert(Queue* _queue, int _item)
{
	if(NULL == _queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if((*_queue).m_nItems == (*_queue).m_size)
	{
		return ERR_OVERFLOW;
	}
	/* enter the item to the head */
	(*_queue).m_vec[(*_queue).m_head] = _item;
	
	/* advance the head and increase number of items*/
	(*_queue).m_head = (1 + (*_queue).m_head) % (*_queue).m_size;
	++(*_queue).m_nItems;
	return ERR_OK;
}


ADTErr QueueRemove(Queue* _queue, int* _item)
{
	if(NULL == _queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if((*_queue).m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	
	/* get the item from the tail */
	if(NULL != _item)
	{
		*_item = (*_queue).m_vec[(*_queue).m_tail];
	}
	/* advance the tail and reduce number of elements */
	(*_queue).m_tail = (1 + (*_queue).m_tail) % (*_queue).m_size;
	--(*_queue).m_nItems;
	return ERR_OK;
}


int QueueIsEmpty(Queue* _queue)
{
	if(NULL != _queue && 0 == (*_queue).m_nItems)
	{
		return 1;
	}
	return 0;
}


void QueuePrint(Queue* _queue)
{
	int element;
	int i;
	for	(i = 0; i < (*_queue).m_nItems; ++i)
	{
		element = (*_queue).m_vec[(i + (*_queue).m_tail) % (*_queue).m_size];
		printf("%d, ", element);
	}
	printf("\n");
}

