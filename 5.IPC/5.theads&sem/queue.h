#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stddef.h>
#include "ADTErr.h"

typedef struct Queue Queue;

/*
creates a new queue data structure
param _size: number of posible elements in queue
return: pointer to a new queue if  a problem accured return NULL
*/
Queue* QueueCreate(size_t _size);

/*
remove a queue safely
param  _queue: queue to remove
*/
void QueueDestroy(Queue* _queue);

/*
insert _item to the queue
param _queue: pointer to the queue
param _item: the item to insert.
return: the error of the function.
*/
ADTErr QueueInsert(Queue* _queue, void* _item);

/*
remove the item from the tail of queue. 
param _queue: pointer to the queue
param _item: _item: pointer to an int to hold the removed item;
*/
ADTErr QueueRemove(Queue* _queue, void** _item);

/*
check if the queue is empty
param _queue: pointer to the queue
return 0: if the queue is full. 1: else
*/
int QueueIsEmpty(Queue* _queue);

/*
prints all the elements of the queue by order
*/
void QueuePrint(Queue* _queue);

/*
get number of items blocked in queue
*/
size_t nItemsInQueue(Queue* _queue);


#endif /* ifndef __QUEUE_H__ */
