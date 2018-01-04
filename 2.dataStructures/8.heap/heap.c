#include <stdlib.h>
#include "heap.h"
#include "vector.h"

#define MAGIC_NUMBER 666666
#define RIGHT(i) (2 * i + 1) /* get the right child */
#define LEFT(i) (2 * i) /* get the left child */
#define FATHER(i) (i / 2) /* get parent */

/* Heap struct */

struct Heap
{
    Vector* m_vector;
    size_t m_heapSize;
    size_t m_magicNumber;

};


/*-------------static heap functions------------*/
/*
returns 1 if _heap is initialized. 0 if it isn't
*/
static int CheckHeap(Heap* _heap)
{
	return (NULL != _heap && MAGIC_NUMBER == _heap->m_magicNumber) ? 1 : 0;
}

/*
swaps element in a vector
input _heap: the heap to swap elements in
input _idx1: the index of the first element to swap
input _idx2: the index of the second element to swap
*/
static ADTErr swapInHeap(Heap* _heap, size_t _idx1, size_t _idx2)
{
	ADTErr error;
	int num1;
	int num2;
	error = VectorGet(_heap->m_vector, _idx1, &num1);
	if(ERR_OK != error)
	{
		return error;
	}
	error = VectorGet(_heap->m_vector, _idx2, &num2);
	if(ERR_OK != error)
	{
		return error;
	}
	VectorSet(_heap->m_vector, _idx1, num2);
	VectorSet(_heap->m_vector, _idx2, num1);
	return ERR_OK;
	
}

static void heapify(Heap* _heap, size_t currentIdx)
{
	ADTErr error;
	int currentElem;
	int leftElem;
	int rightElem;
	size_t destIdx;
	int destElem;
	VectorGet(_heap->m_vector, currentIdx, &currentElem);
	/* get the largest child and his index */
	error = VectorGet(_heap->m_vector, LEFT(currentIdx), &leftElem);
	/* if there is a left child */
	if(ERR_OK == error)
	{
		error = VectorGet(_heap->m_vector, RIGHT(currentIdx), &rightElem);
		/*if there is a right child get largest out of them*/
		if(ERR_OK == error)
		{
			if(leftElem > rightElem)
			{
				destElem = leftElem;
				destIdx = LEFT(currentIdx);
			}
			else
			{
				destElem = rightElem;
				destIdx = RIGHT(currentIdx);
			}
		}
		/* if there is only a left child it has to be the biggest */
		else
		{
			destElem = leftElem;
			destIdx = LEFT(currentIdx);
		}
	}
	/* if the node has no children return */
	else
	{
		return;
	}
	/* check if the largest child is bigger than the parent if it is swap them */
	if(destElem > currentElem)
	{
		swapInHeap(_heap, currentIdx, destIdx);
		heapify(_heap, destIdx);
	}
}

/*--------------main Heap functions-------------*/

Heap* HeapBuild(Vector* _vec)
{
	int i;
	Heap* heap = NULL;
	if(NULL == _vec)
	{
		return NULL;
	}
	heap = malloc(sizeof(Heap));
	if(NULL != heap)
	{
		heap->m_vector = _vec;
		VectorItemsNum(_vec, (int*)&(heap->m_heapSize));
		heap->m_magicNumber = MAGIC_NUMBER;
		/* sort the heap so every element is larger than its children */
		for(i = (heap->m_heapSize / 2 ); i >= 0; --i)
		{
			heapify(heap, i);
		}
	}
	return heap;
}

void HeapDestroy(Heap* _heap)
{
	if(CheckHeap(_heap))
	{
		VectorDestroy(_heap->m_vector);
		_heap->m_magicNumber = 0;
		free(_heap);
	}
}

/*----------------------------------------*/
/*
function that moves an item up a bynary tree until it gets to the right position (the elements futher is bigger than it)
*/
static void BubbleUp(Heap* _heap, size_t _currentIndex)
{
	int currentElem;
	int fatherElem;
	size_t fatherIdx;
	fatherIdx = FATHER(_currentIndex);
	if(1 == _currentIndex)
	{
		return;
	}
	VectorGet(_heap->m_vector, _currentIndex, &currentElem);
	VectorGet(_heap->m_vector, fatherIdx, &fatherElem);
	if(currentElem > fatherElem)
	{
		swapInHeap(_heap, _currentIndex, fatherIdx);
		BubbleUp(_heap, fatherIdx);
	}
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
	ADTErr error;
	if(!CheckHeap(_heap))
	{
		return ERR_NOT_INITIALIZED;
	}
	error = VectorAdd(_heap->m_vector, _data);
	if(ERR_OK != error)
	{
		return error;
	}
	++_heap->m_heapSize;
	BubbleUp(_heap, _heap->m_heapSize);
	return ERR_OK;
}

/*------------------------------------*/

ADTErr HeapMax(Heap* _heap, int* _data)
{
	if(!CheckHeap(_heap))
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorGet(_heap->m_vector, 1, _data);
}

/*------------------------------------*/

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	ADTErr error;
	if(!CheckHeap(_heap))
	{
		return ERR_NOT_INITIALIZED;
	}
	/* swap the first and last element */
	error = swapInHeap(_heap, 1, _heap->m_heapSize);
	if(ERR_OK != error)
	{
		return error;
	}
	/* delete the last element and heapify*/
	VectorDelete(_heap->m_vector, _data);
	--_heap->m_heapSize;
	heapify(_heap, 0);
	return ERR_OK;
}

/*---------------------------------------*/

size_t HeapItemsNum(Heap* _heap)
{
	if(!CheckHeap(_heap))
	{
		return -1;
	}
	return _heap->m_heapSize;
}

/*---------------------------------------*/
void HeapPrint(Heap* _heap)
{
	VectorPrint(_heap->m_vector);
}

