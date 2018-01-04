#ifndef __HEAP_H__
#define __HEAP_H__
#include "vector.h"


typedef struct Heap Heap;

/*-----------Heap functions-----------*/

/*
create a heap struct out of a given vector
input _vec: vector to make a heap out of
returns:
	pointer to the new heap.
	NULL if vector was not initialized or if memory allocation failed. 
*/
Heap* HeapBuild(Vector* _vec);

/*
safely destroys a _heap struct (also destroys the vector the heap is built on)
input _heap: the heap to destroy.
*/
void HeapDestroy(Heap* _heap);

/*
insert a new element to the heap
input _heap: the heap to enter the element to
input _data: the new element to insert
returns:
	ERR_OK: insertion was successful
	ERR_NOT_INITIALIZED: heap is not initialized
	ERR_UNDERFLOW: heap is empty
*/
ADTErr HeapInsert(Heap* _heap, int _data);

/*
get the largest element in heap
input:
	_heap: the heap to get the max from
	_data: pointer to the element to put the max in.
returns:
	ERR_OK: the operation was successful
	ERR_NOT_INITIALIZED: heap is not initialized
	ERR_UNDERFLOW: heap is empty
*/
ADTErr HeapMax(Heap* _heap, int* _data);

/*
remove the largest element in heap
input:
	_heap: the heap to get the max from
	_data: pointer to the element to put the max in.
returns:
	ERR_OK: the operation was successful
	ERR_NOT_INITIALIZED: heap is not initialized
	ERR_UNDERFLOW: heap is empty
*/
ADTErr HeapExtractMax(Heap* _heap, int* _data);

/*
return the number of elements in a heap
input:
	_heap: the heap to get the number of elements of
returns:
	the number of elements in a heap.
	-1 if the heap was not initialized 
*/
size_t HeapItemsNum(Heap* _heap);

/*
prints the heap.
*/
void HeapPrint(Heap* _heap);

#endif /* ifndef __HEAP_H__ */
