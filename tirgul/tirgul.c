#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define ELEM_SIZE 5


typedef struct 
{
	unsigned short* m_buffer;
	size_t m_capacity;
	size_t m_noe;
	size_t m_size;
	short m_tailIdx;
	short m_headIdx;
	short m_tailShift;
	short m_headShift;
	short m_mask;
	
} Queue;


Queue* CreateQueue(size_t _size)
{
	Queue* newQueue = malloc(sizeof(Queue));
	if(NULL == newQueue)
	{
		return NULL;
	}
	
	newQueue->m_size = _size * ELEM_SIZE / 8;
	newQueue->m_buffer = malloc(newQueue->m_size + 1);
	if(NULL == newQueue->m_buffer)
	{
		free(newQueue);
		return NULL;
	}
	
	newQueue->m_capacity = _size;
	newQueue->m_mask = (1 << ELEM_SIZE) - 1;
	newQueue->m_noe = 0;
	newQueue->m_tailIdx = 0;
	newQueue->m_headShift = 0;
	newQueue->m_tailShift = 0;
	newQueue->m_headShift = 0;
	
	return newQueue;
}

void DestroyQueue(Queue* _queue)
{
	if(_queue == NULL)
	{
		return;
	}
	
	free(_queue->m_buffer);
	free(_queue);
}

void MoveForward(Queue* _queue, short* _index, short* _shiftVal)
{
	*_shiftVal += ELEM_SIZE;
	
	if(*_shiftVal >= 8)
	{
		++(*_index);
		if(*_index > _queue->m_size)
		{
			*_index = 0;
			*_shiftVal = 0;
		}
		else
		{
			*_shiftVal -= 8;
		}
	}
}



int Enqueue(Queue* _queue, char _element)
{
	if(NULL == _queue || _queue->m_capacity == _queue->m_noe)
	{
		return 0;
	}
	
	_queue->m_buffer[_queue->m_headIdx] += (short)_element << _queue->m_headShift;
	
	MoveForward(_queue, &_queue->m_headIdx, &_queue->m_headShift);
	
	++_queue->m_noe;
	
	return 1;
}

int Dequeue(Queue* _queue, char* _element)
{
	if(NULL == _queue || 0 == _queue->m_noe)
	{
		return -1;
	}
	
	*_element = (_queue->m_buffer[_queue->m_tailIdx] & (_queue->m_mask << _queue->m_tailShift)) >> _queue->m_tailShift;
	_queue->m_buffer[_queue->m_tailIdx] &= ~(_queue->m_mask >> _queue->m_tailShift);
	
	MoveForward(_queue, &_queue->m_tailIdx, &_queue->m_tailShift);
	--_queue->m_noe;
	
	return 1;
}

int main()
{
	Queue* queue = CreateQueue(5);
	char elem;

	for(char i = 0; i < 5; ++i)
	{
		Enqueue(queue, i);
	}
	for(int i = 0; i < 3; ++i)
	{
		Dequeue(queue, &elem);
		printf("%d\n", elem);
	}
	for(char i = 0; i < 5; ++i)
	{
		Enqueue(queue, i);
	}
	for(int i = 0; i < 9; ++i)
	{
		Dequeue(queue, &elem);
		printf("%d\n", elem);
	}
	return 0;
}
