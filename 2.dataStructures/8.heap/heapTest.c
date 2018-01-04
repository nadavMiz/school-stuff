#include <stdio.h>
#include "heap.h"
#include "ADTErr.h"

typedef enum
{
	PASSED,
	FAILED
} Result;

void static PrintTest(Result _result, char* _testName, Heap* _toPrint)
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
	if(NULL != _toPrint)
	{
		HeapPrint(_toPrint);
	}
}

static Heap* BuildNormalHeap()
{
	Vector* vector;
	vector = VectorCreate(10, 5);
	VectorAdd(vector,  5);
	VectorAdd(vector,  7);
	VectorAdd(vector,  3);
	VectorAdd(vector,  9);
	VectorAdd(vector,  1);
	VectorAdd(vector,  5);
	VectorAdd(vector,  10);
	VectorAdd(vector,  2);
	return HeapBuild(vector);
}

void TestHeapBuildEmpty()
{
	Result result = FAILED;
	Vector* vector;
	Heap* heap;
	vector = VectorCreate(10, 5);
	heap = HeapBuild(vector);
	if(NULL != heap)
	{
		result = PASSED;
	}
	PrintTest(result, "buid heap empty \n", NULL);
	HeapDestroy(heap);
}

void TestHeapBuildNormal()
{
	Result result;
	Heap* heap;
	heap = BuildNormalHeap();
	if(NULL != heap)
	{
		result = PASSED;
	}
	PrintTest(result, "buid heap normal \n", heap);
	HeapDestroy(heap);
}

void TestHeapBuildNull()
{
	Result result = FAILED;
	Heap* heap;
	heap = HeapBuild(NULL);
	if(NULL == heap)
	{
		result = PASSED;
	}
	PrintTest(result, "buid heap NULL pointer \n", NULL);
}

void TestHeapDestroyNull()
{
	HeapDestroy(NULL);
	PrintTest(PASSED, "destroy heap NULL pointer \n", NULL);
}

void TestHeapDestroytwice()
{
	Heap* heap;
	heap = BuildNormalHeap();
	HeapDestroy(heap);
	HeapDestroy(heap);
	PrintTest(PASSED, "destroy heap twice \n", NULL);
}

void TestTreeInsertEmpty()
{
	Result result = FAILED;
	ADTErr error;
	Vector* vector;
	Heap* heap;
	vector = VectorCreate(10, 5);
	heap = HeapBuild(vector);
	error = HeapInsert(heap, 5);
	if(ERR_OK == error)
	{
		result = PASSED;
	}
	PrintTest(result, "insert element empty tree \n", NULL);
	HeapDestroy(heap);
}

void TestInsertNormal()
{
	ADTErr error;
	Result result = FAILED;
	Heap* heap;
	heap = BuildNormalHeap();
	error = HeapInsert(heap, 2);
	error = HeapInsert(heap, 7);
	error = HeapInsert(heap, 11);
	if(ERR_OK == error)
	{
		result = PASSED;
	}
	PrintTest(result, "insert element normal \n", heap);
	HeapDestroy(heap);
}

void TestTreeInsertNullTree()
{
	ADTErr error;
	Result result = FAILED;
	error = HeapInsert(NULL, 2);
	if(ERR_NOT_INITIALIZED == error)
	{
		result = PASSED;
	}
	PrintTest(result, "insert element NULL tree \n", NULL);
}

void TestHeapMaxNormal()
{
	ADTErr error;
	int maxNum;
	Result result = FAILED;
	Heap* heap;
	heap = BuildNormalHeap();
	error = HeapMax(heap, &maxNum);
	if(ERR_OK == error && 10 == maxNum)
	{
		result = PASSED;
	}
	PrintTest(result, "get max number normal \n", NULL);
}

void TestHeapMaxEmpty()
{
	ADTErr error;
	int maxNum;
	Result result = FAILED;
	Vector* vector;
	Heap* heap;
	vector = VectorCreate(10, 5);
	heap = HeapBuild(vector);
	error = HeapMax(heap, &maxNum);
	if(ERR_OVERFLOW == error)
	{
		result = PASSED;
	}
	PrintTest(result, "get max number empty heap \n", NULL);
}

void TestHeapMaxNullTree()
{
	Result result = FAILED;
	ADTErr error;
	int maxNum;
	error = HeapMax(NULL, &maxNum);
	if(ERR_NOT_INITIALIZED == error)
	{
		result = PASSED;
	}
	PrintTest(result, "get max number NULL heap \n", NULL);
}

void TestHeapExtractMaxNormal()
{
	ADTErr error;
	int maxNum;
	Result result = FAILED;
	Heap* heap;
	heap = BuildNormalHeap();
	error = HeapExtractMax(heap, &maxNum);
	if(ERR_OK == error && 10 == maxNum)
	{
		result = PASSED;
	}
	PrintTest(result, "get max number normal \n", NULL);
}

void TestHeapExtractMaxEmpty()
{
	ADTErr error;
	int maxNum;
	Result result = FAILED;
	Vector* vector;
	Heap* heap;
	vector = VectorCreate(10, 5);
	heap = HeapBuild(vector);
	error = HeapExtractMax(heap, &maxNum);
	if(ERR_OVERFLOW == error)
	{
		result = PASSED;
	}
	PrintTest(result, "get max number empty heap \n", NULL);
}

void TestHeapExtractMaxNullTree()
{
	Result result = FAILED;
	ADTErr error;
	int maxNum;
	error = HeapExtractMax(NULL, &maxNum);
	if(ERR_NOT_INITIALIZED == error)
	{
		result = PASSED;
	}
	PrintTest(result, "get max number NULL heap \n", NULL);
}

int main()
{
	
	TestHeapBuildEmpty();
	TestHeapBuildNormal();
	TestHeapBuildNull();
	
	TestHeapDestroyNull();
	TestHeapDestroytwice();
	
	TestTreeInsertEmpty();
	TestInsertNormal();
	TestTreeInsertNullTree();
	
	TestHeapMaxNormal();
	TestHeapMaxEmpty();
	TestHeapMaxNullTree();
	
	TestHeapExtractMaxNormal();
	TestHeapExtractMaxEmpty();
	TestHeapExtractMaxNullTree();
	
	/*
	TestHeapItemsNumNormal();
	TestHeapItemsNumempty();
	TestHeapItemsNumNotInitialized();
	*/
	
	return 1;
}
