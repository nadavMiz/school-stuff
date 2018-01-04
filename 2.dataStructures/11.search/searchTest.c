#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"

#define DEFAULT_ARRAY_SIZE 50000
#define SEARCH_VAL 16555 

/*---------------helper functions----------------*/

/*prints test results*/
static void PrintTest(int _result, char* _testName)
{
	switch(_result)
	{
		case 0:
			printf("FAILED %s\n", _testName);
			break;
		case 1:
			printf("PASSED %s\n",_testName);
			break;
			
	}
}

/*build array of size _capacity of ascending values*/
static int* BuildArrayAscending(size_t _capacity)
{
	int i;
	int* array = malloc((_capacity + 1) * sizeof(int));
	for(i = 0; i < _capacity; ++i)
	{
		array[i] = i;
	}
	return array;
}

static int* BuildRandomArray(size_t _capacity, int _maxNum, int _offset)
{
	int i;
	int* array = malloc((_capacity + 1) * sizeof(int));
	srand(time(NULL));
	for(i = 0; i < _capacity; ++i)
	{
		array[i] = _offset + rand() % _maxNum;
	}
	return array;
	
}

double TimeSearch(int* _array, int* _searchArray, size_t arrayLength, size_t _numSearches, SearchFunc _searchFunc)
{
	clock_t beginClock, endClock;
	size_t i;
	beginClock = clock();
	for(i = 0; i < _numSearches; ++i)
	{
		_searchFunc(_array, arrayLength, _searchArray[i]);
	}
	endClock = clock();
	return (double)(endClock - beginClock) / CLOCKS_PER_SEC;
}

/*------------------main test functions-----------------*/

void TestLinearSearch()
{
	int* array;
	char testName[30] = "linear search";
	
	array = BuildArrayAscending(DEFAULT_ARRAY_SIZE);
	if(LinearSearch(array, DEFAULT_ARRAY_SIZE, SEARCH_VAL) && !LinearSearch(array, DEFAULT_ARRAY_SIZE, -5))
	{
		PrintTest(1, testName);
	}
	else
	{
		PrintTest(0, testName);
	}
	free(array);
}

/*---------------------------------------*/

void TestlinearSearchAdapted()
{
	int* array;
	char testName[30] = "modified linear search";
	
	array = BuildArrayAscending(DEFAULT_ARRAY_SIZE);
	if(ModifiedLinearSearch(array, DEFAULT_ARRAY_SIZE, SEARCH_VAL) && !ModifiedLinearSearch(array, DEFAULT_ARRAY_SIZE, -5))
	{
		PrintTest(1, testName);
	}
	else
	{
		PrintTest(0, testName);
	}
	free(array);
}

void TestProportionalSearch()
{
	int* array;
	char testName[30] = "Proportional Search";
	
	array = BuildArrayAscending(DEFAULT_ARRAY_SIZE);
	array[4000] = 3999;
	if(ProportionalSearch(array, DEFAULT_ARRAY_SIZE, SEARCH_VAL) && !ProportionalSearch(array, DEFAULT_ARRAY_SIZE, 4000) &&
	   ProportionalSearch(array, DEFAULT_ARRAY_SIZE, 0) && ProportionalSearch(array, DEFAULT_ARRAY_SIZE, 9999))
	{
		PrintTest(1, testName);
	}
	else
	{
		PrintTest(0, testName);
	}
	free(array);
}

void TestJumpSearch()
{
	int* array;
	char testName[30] = "jump Search";
	
	array = BuildArrayAscending(DEFAULT_ARRAY_SIZE);
	array[4000] = 3999;
	if(JumpSearch(array, DEFAULT_ARRAY_SIZE, SEARCH_VAL) && !JumpSearch(array, DEFAULT_ARRAY_SIZE, 4000) &&
	   JumpSearch(array, DEFAULT_ARRAY_SIZE, 0) && JumpSearch(array, DEFAULT_ARRAY_SIZE, 9999))
	{
		PrintTest(1, testName);
	}
	else
	{
		PrintTest(0, testName);
	}
	free(array);
}

/*--------------time mesurement functions--------------------*/
void testLinearVsAdapted(size_t _numSearches)
{
	int* array;
	int* searchArray;
	double linearTime, modifiedTime;
	array = BuildRandomArray(DEFAULT_ARRAY_SIZE, DEFAULT_ARRAY_SIZE, 0);
	searchArray = BuildRandomArray(_numSearches, 10000, 30000);
	linearTime = TimeSearch(array, searchArray, DEFAULT_ARRAY_SIZE, _numSearches, LinearSearch);
	modifiedTime = TimeSearch(array, searchArray, DEFAULT_ARRAY_SIZE, _numSearches, ModifiedLinearSearch);
	printf("time for: %d searches. linear: %f, modified: %f\n", (int)_numSearches, linearTime, modifiedTime);
}

void testJumpVsProportionalVsLinear(size_t _numSearches)
{
	int* array;
	int* searchArray;
	double linearTime, jumpTime, ProportionalTime;
	array = BuildRandomArray(DEFAULT_ARRAY_SIZE, DEFAULT_ARRAY_SIZE, 0);
	searchArray = BuildRandomArray(_numSearches, DEFAULT_ARRAY_SIZE, 0);
	linearTime = TimeSearch(array, searchArray, DEFAULT_ARRAY_SIZE, _numSearches, LinearSearch);
	jumpTime = TimeSearch(array, searchArray, DEFAULT_ARRAY_SIZE, _numSearches, JumpSearch);
	ProportionalTime = TimeSearch(array, searchArray, DEFAULT_ARRAY_SIZE, _numSearches, ProportionalSearch);
	printf("time for: %d searches. linear: %f, jump: %f, proportional: %f\n", (int)_numSearches, linearTime, jumpTime, ProportionalTime);
}


int main()
{
	TestLinearSearch();
	TestlinearSearchAdapted();
	TestProportionalSearch();
	TestJumpSearch();
	testLinearVsAdapted(200000);
	testJumpVsProportionalVsLinear(200000);
	return 1;
}
