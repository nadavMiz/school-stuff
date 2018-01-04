#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "genericVector.h"

#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)
#define LAST_PARENT(capacity) ((capacity) / 2 - 1)

#define HEAP_SIZE 10000

typedef enum
{
	PASSED,
	FAILED
} Result;

/*----------user functions---------------*/

int LestThan(int* _a, int* _b)
{
	return ((*_a) < (*_b));
}

int destroyer(void* _data, void* _dummy)
{
	free((int*)_data);
	return 1;
}

int predicate(void* _data, void* _toCompare)
{
	return(*((int*)_data) - *((int*)_toCompare));
}


int PrintFunc(void* _data, void* _dummy)
{
	printf("%d ", *((int*)_data));
	return 1;
}

/*--------------test helper functions------------------*/

static void PrintTest(Result _result, char* _testName)
{
	switch(_result)
	{
		case PASSED:
			printf("PASSED %s\n", _testName);
			break;
			
		case FAILED:
			printf("FAILED %s\n", _testName);
			break;
	}
}

static Heap* BuildHeap(size_t _capacity)
{
	Vector* vector;
	Heap* heap;
	int* element;
	size_t i;
	
	vector = VectorCreate(_capacity, 5);
	
	for(i = 0; i < _capacity; ++i)
	{
		element = malloc(sizeof(int));
		*element = rand();
		VectorAdd(vector,  element);
	}
	heap = Heap_Build(vector, (LessThanComparator)LestThan);
	return heap;
}

static void FullyDestroyHeap(Heap* _heap)
{
	Vector* vec = GetVector(_heap);
	
	VectorDestroy(&vec, destroyer);
	Heap_Destroy(&_heap);
}

static int checkHeap(Heap* _heap)
{
	size_t i;
	int *parent, *left, *right;
	Vector* vec;
	
	vec = GetVector(_heap);
	
	for(i = 0; i < LAST_PARENT(Heap_Size(_heap)); ++i)
	{
		VectorGet(vec, i, (void**)(&parent));
		VectorGet(vec, LEFT(i), (void**)(&left));
		VectorGet(vec, RIGHT(i), (void**)(&right));
		if(LestThan(parent, left) || LestThan(parent, right))
		{
			return 0;
		}
	}
	VectorGet(vec, i, (void**)(&parent));
	VectorGet(vec, LEFT(i), (void**)(&left));
	VectorGet(vec, RIGHT(i), (void**)(&right));
	
	if(LestThan(parent, left) || (RIGHT(i) < Heap_Size(_heap) && (LestThan(parent, right))))
	{
		return 0;
	}
	return 1;
}

int isSortedVector(Vector* _vector)
{
	size_t i, size;
	int *prev, *next;
	VectorItemsNum(_vector, &size);
	
	VectorGet(_vector, 0, (void**)(&prev));
	for(i = 1; i < size; ++i)
	{
		VectorGet(_vector, i, (void**)(&next));
		if(*prev > *next)
		{
			return 0;
		}
		prev = next;
	}
	return 1;
}

/*---------------main test functions---------------------*/

void TestBuildEmptyHeap()
{
	char testName[] = "build empty heap";
	Heap* heap;
	
	heap = BuildHeap(0);
	if(NULL != heap)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	FullyDestroyHeap(heap);
}

void TestBuildHeap()
{
	char testName[] = "build full heap";
	Heap* heap;
	
	heap = BuildHeap(HEAP_SIZE);
	if(checkHeap(heap))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	FullyDestroyHeap(heap);
}

void TestBuildNullHeap()
{
	char testName[] = "build null heap";
	Heap* heap1;
	Heap* heap2;
	Vector* vec = VectorCreate(1, 1);
	
	heap1 = Heap_Build(vec, NULL);
	heap2 = Heap_Build(NULL, (LessThanComparator)LestThan);
	
	if(NULL == heap1 && NULL == heap2)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, destroyer);
}

void TestInsertHeap()
{
	char testName[] = "insert to heap";
	Heap* heap;
	int* element;
	size_t i;
	
	heap = BuildHeap(0);
	for(i = 0; i < HEAP_SIZE; ++i)
	{
		element = malloc(sizeof(int));
		*element = rand();
		Heap_Insert(heap, element);
	}
	
	if(checkHeap(heap))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	FullyDestroyHeap(heap);
	
}

void TestInsertNull()
{
	char testName[] = "insert null";
	int elem = 5;
	Heap_Result error;
	
	error = Heap_Insert(NULL, &elem);
	if(HEAP_NOT_INITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestPeek()
{
	char testName[] = "peek heap";
	int* elem;
	int i;
	Heap* heap;
	
	heap = BuildHeap(0);
	for(i = 0; i < 10; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = i;
		Heap_Insert(heap, elem);
	}
	
	elem = (int*)Heap_Peek(heap);
	if(9 == *elem)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	FullyDestroyHeap(heap);
}

void TestPeekEmpty()
{
	char testName[] = "peek empty";
	Heap* heap;
	
	heap = BuildHeap(0);
	
	if(NULL == Heap_Peek(heap))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	FullyDestroyHeap(heap);
}

void TestPeekNull()
{
	char testName[] = "peek null";
	
	if(NULL == Heap_Peek(NULL))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void testHeapExtract()
{
	char testName[] = "extract max";
	Heap* heap;
	Result result = PASSED;
	int *currentElem, *prevElem;
	size_t i;
	
	heap = BuildHeap(HEAP_SIZE);
	prevElem = Heap_Extract(heap);
	for(i = 0; i < (HEAP_SIZE - 1); ++i)
	{
		currentElem = Heap_Extract(heap);
		if(*currentElem > *prevElem)
		{
			result = FAILED;
			break;
		}
		prevElem = currentElem;
	}
	PrintTest(result, testName);
	FullyDestroyHeap(heap);
}

void testHeapSort()
{
	char testName[] = "heap sort";
	Vector* vector;
	int* element;
	size_t i;
	
	vector = VectorCreate(HEAP_SIZE, 5);
	
	for(i = 0; i < HEAP_SIZE; ++i)
	{
		element = malloc(sizeof(int));
		*element = rand();
		VectorAdd(vector,  element);
	}
	
	Heap_Sort(vector, (LessThanComparator)LestThan);
	
	if(isSortedVector(vector))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vector, destroyer);
}

int main()
{
	TestBuildEmptyHeap();
	TestBuildHeap();
	TestBuildNullHeap();
	TestInsertHeap();
	TestInsertNull();
	TestPeek();
	TestPeekEmpty();
	TestPeekNull();
	testHeapExtract();
	testHeapSort();
	return 1;
}
