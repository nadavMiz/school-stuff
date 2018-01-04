#include <stdio.h>
#include "hash.h"
#include "ADTErr.h"

typedef enum
{
	PASSED,
	FAILED
} Result;

/********helper functions**********/

static void PrintTest(Result _result, char* _testName, Hash* _toPrint)
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
		HashPrint(_toPrint);
	}
}

static Hash* BuiltFullHash()
{
	int i;
	size_t capacity = 10;
	Hash* hash;
	int elements[10] = {13, 26, 39, 65, 10, 7, 20, 9, 8, 34};
	hash = HashCreate(capacity);
	for(i = 0; i < capacity; ++i)
	{
		HashInsert(hash, elements[i]);
	}
	return hash;
}

/*----------test functions-------------*/

void TestInsertUntilFull()
{
	ADTErr error;
	size_t i;
	size_t capacity = 10;
	Hash* hash;
	int elements[10] = {13, 26, 39, 65, 10, 7, 20, 9, 8, 34};
	hash = HashCreate(capacity);
	for(i = 0; i < capacity; ++i)
	{
		error = HashInsert(hash, elements[i]);
		if(ERR_OK != error)
		{
			PrintTest(FAILED, "insert until full0", hash);
			HashDestroy(hash);
			return;
		}
	}
	for(i = 0; i < capacity; ++i)
	{
		if(!HashIsFound(hash, elements[i]))
		{
			PrintTest(FAILED, "insert until full1", hash);
			HashDestroy(hash);
			return;
		}
	}
	PrintTest(PASSED, "insert until full", NULL);
	HashDestroy(hash);
	return;
}

void TestInsertOverCapacity()
{
	ADTErr error;
	Hash* hash;
	hash = BuiltFullHash();
	error = HashInsert(hash, 66);
	if(ERR_OVERFLOW != error || HashIsFound(hash, 66))
	{
		PrintTest(FAILED, "insert over capacity", hash);
		HashDestroy(hash);
		return;
	}
	PrintTest(PASSED, "insert over capacity", NULL);
	HashDestroy(hash);
	return;
}

void TestDeleteAll()
{
	int i;
	ADTErr error;
	Hash* hash;
	int elements[10] = {13, 26, 39, 65, 10, 7, 20, 9, 8, 34};
	hash = BuiltFullHash();
	error = HashRemove(hash, -5);
	if(ERR_ELEM_NOT_EXISTS != error)
	{
		PrintTest(FAILED, "delete all0", hash);
		HashDestroy(hash);
		return;
	}
	for(i = 0; i < 10; ++i)
	{
		error = HashRemove(hash, elements[i]);
		if(ERR_OK != error || HashIsFound(hash, elements[i]))
		{
			PrintTest(FAILED, "delete all1", hash);
			HashDestroy(hash);
			return;
		}
	}
	PrintTest(PASSED, "delete all", NULL);
	HashDestroy(hash);
	return;
}


int main()
{
	/*normal tests*/
	
	TestInsertUntilFull();
	TestInsertOverCapacity();
	TestDeleteAll();
	/*TestInsertwithLoop();
	TestHashFindWithLargeMaxCapacity();
	*/
	/*extreme cases tests*/	
	return 1;
}
