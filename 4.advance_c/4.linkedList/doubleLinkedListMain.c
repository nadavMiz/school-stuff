#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ADTErr.h"
#include "doubleLinkedList.h"

#define INITIAL_VECTOR_CAPACITY 10000
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

/*--------------------match function--------------------*/

int MatchPerson(Person* person, Person* match)
{
	return (person->m_id == match->m_id);
}

int DummyFunction(void* dummy1, void* dummy2)
{
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

static Person* createPerson(char* _name, int _id)
{
	Person* person;
	person = malloc(sizeof(Person));
	person->m_name = malloc(NAME_SIZE * sizeof(char));
	strcpy(person->m_name, _name);
	person->m_id = _id;
	return person;
	
}

static List* BuildListInt(size_t _capacity)
{
	List* list;
	int* elem;
	size_t i;
	list = ListCreate();
	for(i = 0; i < _capacity; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = (int)i;
		if(LIST_OK != ListPushTail(list, elem))
		{
			return NULL;
		}
	}
	return list;
}

static List* BuildListPerson(size_t _capacity)
{
	List* list;
	Person* elem;
	size_t i;
	list = ListCreate();
	for(i = 0; i < _capacity; ++i)
	{
		elem = createPerson("stan", (int)i);
		if(LIST_OK != ListPushTail(list, elem))
		{
			return NULL;
		}
	}
	return list;
}

/*-------------main test functions----------*/

void TestListCreate()
{
	char testName[30] = "create list";
	List* list;
	list = ListCreate();
	if(NULL != list)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	ListDestroy(&list, DestroyInt);
}

void TestListPushTailInt(size_t _tries)
{
	char testName[30] = "push tail int";
	size_t i;
	int* elem;
	List* list;
	Result result = PASSED;
	list = ListCreate();
	for(i = 0; i < _tries; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = (int)i;
		if(LIST_OK != ListPushTail(list, elem))
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	ListDestroy(&list, DestroyInt);
}

void TestListPushTailPerson(size_t _tries)
{
	char testName[30] = "push tail person";
	size_t i;
	Person* elem;
	List* list;
	Result result = PASSED;
	list = ListCreate();
	for(i = 0; i < _tries; ++i)
	{
		elem = malloc(sizeof(Person));
		elem->m_name = malloc(NAME_SIZE * sizeof(char));
		strcpy(elem->m_name, "stan");
		elem->m_id = (int)i;
		if(LIST_OK != ListPushTail(list, elem))
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	ListDestroy(&list, DestroyPerson);
}

void TestListPushTailNull()
{
	int elem = 5;
	char testName[30] = "push tail null";
	ListErrors error;
	
	error = ListPushTail(NULL, &elem);
	
	if(LIST_UNINITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestListPopTailInt(size_t _capacity)
{
	int i;
	int* elem;
	ListErrors error;
	Result result = PASSED;
	char testName[30] = "pop tail int";
	List* list;
	list = BuildListInt(_capacity);
	for(i = (int)_capacity - 1; i >= 0; --i)
	{
		error = ListPopTail(list, (void**)&elem);
		if(LIST_OK != error || i != *elem)
		{
			result = FAILED;
			free(elem);
			break;
		}
		free(elem);
	}

	PrintTest(result, testName);
	ListDestroy(&list, DestroyInt);
}

void TestListPopTailPerson(size_t _capacity)
{
	int i;
	Person* elem;
	ListErrors error;
	Result result = PASSED;
	char testName[30] = "pop tail person";
	List* list;
	list = BuildListPerson(_capacity);
	for(i = (int)_capacity - 1; i >= 0; --i)
	{
		error = ListPopTail(list, (void**)&elem);
		if(LIST_OK != error || i != elem->m_id)
		{
			result = FAILED;
			DestroyPerson(elem, NULL);
			break;
		}
		DestroyPerson(elem, NULL);
	}

	PrintTest(result, testName);
	ListDestroy(&list, DestroyPerson);
}

void TestListPopTailEmpty()
{
	char testName[30] = "pop tail empty";
	Person* elem;
	size_t i;
	ListErrors error;
	List* list;
	
	list = BuildListPerson(4);
	for(i = 0; i < 4; ++i)
	{
		ListPopTail(list, (void**)&elem);
		DestroyPerson(elem, NULL);
	}
	error = ListPopTail(list, (void**)&elem);
	if(LIST_IS_EMPTY == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	ListDestroy(&list, DestroyInt);	
}

void TestListPopTailNull()
{
	char testName[30] = "pop tail null";
	Person* elem;
	ListErrors error;
	error = ListPopTail(NULL, (void**)&elem);
	if(LIST_UNINITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestListPushHeadInt(size_t _capacity)
{
	char testName[30] = "push head int";
	size_t i;
	int* elem;
	List* list;
	ListErrors error;
	Result result = PASSED;
	list = ListCreate();
	
	/*push capacity elements*/
	for(i = 0; i < _capacity; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = (int)i;
		if(LIST_OK != ListPushHead(list, elem))
		{
			result = FAILED;
			break;
		}
	}
	
	/*pop and compare all the elements*/
	for(i = 0; i < _capacity; --i)
	{
		error = ListPopTail(list, (void**)&elem);
		if(LIST_OK != error || i != *elem)
		{
			result = FAILED;
			free(elem);
			break;
		}
		free(elem);
	}
	
	PrintTest(result, testName);
	ListDestroy(&list, DestroyInt);
}

void TestListPushHeadPerson(size_t _capacity)
{
	char testName[30] = "push head person";
	size_t i;
	Person* elem;
	List* list;
	ListErrors error;
	Result result = PASSED;
	list = ListCreate();
	
	/*push capacity elements*/
	for(i = 0; i < _capacity; ++i)
	{
		elem = malloc(sizeof(Person));
		elem->m_name = malloc(NAME_SIZE * sizeof(char));
		strcpy(elem->m_name, "stan");
		elem->m_id = (int)i;
		if(LIST_OK != ListPushHead(list, elem))
		{
			result = FAILED;
			break;
		}
	}
	
	/*pop all the elements and compare to the values they should have*/
	for(i = 0; i < _capacity; --i)
	{
		error = ListPopTail(list, (void**)&elem);
		if(LIST_OK != error || i != elem->m_id)
		{
			result = FAILED;
			DestroyPerson(elem, NULL);
			break;
		}
		DestroyPerson(elem, NULL);
	}

	PrintTest(result, testName);
	ListDestroy(&list, DestroyPerson);
}

void TestListPushHeadNull()
{
	char testName[30] = "push head null";
	int* elem = NULL;
	ListErrors error;
	
	error = ListPushHead(NULL, elem);
	if(LIST_UNINITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestListPushTailThanHead(size_t _capacity)
{
	char testName[30] = "push tail than head";
	int i;
	int* elem;
	List* list;
	ListErrors error;
	Result result = PASSED;
	list = BuildListInt(_capacity);
	
	/*push capacity elements*/
	for(i = 0; i < _capacity; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = i;
		if(LIST_OK != ListPushHead(list, elem))
		{
			result = FAILED;
			break;
		}
	}
	
	/*pop and compare all the elements*/
	for(i = (int)_capacity - 1; i >= 0; --i)
	{
		error = ListPopTail(list, (void**)&elem);
		if(LIST_OK != error || i != *elem)
		{
			result = FAILED;
			free(elem);
			break;
		}
		free(elem);
	}
	
	PrintTest(result, testName);
	ListDestroy(&list, DestroyInt);
}

void TestListPopHeadInt(size_t _capacity)
{
	int i;
	int* elem;
	ListErrors error;
	Result result = PASSED;
	char testName[30] = "pop head int";
	List* list;
	list = BuildListInt(_capacity);
	for(i = 0; i < (int)_capacity; ++i)
	{
		error = ListPopHead(list, (void**)&elem);
		if(LIST_OK != error || i != *elem)
		{
			result = FAILED;
			free(elem);
			break;
		}
		free(elem);
	}

	PrintTest(result, testName);
	ListDestroy(&list, DestroyInt);
}

void TestListPopHeadPerson(size_t _capacity)
{
	int i;
	Person* elem;
	ListErrors error;
	Result result = PASSED;
	char testName[30] = "pop head person";
	List* list;
	list = BuildListPerson(_capacity);
	for(i = 0; i < (int)_capacity; ++i)
	{
		error = ListPopHead(list, (void**)&elem);
		if(LIST_OK != error || i != elem->m_id)
		{
			result = FAILED;
			DestroyPerson(elem, NULL);
			break;
		}
		DestroyPerson(elem, NULL);
	}

	PrintTest(result, testName);
	ListDestroy(&list, DestroyPerson);
}

void TestListPopHeadNull()
{
	char testName[30] = "pop head null";
	Person* elem;
	ListErrors error;
	error = ListPopHead(NULL, (void**)&elem);
	if(LIST_UNINITIALIZED == error)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestFindForward()
{
	char testName[30] = "find forward";
	Person* elem1, *elem2;
	List* list;
	
	list = BuildListPerson(10);
	elem1 = createPerson("Bob", 4);
	ListPushHead(list, elem1);
	elem2 = createPerson("Nadav", 8);
	ListPushHead(list, elem2);
	FindFirstForward(list, (PredicateFunc)MatchPerson, elem1, (void**)&elem2);
	if(strcmp(elem2->m_name, "stan"))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	ListDestroy(&list, DestroyPerson);
}

void TestFindBackward()
{
	char testName[30] = "find backward";
	Person* elem1, *elem2;
	List* list;
	
	list = BuildListPerson(10);
	elem1 = createPerson("Bob", 4);
	ListPushHead(list, elem1);
	elem2 = createPerson("Nadav", 8);
	ListPushHead(list, elem2);
	FindFirstBackward(list, (PredicateFunc)MatchPerson, elem1, (void**)&elem2);
	if(strcmp(elem2->m_name, "Bob"))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}	
	ListDestroy(&list, DestroyPerson);
}

void TestListCountItem()
{
	char testName[30] = "count items";
	List* list;
	list = BuildListInt(INITIAL_VECTOR_CAPACITY);
	if(INITIAL_VECTOR_CAPACITY == ListCountItems(list))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}	
	ListDestroy(&list, DestroyInt);
}

void TestListCountItemNull()
{
	char testName[30] = "count items null";
	if(0 == ListCountItems(NULL))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}	
}

void TestIsEmpty()
{
	char testName[30] = "is empty";
	int result1, result2;
	List* list;
	list = BuildListInt(INITIAL_VECTOR_CAPACITY);
	result1 = ListIsEmpty(list);
	ListDestroy(&list, DestroyInt);
	list = ListCreate();
	result2 = ListIsEmpty(list);
	if(result2 && !result1)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}	
	
}
void TestIsEmptyNull()
{
	char testName[30] = "is empty null";
	if(ListIsEmpty(NULL))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}	
}

void TestForEach()
{
	char testName[30] = "for each";
	List* list;
	list = BuildListInt(INITIAL_VECTOR_CAPACITY);
	if(INITIAL_VECTOR_CAPACITY == ListForEach(list, DummyFunction, NULL))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	ListDestroy(&list, DestroyInt);
}

void TestForEachNull()
{
	char testName[30] = "for each null";
	List* list;
	size_t result1, result2;
	list = BuildListInt(INITIAL_VECTOR_CAPACITY);
	result1 = ListForEach(list, NULL, NULL);
	result2 = ListForEach(NULL, DummyFunction, NULL);
	if(0 == result1 && 0 == result2)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	ListDestroy(&list, DestroyInt);
}

int main()
{
	TestListCreate();

	TestListPushTailInt(INITIAL_VECTOR_CAPACITY);
	TestListPushTailPerson(INITIAL_VECTOR_CAPACITY);
	TestListPushTailNull();
	
	TestListPopTailInt(INITIAL_VECTOR_CAPACITY);
	TestListPopTailPerson(INITIAL_VECTOR_CAPACITY);
	TestListPopTailEmpty();
	TestListPopTailNull();

	TestListPushHeadInt(INITIAL_VECTOR_CAPACITY);
	TestListPushHeadPerson(INITIAL_VECTOR_CAPACITY);
	TestListPushHeadNull();
	TestListPushTailThanHead(INITIAL_VECTOR_CAPACITY);

	TestListPopHeadInt(INITIAL_VECTOR_CAPACITY);
	TestListPopHeadPerson(INITIAL_VECTOR_CAPACITY);
	TestListPopHeadNull();

	TestFindForward();
	TestFindBackward();

	TestListCountItem();
	TestListCountItemNull();

	TestIsEmpty();
	TestIsEmptyNull();

	TestForEach();
	TestForEachNull();

	return 1;
}
