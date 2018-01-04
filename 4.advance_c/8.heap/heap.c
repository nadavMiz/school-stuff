#include <stdlib.h>

#include "heap.h"
#include "genericVector.h"

#define HEAP_MAGIC_NUMBER 0X1111114 
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) (((i) - 1) / 2)
#define LAST_PARENT(heap) ((((heap)->m_size) / 2) - 1)
#define IS_NULL_HEAP(heap) ((NULL == (heap)) || (HEAP_MAGIC_NUMBER != (heap)->m_magicNumber))
#define IS_HEAP_EMPTY(heap) ((0 == (heap)->m_size))

struct Heap
{
	Vector* m_vector;
	size_t m_size;
	LessThanComparator m_pfLess;
	size_t m_magicNumber;
};

/*--------------------static functions----------------------------*/


static void swapInHeap(Heap *_heap, void* _a, void* _b, size_t _aIdx, size_t _bIdx)
{
	VectorSet(_heap->m_vector, _aIdx, _b);
	VectorSet(_heap->m_vector, _bIdx, _a);
}

/*--------------------------------------------------*/

static size_t getLargerChild(Heap* _heap, size_t _parntIdx, void** _destElem)
{
	void* leftElem;
	void* rightElem;
	/*there are no children*/
	if(_heap->m_size <= LEFT(_parntIdx))
	{
		return _heap->m_size;
	}
	
	VectorGet(_heap->m_vector, LEFT(_parntIdx), &leftElem);
	
	/*there is only left child so he is the biggest*/
	if(_heap->m_size <= RIGHT(_parntIdx))
	{
		*_destElem = leftElem;
		return LEFT(_parntIdx);
	}
	
	/*both childs exists so return the largest*/
	VectorGet(_heap->m_vector, RIGHT(_parntIdx), &rightElem);
	if(_heap->m_pfLess(leftElem, rightElem))
	{
		/*right is the largest*/
		*_destElem = rightElem;
		return  RIGHT(_parntIdx);
	}
	/*left is the largest*/
	*_destElem = leftElem;
	return LEFT(_parntIdx);
}

/*--------------------------------------------------*/

static void Heapify(Heap* _heap, size_t _parntIdx)
{
	void* parentElem;
	void* destElem;
	size_t destIdx;
	
	VectorGet(_heap->m_vector, _parntIdx, &parentElem);
	
	while(1)
	{
		destIdx = getLargerChild(_heap, _parntIdx, &destElem);
		
		/*if the parent is in the right place*/
		if(_heap->m_size == destIdx || _heap->m_pfLess(destElem, parentElem))
		{
			return;
		}
		
		/*if it isnt swap it and continue*/
		swapInHeap(_heap, parentElem, destElem, _parntIdx, destIdx);
		_parntIdx = destIdx;
	}
}

/*----------------------------------------------------*/

static void HeapifyVector(Heap* _heap)
{
	size_t currentParent;
	for(currentParent = LAST_PARENT(_heap); currentParent < _heap->m_size; --currentParent)
	{
		Heapify(_heap, currentParent);
	}
}


/*----------------------------------------------------*/

static void BubbleUp(Heap* _heap, size_t _index)
{
	void* childElem;
	void* parentElem;
	
	VectorGet(_heap->m_vector, _index, &childElem);
	
	/* while the element is not the root*/
	while(_index > 0)
	{
		VectorGet(_heap->m_vector, PARENT(_index), &parentElem);
		
		if(_heap->m_pfLess(childElem, parentElem))
		{
			break;
		}
		
		swapInHeap(_heap, childElem, parentElem, _index, PARENT(_index));
		
		_index = PARENT(_index);
	}
}

/*--------------main heap functions-----------------*/

Heap* Heap_Build(Vector* _vector, LessThanComparator _pfLess)
{
	Heap* newHeap;
	
	if(NULL == _vector || NULL == _pfLess)
	{
		return NULL;
	}
	
	newHeap = malloc(sizeof(Heap));
	if(NULL == newHeap)
	{
		return NULL;
	}
	
	/* initialized values */
	newHeap->m_vector = _vector;
	newHeap->m_magicNumber = HEAP_MAGIC_NUMBER;
	VectorItemsNum(_vector, &(newHeap->m_size));
	newHeap->m_pfLess = _pfLess;
	
	HeapifyVector(newHeap);
	return newHeap;
}

/*------------------------------------*/

Vector* Heap_Destroy(Heap** _heap)
{
	Vector* vec = (*_heap)->m_vector;
	
	/*destroy the vector*/
	(*_heap)->m_magicNumber = 0;
	free((*_heap));
	(*_heap) = NULL;
	
	return vec;
}

/*-------------------------------------*/

Heap_Result Heap_Insert(Heap* _heap, void* _element)
{
	size_t index;
	
	if(IS_NULL_HEAP(_heap))
	{
		return HEAP_NOT_INITIALIZED;
	}
	
	index = _heap->m_size;
	
	VectorAdd(_heap->m_vector,  _element);
	
	BubbleUp(_heap, index);
	++_heap->m_size;
	
	return HEAP_SUCCESS;
}

static void* ExtractMaxWithoutDelete(Heap* _heap)
{
	void* top;
	void* tmp;
	
	VectorGet(_heap->m_vector, 0, &top);
	VectorGet(_heap->m_vector, _heap->m_size - 1, &tmp);
	
	swapInHeap(_heap, top, tmp, 0, _heap->m_size - 1);
	--(_heap->m_size);
	
	Heapify(_heap, 0);
	
	return top;
}

const void* Heap_Peek(const Heap* _heap)
{
	void* top;
	if( IS_NULL_HEAP(_heap) || IS_HEAP_EMPTY(_heap))
	{
		
		return NULL;
	}
	VectorGet(_heap->m_vector, 0, &top);
	return top;
}

void* Heap_Extract(Heap* _heap)
{
	void* top;
	void* tmp;
	
	if(IS_NULL_HEAP(_heap) || IS_HEAP_EMPTY(_heap))
	{
		return NULL;
	}
	
	top = ExtractMaxWithoutDelete(_heap);
	VectorDelete(_heap->m_vector,  &tmp);
	
	return top;
}

size_t Heap_Size(const Heap* _heap)
{
	if(IS_NULL_HEAP(_heap))
	{
		return 0;
	}
	return _heap->m_size;
}

size_t Heap_ForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t count;
	void* elem;
	
	if(IS_NULL_HEAP(_heap) || NULL == _act)
	{
		return 0;
	}
	
	for(count = 0; count < _heap->m_size; ++count)
	{
		VectorGet(_heap->m_vector, count, &elem);
		if(0 == _act(elem, _context))
		{
			break;
		}
	}
	
	return count;
}

void Heap_Sort(Vector* _vec, LessThanComparator _pfLess)
{
	Heap* heap;
	size_t i;
	size_t size;
	
	if(NULL == _vec)
	{
		return;
	}
	
	heap = Heap_Build(_vec, _pfLess);
	
	size = heap->m_size;
	
	for(i = 0; i < size; ++i)
	{
		ExtractMaxWithoutDelete(heap);
	}
	
	Heap_Destroy(&heap);
}

/*---------------test functions-----------*/

Vector* GetVector(Heap* _heap)
{
	return _heap->m_vector;
}
