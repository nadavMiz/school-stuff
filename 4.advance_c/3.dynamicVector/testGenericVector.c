#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genericVector.h"
#include "ADTErr.h"

#define INITIAL_VECTOR_CAPACITY 10000
#define EXTENTION_BLOCK_SIZE 10
#define NAME_SIZE 10

typedef struct
{
	char* m_name;
	int m_id;
} Person;

typedef enum 
{
	PASSED,
	FAILED
} Result;

/*--------------destroy element functions-------------*/

int DestroyInt(void* _elementPtr, void* _dummy)
{
	free(_elementPtr);
	return 1;
}

int DestroyPerson(void* _elementPtr, void* _dummy)
{
	free(((Person*)_elementPtr)->m_name);
	free(_elementPtr);
	return 1;
}

/*----------------print element functions---------------*/

int PrintInt(void* _intPtr, void* _dummy)
{
	printf("%d ", (*(int*)_intPtr));
	return 1;
}

int PrintPerson(void* _person, void* _dummy)
{
	printf("name: %s ID: %d| ", ((Person*)_person)->m_name, ((Person*)_person)->m_id);
	return 1;
}

/*-------------------helper functions-------------------*/

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

static Vector* createIntVec(size_t _capacity)
{
	int i;
	int* element;
	Vector* vector;
	vector = VectorCreate(_capacity, EXTENTION_BLOCK_SIZE);
	for(i = 0; i < _capacity; ++i)
	{
		element = malloc(sizeof(int));
		*element = i;
		VectorAdd(vector,  element);
	}
	return vector;
}

static Vector* createPersonVec(size_t _capacity)
{
	int i;
	Person* person;
	Vector* vector;
	vector = VectorCreate(_capacity, EXTENTION_BLOCK_SIZE);
	for(i = 0; i < _capacity; ++i)
	{
		person = malloc(sizeof(Person));
		person->m_name = malloc(sizeof(char) * NAME_SIZE);
		strcpy(person->m_name, "nadav");
		person->m_id = i;
		VectorAdd(vector,  person);
	}
	return vector;
}



/*------------------main test functions------------------*/

void TestCreateVectorNormalInt()
{
	char testName[30] = "create int vector";
	Vector* vec;
	vec = VectorCreate(30, EXTENTION_BLOCK_SIZE/2);
	if(NULL != vec)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(PASSED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}

void TestCreateVectorNormalPerson()
{
	char testName[30] = "create person vector";
	Vector* vec;
	vec = VectorCreate(INITIAL_VECTOR_CAPACITY/2, EXTENTION_BLOCK_SIZE);
	if(NULL != vec)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(PASSED, testName);
	}
	VectorDestroy(&vec, DestroyPerson);
}

void TestCreateVectorZeroInput()
{
	char testName[30] = "create vector zero input";
	Vector* vec;
	vec = VectorCreate(0, 0);
	if(NULL == vec)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
		VectorDestroy(&vec, DestroyInt);
	}
}

