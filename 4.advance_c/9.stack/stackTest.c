#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "doubleLinkedList.h"

#define STACK_SIZE 10000

typedef enum
{
	PASSED,
	FAILED
} Result;

/*----------------user defined functions------------------*/

int destroyer(void* _data, void* _dummy)
{
	free((int*)_data);
	return 1;
}

int PrintFunc(void* _data, void* _dummy)
{
	printf("%d ", *((int*)_data));
	return 1;
}

/*-------------helper functions-------------------*/

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

/*------------------main test functions--------------------*/

void TestCreate()
{
	char testName[] = "create stack";
	Stack* stack;
	stack = StackCreate();
	if(NULL != stack)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(PASSED, testName);
	}
	StackDestroy(&stack, destroyer);
}

void TestStackPush()
{
	char testName[] = "stack push";
	Stack* stack;
	size_t i;
	int* elem;
	StackError error;
	Result result = PASSED;
	
	stack = StackCreate();
	for(i = 0; i < 10; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = (int)i;
		error = StackPush(stack, elem);
		if(STACK_OK != error)
		{
			result = FAILED;
			break;
		}
	}
	/*StackPrint(stack, PrintFunc);*/
	PrintTest(result, testName);
	StackDestroy(&stack, destroyer);
}

void TestStackNull()
{
	char testName[] = "stack push null";
	int elem = 5;
	StackError error;
	
	error = StackPush(NULL, &elem);
	if(STACK_UNINITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(PASSED, testName);
	}
}

int main()
{
	TestCreate();
	TestStackPush();
	TestStackNull();
	return 1;
}
