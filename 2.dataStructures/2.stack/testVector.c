#include <stdio.h>
#include "vector.h"
#include "ADTErr.h"

void printResult(int testReasult, char* testName)
{
	if(testReasult)
	{
		printf("PASSED: %s \n", testName);
	}
	else
	{
		printf("FAILED: %s \n", testName);
	}
}

void testVectorCreateNormal()
{
	Vector* myVec;
	int intial_size = 15;
	int block_size = 10;
	myVec = VectorCreate(intial_size, block_size);
	if(!myVec || !(*myVec).m_items || (*myVec).m_originalSize != intial_size || (*myVec).m_size != intial_size ||
      (*myVec).m_nItems != 0 || (*myVec).m_blockSize != block_size)
	{
		printf("FAILED create vector normal \n");
	}
	else
	{
		printf("PASSED create vector normal \n");
	}
	VectorDestroy(myVec);
}

void testCreateVectorZeroCapacity()
{
	Vector* myVec;
	int intial_size = 0;
	int block_size = 10;
	myVec = VectorCreate(intial_size, block_size);
	if(!myVec || !(*myVec).m_items || (*myVec).m_originalSize != intial_size || (*myVec).m_size != intial_size ||
      (*myVec).m_nItems != 0 || (*myVec).m_blockSize != block_size)
	{
		printf("FAILED create vector no capacity \n");
	}
	else
	{
		printf("PASSED create vector no capacity \n");
	}
	VectorDestroy(myVec);
}

void testVectorCreateNoBlockSize()
{
	Vector* myVec;
	int intial_size = 15;
	int block_size = 0;
	myVec = VectorCreate(intial_size, block_size);
	if(!myVec || !(*myVec).m_items || (*myVec).m_originalSize != intial_size || (*myVec).m_size != intial_size ||
      (*myVec).m_nItems != 0 || (*myVec).m_blockSize != block_size)
	{
		printf("FAILED create vector no block size \n");
	}
	else
	{
		printf("PASSED create vector no block size \n");
	}
	VectorDestroy(myVec);
}

void testCreateVectorInvalidInput()
{
	Vector* myVec;
	int intial_size = -15;
	int block_size = -10;
	myVec = VectorCreate(intial_size, block_size);
	if(myVec)
	{
		printf("FAILED create vector invalid input \n");
	}
	else
	{
		printf("PASSED create vector invalid input \n");
	}
	VectorDestroy(myVec);
}

void testVectorAddNormal()
{
	int i;
	Vector* myVec;
	myVec = VectorCreate(15, 10);
	for(i = 0; i < 3; ++i)
	{
		VectorAdd(myVec,  i);
	}
	if ((*myVec).m_items[0] != 0 || (*myVec).m_items[1] != 1 || (*myVec).m_items[2] != 2)
	{
		printf("FAILED add normal\n");
	}
	else
	{
		printf("PASSED add normal\n");
	}
	VectorDestroy(myVec);
}

void testVectorAddNoBlockSize()
{
	int i;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(2, 0);
	for(i = 0; i < 3; ++i)
	{
		error = VectorAdd(myVec,  i);
	}
	if (error != ERR_OVERFLOW)
	{
		printf("FAILED add no block size NULL\n");
	}
	else
	{
		printf("PASSED add no block size NULL\n");
	}	
	VectorDestroy(myVec);
}
void testVectorAddWithRealoc()
{
	int i;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(2, 3);
	for(i = 0; i < 3; ++i)
	{
		error = VectorAdd(myVec,  i);
	}
	if (error == ERR_OK && (*myVec).m_items[2] == 2 && (*myVec).m_size > 2)
	{
		printf("PASSED add with realocate\n");
	}
	else
	{
		printf("FAILED add with realocate\n");
	}
	VectorDestroy(myVec);
}