void TestAddElementsNormalInt(size_t _capacity)
{
	int i;
	int* elem;
	Result result = PASSED;
	char testName[30] = "add int elements normal";
	Vector* vec;
	vec = createIntVec(_capacity);
	for(i = 0; i < _capacity; ++i)
	{
		VectorGet(vec, (size_t)i, (void**)(&elem));
		if(i != *elem)
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	VectorDestroy(&vec, DestroyInt);
}

void TestAddElementsNormalPerson(size_t _capacity)
{
	int i;
	Person* person;
	Result result = PASSED;
	char testName[30] = "add person elements normal";
	Vector* vec;
	vec = createPersonVec(_capacity);
	for(i = 0; i < _capacity; ++i)
	{
		VectorGet(vec, (size_t)i, (void**)(&person));
		if(i != person->m_id)
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	VectorDestroy(&vec, DestroyPerson);
}

void TestAddElementsNULL()
{
	char testName[30] = "add element NULL";
	ADTErr error1, error2;
	int elem = 5;
	Vector* vec;
	vec = VectorCreate(1, 0);
	error1 = VectorAdd(vec,  NULL);
	error2 = VectorAdd(NULL, &elem);
	if(ERR_NOT_INITIALIZED == error1 && ERR_NOT_INITIALIZED == error2)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}
	
void TestVectorDeleteNormalInt(size_t _capacity)
{
	int i;
	int* elem = malloc(sizeof(int));
	Result result = PASSED;
	char testName[30] = "delete int elements normal";
	Vector* vec;
	vec = createIntVec(_capacity);
	for(i = 0; i < _capacity; ++i)
	{
		VectorDelete(vec, (void**)&elem);
		if(((int)_capacity - i - 1) != *elem)
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	free(elem);
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorDeleteNormalPerson(size_t _capacity)
{
	int i;
	Person* elem = malloc(sizeof(Person));
	Result result = PASSED;
	char testName[30] = "delete person elements normal";
	Vector* vec;
	vec = createPersonVec(_capacity);
	for(i = 0; i < _capacity; ++i)
	{
		VectorDelete(vec, (void**)&elem);
		if(((int)_capacity - i - 1) != elem->m_id)
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	free(elem);
	VectorDestroy(&vec, DestroyPerson);
}

void TestVectorDeleteEmpty()
{
	char testName[30] = "vector delete empty vector";
	ADTErr error;
	int* elem = malloc(sizeof(int));
	Vector* vec;
	vec = VectorCreate(1, 0);
	error = VectorDelete(vec, (void**)&elem);
	if(ERR_UNDERFLOW == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	free(elem);
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorDeleteNull()
{
	char testName[30] = "vector delete NULL input";
	ADTErr error1, error2;
	int* elem = malloc(sizeof(int));
	Vector* vec;
	vec = VectorCreate(1, 0);
	error1 = VectorDelete(NULL, (void**)&elem);
	error2 = VectorDelete(vec, NULL);
	if(ERR_NOT_INITIALIZED == error1 && ERR_NOT_INITIALIZED == error2)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	free(elem);
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorGetNormal(size_t _capacity)
{
	char testName[30] = "vector get normal";
	int i;
	int* elem;
	Result result;
	Vector* vec;
	vec = createIntVec(_capacity);
	for(i = 0; i < _capacity; ++i)
	{
		VectorGet(vec, (size_t)i, (void**)(&elem));
		if(i != *elem)
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorGetIndexTooLarge()
{
	char testName[30] = "vector get index too large";
	ADTErr error;
	int* elem = NULL;
	Vector* vec;
	vec = createIntVec(10);
	error = VectorGet(vec, 10, (void**)(&elem));
	if(ERR_OVERFLOW == error && NULL == elem)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorGetNull()
{
	char testName[30] = "vector get NULL vector";
	ADTErr error;
	int* elem = NULL;
	Vector* vec;
	vec = createIntVec(10);
	error = VectorGet(NULL, 2, (void**)(&elem));
	if(ERR_NOT_INITIALIZED == error && NULL == elem)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorSetNormal(size_t _capacity)
{
	char testName[30] = "vector set normal";
	int i;
	int* newElem;
	int* elem;
	Result result = PASSED;
	Vector* vec;
	vec = createIntVec(_capacity);
	for(i = 0; i < _capacity; ++i)
	{
		VectorGet(vec, (size_t)i, (void**)(&elem));
		free(elem);
		newElem = malloc(sizeof(int));
		*newElem = (int)_capacity - i - 1;
		VectorSet(vec, (size_t)i, (void*)newElem);
		--newElem;
	}
	for(i = 0; i < _capacity; ++i)
	{
		VectorGet(vec, (size_t)i, (void**)(&elem));
		if(((int)_capacity - i - 1) != *elem)
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorSetIndexTooLarge()
{
	char testName[30] = "vector set index too large";
	ADTErr error;
	int* elem = NULL;
	Vector* vec;
	vec = createIntVec(10);
	error = VectorSet(vec, 10, (void*)(elem));
	if(ERR_OVERFLOW == error && NULL == elem)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorSetNull()
{
	char testName[30] = "vector set NULL vector";
	ADTErr error;
	int* elem = NULL;
	Vector* vec;
	vec = createIntVec(10);
	error = VectorSet(NULL, 2, (void*)(elem));
	if(ERR_NOT_INITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorItemsNumNormal(size_t _capacity)
{
	char testName[30] = "vector size normal";
	ADTErr error;
	size_t size;
	Vector* vec;
	vec = createIntVec(_capacity);
	error = VectorItemsNum(vec, &size);
	if(ERR_OK == error && _capacity == size)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	VectorDestroy(&vec, DestroyInt);
}

void TestVectorItemsNumNull()
{
	char testName[30] = "vector size NULL vector";
	ADTErr error;
	size_t size;
	error = VectorItemsNum(NULL, &size);
	if(ERR_NOT_INITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

int main()
{
	TestCreateVectorNormalInt();
	TestCreateVectorNormalPerson();
	TestCreateVectorZeroInput();
	
	TestAddElementsNormalInt(INITIAL_VECTOR_CAPACITY);
	TestAddElementsNormalPerson(INITIAL_VECTOR_CAPACITY);
	TestAddElementsNULL();
	
	TestVectorDeleteNormalInt(INITIAL_VECTOR_CAPACITY);
	TestVectorDeleteNormalPerson(INITIAL_VECTOR_CAPACITY);
	TestVectorDeleteEmpty();
	TestVectorDeleteNull();
	
	TestVectorGetNormal(INITIAL_VECTOR_CAPACITY);
	TestVectorGetIndexTooLarge();
	TestVectorGetNull();
	
	TestVectorSetNormal(INITIAL_VECTOR_CAPACITY);
	TestVectorSetIndexTooLarge();
	TestVectorSetNull();
	
	TestVectorItemsNumNormal(INITIAL_VECTOR_CAPACITY);
	TestVectorItemsNumNull();
	return 1;
}
