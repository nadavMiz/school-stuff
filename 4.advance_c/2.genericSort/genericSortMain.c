#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"

#include "genericSort.h"

#define ARR_LENGTH 10000

typedef enum 
{
	PASSED,
	FAILED
} Result;

typedef struct
{
	char m_name[10];
	size_t m_id;
} Person;

/*-------------------compare function-----------------*/

int BiggerThanInt(const void* first, const void* second)
{
	return (*((int*)first) > *((int*)second));
}

int SmallerThanInt(const void* first, const void* second)
{
	return (*((int*)second) > *((int*)first));
}

int biggerSinInt(const void* first, const void* second)
{
	return (sin(*((int*)first)) > sin(*((int*)second)));
}

/*---------------------------*/

int BiggerThanChar(const void* first, const void* second)
{
	return ((*(char*)first) > (*(char*)second));
}

int SmallerThanChar(const void* first, const void* second)
{
	return (*((char*)second) > *((char*)first));
}

int biggerSinChar(const void* first, const void* second)
{
	return (sin(*((char*)first)) > sin(*((char*)second)));
}

/*------------------------------*/

int BiggerThanPerson(const void* first, const void* second)
{
	return ((*(Person*)first).m_id > (*(Person*)second).m_id);
}

int SmallerThanPerson(const void* first, const void* second)
{
	return ((*(Person*)second).m_id > (*(Person*)first).m_id);
}

int biggerSinPerson(const void* first, const void* second)
{
	return (sin((*(Person*)first).m_id) > sin((*(Person*)second).m_id));
}

/*--------------------helper functions--------------------*/

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

int* createIntArr(size_t _capacity)
{
	size_t i;
	int* array;
	array = malloc(_capacity*sizeof(int));
	for(i = 0; i < _capacity; ++i)
	{
		array[i] = rand();
	}
	return array;
	
}

char* createCharArr(size_t _capacity)
{
	size_t i;
	char* array;
	array = malloc(_capacity*sizeof(char));
	for(i = 0; i < _capacity; ++i)
	{
		array[i] = (char)(rand() % 125);
	}
	return array;
}

Person* createPersonArr(size_t _capacity)
{
	size_t i;
	Person* array;
	array = malloc(_capacity*sizeof(Person));
	for(i = 0; i < _capacity; ++i)
	{
		strcpy(array[i].m_name, "Bob");
		array[i].m_id = (size_t)rand();
	}
	return array;
}


int isSorted(void* _array, size_t _elemSize , size_t length, CompareFunc _compare)
{
	size_t i;
	int* currentNum;
	int* nextNum;
	for(i = 0; i < length * _elemSize - _elemSize; i = i + _elemSize)
	{
		currentNum = (void*)(&((char*)_array)[i]);
		nextNum = (void*)(&((char*)_array)[i + _elemSize]);
		if(_compare(currentNum, nextNum))
		{
			return 0;
		}
	}
	return 1;
}

/*-----------main test functions-------------*/

void TestSortInt(CompareFunc _compareFunc)
{
	int* array;
	char testName[] = "sort int normal";
	array = createIntArr(ARR_LENGTH);
	GenericBubbleSort((void*)array, ARR_LENGTH, sizeof(int), _compareFunc);
	if(isSorted(array, sizeof(int), ARR_LENGTH, _compareFunc))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	free(array);
}

void TestSortChar(CompareFunc _compareFunc)
{
	char* array;
	char testName[] = "sort char normal";
	array = createCharArr(ARR_LENGTH);
	GenericBubbleSort((void*)array, 3, sizeof(char), _compareFunc);
	if(isSorted(array, sizeof(char), 3, _compareFunc))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestSortPerson(CompareFunc _compareFunc)
{
	Person* array;
	char testName[] = "sort person normal";
	array = createPersonArr(ARR_LENGTH);
	GenericBubbleSort((void*)array, ARR_LENGTH, sizeof(Person), _compareFunc);
	if(isSorted(array, sizeof(Person), ARR_LENGTH, _compareFunc))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	free(array);
}

int main()
{	
	TestSortInt(BiggerThanInt);
	TestSortChar(BiggerThanChar);
	TestSortPerson(BiggerThanPerson);
	TestSortInt(SmallerThanInt);
	TestSortChar(SmallerThanChar);
	TestSortPerson(SmallerThanPerson);
	TestSortInt(biggerSinInt);
	TestSortChar(biggerSinChar);
	TestSortPerson(biggerSinPerson);
	return 1;
}