void testVectorAddNoCapacity()
{
	int i;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(0, 3);
	for(i = 0; i < 3; ++i)
	{
		error = VectorAdd(myVec,  i);
	}
	if (error == ERR_OK && (*myVec).m_items[2] == 2 && (*myVec).m_size > 0)
	{
		printf("PASSED add no capacity \n");
	}
	else
	{
		printf("FAILED add no capacity \n");
	}
	VectorDestroy(myVec);
}
void testVectorAddInvalidVector()
{
	ADTErr error;
	Vector* myVec;
	error = VectorAdd(myVec,  2);
	if (error != ERR_NOT_INITIALIZED)
	{
		printf("FAILED add NULL vector\n");
	}
	else
	{
		printf("PASSED add NULL vector\n");
	}
	VectorDestroy(myVec);	
}

void testVectorDelete()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(15, 10);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorDelete(myVec,  &result);
	if (error == ERR_OK && result == 4 && (*myVec).m_nItems == 4)
	{
		printf("PASSED delete normal\n");
	}
	else
	{
		printf("FAILED delete normal\n");
	}
	VectorDestroy(myVec);
}
void testVectorDeleteEmpty()
{
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(15, 10);
	error = VectorDelete(myVec,  &result);
	if (error == ERR_UNDERFLOW)
	{
		printf("PASSED delete empty vector\n");
	}
	else
	{
		printf("FAILED delete empty vector\n");
	}
	VectorDestroy(myVec);
}
void testVectorDeleteNullDest()
{
	int i;
	int* result = NULL;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(15, 10);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorDelete(myVec,  result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED delete no destination int\n");
	}
	else
	{
		printf("FAILED delete no destination int\n");
	}
	VectorDestroy(myVec);
}
void testVectorDeleteNullVector()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorDelete(myVec,  &result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED delete NULL vector int\n");
	}
	else
	{
		printf("FAILED delete NULL vector int\n");
	}
	VectorDestroy(myVec);
}

void testVectorDeleteWithRealoc()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(5, 5);
	for(i = 0; i < 16; ++i)
	{
		VectorAdd(myVec,  i);
	}
	for(i = 0; i < 7; ++i)
	{
		error = VectorDelete(myVec,  &result);
	}
	if (error == ERR_OK && result == 9 && (*myVec).m_nItems == 9 && (*myVec).m_size == 15)
	{
		printf("PASSED delete with realoc\n");
	}
	else
	{
		printf("FAILED delete with realoc\n");
	}
	VectorDestroy(myVec);
}

void testVectorDeleteWithRealocLessThanCapacity()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(5, 5);
	for(i = 0; i < 16; ++i)
	{
		VectorAdd(myVec,  i);
	}
	for(i = 0; i < 7; ++i)
	{
		error = VectorDelete(myVec,  &result);
	}
	if (error == ERR_OK && result == 9 && (*myVec).m_nItems == 9 && (*myVec).m_size == 15)
	{
		printf("PASSED delete with realoc\n");
	}
	else
	{
		printf("FAILED delete with realoc\n");
	}
	VectorDestroy(myVec);
}

void testVectorGet()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorGet(myVec , 2, &result);
	if (error == ERR_OK && result == 1)
	{
		printf("PASSED get normal\n");
	}
	else
	{
		printf("FAILED get normal\n");
	}
	VectorDestroy(myVec);
}

void testVectorGetIndexTooSmall()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorGet(myVec , 0, &result);
	if (error == ERR_UNDERFLOW)
	{
		printf("PASSED get too small index\n");
	}
	else
	{
		printf("FAILED get too small index\n");
	}
	VectorDestroy(myVec);
}

void testVectorGetIndexTooLarge()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorGet(myVec , 15, &result);
	if (error == ERR_OVERFLOW)
	{
		printf("PASSED get too large index\n");
	}
	else
	{
		printf("FAILED get too large index\n");
	}
	VectorDestroy(myVec);
}

void testVectorGetNULLvector()
{
	int i;
	int result;
	ADTErr error;
	Vector* myVec;
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorGet(myVec , 2, &result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED get NULL vector\n");
	}
	else
	{
		printf("FAILED NULL vector\n");
	}
	VectorDestroy(myVec);
}

void testVectorSet()
{
	int i;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorSet(myVec , 2, 6);
	if (error == ERR_OK && (*myVec).m_items[1] == 6)
	{
		printf("PASSED set normal\n");
	}
	else
	{
		printf("FAILED set normal\n");
	}
	VectorDestroy(myVec);
}

