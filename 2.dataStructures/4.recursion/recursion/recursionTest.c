#include <string.h>
#include <stdio.h>
#include "recursion.h"
#include "ADTErr.h"


typedef enum 
{
	PASSED,
	FAILED
} Result;
/*******************helper functions******************/
void PrintTest(Result _result, char* _testName)
{
	if(PASSED == _result)
	{
		printf("PASSED %s\n", _testName);
	}
	else if(FAILED == _result)
	{
		printf("FAILED %s\n", _testName);
	}
}

/******************test functions***********************/
void TestbinarySearchNormal()
{
	Result result;
	int* dest;
	int array[6] = {1,2,3,4,5,6};
	dest = RecursBinarySearch(array, 6, 2);
	if(NULL != dest && *dest == 2)
	{
		result = PASSED;
	}
	else
	{
		result = FAILED;
	}
	PrintTest(result, "binary search normal");
}

void TestbinarySearchSearchValNotPresent()
{
	Result result;
	int* dest;
	int array[6] = {1,2,3,4,5,6};
	dest = RecursBinarySearch(array, 6, 9);
	if(dest == NULL)
	{
		result = PASSED;
	}
	else
	{
		result = FAILED;
	}
	PrintTest(result, "binary search search value not present");
}

void TestbinarySearchAtBeginning()
{
	Result result;
	int* dest;
	int array[6] = {1,2,3,4,5,6};
	dest = RecursBinarySearch(array, 6, 1);
	if(*dest == 1)
	{
		result = PASSED;
	}
	else
	{
		result = FAILED;
	}
	PrintTest(result, "binary search at beginning");
}

void TestbinarySearchAtEnd()
{
	Result result;
	int* dest;
	int array[6] = {1,2,3,4,5,6};
	dest = RecursBinarySearch(array, 6, 6);
	if(*dest == 6)
	{
		result = PASSED;
	}
	else
	{
		result = FAILED;
	}
	PrintTest(result, "binary search at end");
}

void TestReverse()
{
	int i = 0;
	int lastIdx = 0;
	Result result = PASSED;
	char reverse[5];
	char string[5] = "apple";
	RecusStringReverse(string, reverse);
	lastIdx = strlen(string) - 1;
	while(lastIdx > i)
	{
		if(string[i] != reverse[lastIdx])
		{
			result = FAILED;
			break;
		}
		++i;
		--lastIdx;
	}
	PrintTest(result, "reverse string");
	
}

void TestHanoi(int _isPrinted)
{
	Result result = FAILED;
	ADTErr error;
	error = Hanoi(6, _isPrinted);
	if(ERR_OK == error)
	{
		result = PASSED;
	}
	PrintTest(result, "hanoi towers");
}

void TestHanoiEmpty(int _isPrinted)
{
	Result result = FAILED;
	ADTErr error;
	error = Hanoi(0, _isPrinted);
	if(ERR_OK == error)
	{
		result = PASSED;
	}
	PrintTest(result, "hanoi towers empty");
}

void TestFindMaxNormal()
{
	ADTErr error;
	Result result = FAILED;
	int dest;
	int array[6] = {1, 2, 3, 6, 5, 4};
	error = FindMax(array, 6, &dest);
	if(ERR_OK == error && dest == 6)
	{
		result = PASSED;
	}
	PrintTest(result, "find max normal");
}

void TestFindMaxBeginning()
{
	ADTErr error;
	Result result = FAILED;
	int dest;
	int array[6] = {6, 2, 3, 4, 5, 1};
	error = FindMax(array, 6, &dest);
	if(ERR_OK == error && dest == 6)
	{
		result = PASSED;
	}
	PrintTest(result, "find max beginning");
}

void TestFindMaxEnd()
{
	ADTErr error;
	Result result = FAILED;
	int dest;
	int array[6] = {1, 2, 3, 4, 5, 6};
	error = FindMax(array, 6, &dest);
	if(ERR_OK == error && dest == 6)
	{
		result = PASSED;
	}
	PrintTest(result, "find max end");
}

void TestFindMaxEmpty()
{
	ADTErr error;
	Result result = FAILED;
	int dest;
	int array[6] = {1, 2, 3, 4, 5, 6};
	error = FindMax(array, 0, &dest);
	if(ERR_EMPTY_ARRAY == error)
	{
		result = PASSED;
	}
	PrintTest(result, "find max empty array");
}

void TestFindMaxNULL()
{
	ADTErr error;
	Result result = FAILED;
	int dest;
	error = FindMax(NULL, 0, &dest);
	if(ERR_NOT_INITIALIZED == error)
	{
		result = PASSED;
	}
	PrintTest(result, "find max empty array");
}

void TestQueens(int _isPrintSolution)
{
	Result result = FAILED;
	int isSolved;
	int board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE] = {{0}};
	isSolved = Queens(board , 8, _isPrintSolution);
	if(isSolved)
	{
		result = PASSED;
	}
	PrintTest(result, "eight queens");
}

int main()
{
	TestbinarySearchNormal();
	TestbinarySearchSearchValNotPresent();
	TestbinarySearchAtBeginning();
	TestbinarySearchAtEnd();
	
	TestReverse();
	
	TestHanoi(1);
	TestHanoiEmpty(0);
	
	TestFindMaxNormal();
	TestFindMaxBeginning();
	TestFindMaxEnd();
	TestFindMaxEmpty();
	TestFindMaxNULL();
	TestQueens(1);
	return 0;
}
