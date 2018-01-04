#include <stdio.h>

#include "myalloc.h"
#include "mu_test.h"

#define SIZE_OF_CHUNK (sizeof(int))
#define NUM_OF_CHUNKS 10  


UNIT(createBuffer)
	Buffer* buffer = CreateBuffer(SIZE_OF_CHUNK, NUM_OF_CHUNKS);
	ASSERT_THAT(NULL != buffer);
	DestroyBuffer(buffer);
END_UNIT

UNIT(myAllocOneAllocation)
	Buffer* buffer;
	int* dataPtr;
	
	buffer = CreateBuffer(SIZE_OF_CHUNK, NUM_OF_CHUNKS);
	dataPtr = MyAlloc(buffer);
	*dataPtr = 5;
	
	ASSERT_THAT(NULL != dataPtr);
	DestroyBuffer(buffer);
END_UNIT

UNIT(myAllocUntillFull)
	Buffer* buffer;
	size_t i;
	
	buffer = CreateBuffer(SIZE_OF_CHUNK, NUM_OF_CHUNKS);
	
	for(i = 0; i < NUM_OF_CHUNKS; ++i)
	{
		ASSERT_THAT(NULL != MyAlloc(buffer));
	}
	
	ASSERT_THAT(NULL == MyAlloc(buffer));
	DestroyBuffer(buffer);
END_UNIT

UNIT(myFreeNormal)
	Buffer* buffer;
	size_t i;
	int* data1;
	int* data2;
	
	buffer = CreateBuffer(SIZE_OF_CHUNK, NUM_OF_CHUNKS);
	
	/*do the mallocs*/
	for(i = 0; i < NUM_OF_CHUNKS - 5; ++i)
	{
		MyAlloc(buffer);
	}
	data1 = MyAlloc(buffer);
	for(i = 0; i < 4; ++i)
	{
		MyAlloc(buffer);
	}
	
	/*check the free*/
	myFree(buffer, data1);
	data2 = MyAlloc(buffer);
	ASSERT_THAT(data2 == data1);
	ASSERT_THAT(NULL == MyAlloc(buffer));
	
	DestroyBuffer(buffer);
END_UNIT

UNIT(DoubleFree)
	Buffer* buffer;
	size_t i;
	int* data1;
	int* data2;
	
	buffer = CreateBuffer(SIZE_OF_CHUNK, NUM_OF_CHUNKS);
	
	/*do the mallocs*/
	for(i = 0; i < NUM_OF_CHUNKS - 5; ++i)
	{
		MyAlloc(buffer);
	}
	data1 = MyAlloc(buffer);
	for(i = 0; i < 4; ++i)
	{
		MyAlloc(buffer);
	}
	
	/*check the free*/
	myFree(buffer, data1);
	myFree(buffer, data1);
	data2 = MyAlloc(buffer);
	ASSERT_THAT(data2 == data1);
	ASSERT_THAT(NULL == MyAlloc(buffer));
	
	DestroyBuffer(buffer);
END_UNIT

UNIT(wildTest)
	Buffer* buffer;
	int* arr[NUM_OF_CHUNKS];
	size_t i;
	
	buffer = CreateBuffer(SIZE_OF_CHUNK, NUM_OF_CHUNKS);
	
	for(i = 0; i < NUM_OF_CHUNKS; ++i)
	{
		arr[i] = MyAlloc(buffer);
		*(arr[i]) = (int)i;
	}
	
	for(i = 0; i < 3; ++i)
	{
		myFree(buffer, arr[1]);
		myFree(buffer, arr[5]);
		myFree(buffer, arr[0]);
		myFree(buffer, arr[9]);
	}
	
	for(i = 0; i < 4; ++i)
	{
		ASSERT_THAT(NULL != MyAlloc(buffer));
	}
	ASSERT_THAT(NULL == MyAlloc(buffer));
	ASSERT_THAT(NULL == MyAlloc(buffer));
	
	DestroyBuffer(buffer);
END_UNIT

UNIT(NoChunksAlloc)
	Buffer* buffer;
	
	buffer = CreateBuffer(SIZE_OF_CHUNK, 0);
	ASSERT_THAT(NULL == MyAlloc(buffer));
	
	DestroyBuffer(buffer);
END_UNIT

TEST_SUITE(My Alloc test)
	TEST(createBuffer)
	TEST(myAllocOneAllocation)
	TEST(myAllocUntillFull)
	TEST(myFreeNormal)
	TEST(DoubleFree)
	TEST(wildTest)
	TEST(NoChunksAlloc)
END_SUITE