void testVectorSetInvalidTooSmall()
{
	int i;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorSet(myVec , 0, 6);
	if (error == ERR_UNDERFLOW)
	{
		printf("PASSED set normal index too small\n");
	}
	else
	{
		printf("FAILED set normal index too small\n");
	}
	VectorDestroy(myVec);
}

void testVectorSetInvalidTooLarge()
{
	int i;
	ADTErr error;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorSet(myVec , 15, 6);
	if (error == ERR_OVERFLOW)
	{
		printf("PASSED set normal index too large\n");
	}
	else
	{
		printf("FAILED set normal index too large\n");
	}
	VectorDestroy(myVec);
}

void testVectorSetNULLvector()
{
	int i;
	ADTErr error;
	Vector* myVec;
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorSet(myVec , 3, 6);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED set null vector\n");
	}
	else
	{
		printf("FAILED set null vector\n");
	}
	VectorDestroy(myVec);
}

void testVectorItemsNum()
{
	int i;
	ADTErr error;
	int result;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorItemsNum(myVec, &result);
	if (error == ERR_OK && (*myVec).m_nItems == 5)
	{
		printf("PASSED number of items\n");
	}
	else
	{
		printf("FAILED number of items\n");
	}
	VectorDestroy(myVec);
}
void testVectorItemsNumNULLVector()
{
	int i;
	ADTErr error;
	int result;
	Vector* myVec;
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorItemsNum(myVec, &result);
	if (error == ERR_OK && (*myVec).m_nItems == 5)
	{
		printf("PASSED number of items NULL vector\n");
	}
	else
	{
		printf("FAILED number of items NULL vector\n");
	}
	VectorDestroy(myVec);
}

void testVectorItemsNumNULLdest()
{
	int i;
	ADTErr error;
	int* result = NULL;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		VectorAdd(myVec,  i);
	}
	error = VectorItemsNum(myVec, result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED number of items NULL dest\n");
	}
	else
	{
		printf("FAILED number of items NULL dest\n");
	}
	VectorDestroy(myVec);
}

void wildTest()
{
	int i;
	int result;
	Vector* myVec;
	myVec = VectorCreate(10, 5);
	for(i = 0; i < 20; ++i)
	{
		VectorAdd(myVec,  i);
	}
	for(i = 0; i < 7; ++i)
	{
		VectorDelete(myVec,  &result);
		if (result != 19 - i)
		{
			printf("FAILED wild test0\n");
			return;
		}
	}
	VectorGet(myVec, 2, &result);
	if(result != 1)
	{
		printf("FAILED wild test1\n");
		return;
	}
	for(i = 0; i < 30; ++i)
	{
		VectorDelete(myVec,  &result);
	}
	VectorItemsNum(myVec, &result);
	if(result != 0)
	{
		printf("FAILED wild test2\n");
	}
	else
	{
		printf("PASSED wild test\n");
	}
}
	
int main() 
{
	testVectorCreateNormal();
	testVectorCreateInvalidInput();
	testVectorCreateZeroCapacity();
	testVectorCreateNoBlockSize();

	testVectorAddNormal();
	testVectorAddNoBlockSize();
	testVectorAddWithRealoc();
	testVectorAddNoCapacity();
	testVectorAddInvalidVector();

	testVectorItemsNum();
	testVectorItemsNumNULLVector();
	testVectorItemsNumNULLdest();
	/* testItemsNumMoreThanOriginalSize() */

	testVectorGet();
	testVectorGetIndexTooSmall();
	testVectorGetIndexTooLarge();
	testVectorGetNULLvector();

	testVectorSet();
	testVectorSetInvalidTooSmall();
	testVectorSetInvalidTooLarge();
	testVectorSetNULLvector();

	testVectorDelete();
	testVectorDeleteEmpty();
	testVectorDeleteNullDest();
	testVectorDeleteNullVector();
	testVectorDeleteWithRealoc();
	/* testVectorDeleteWithMultipleVector()*/
	testVectorDeleteWithRealocLessThanCapacity();
	wildTest();

	return 0;
}

