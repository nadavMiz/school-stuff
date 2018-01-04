#include <stdio.h>
#include <stdlib.h>
#include "../../inc/bin_tree.h"

#define TREE_SIZE 10000

typedef enum
{
	PASSED,
	FAILED
} Result;

/*----------user functions---------------*/

int LestThan(int* _a, int* _b)
{
	return ((*_a) < (*_b));
}

void destroyer(void* _data)
{
	free((int*)_data);
}

int predicate(void* _data, void* _toCompare)
{
	return(*((int*)_data) - *((int*)_toCompare));
}


int PrintFunc(void* _data, void* _dummy)
{
	printf("%d ", *((int*)_data));
	return 1;
}

/********helper functions**********/

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

static void InsertArray(BSTree* _tree, int* _elements, size_t arrayLen)
{
	int* elem;
	size_t i;
	for(i = 0; i < arrayLen; ++i)
	{
		elem = malloc(sizeof(int));
		*elem = _elements[i];
		BSTree_Insert(_tree, (void*)elem);
	}
}

static int CheckTree(BSTree* _tree, int* sortedElements)
{
	size_t i;
	BSTreeItr itr;
	
	itr = BSTreeItr_Begin(_tree);
	for(i = 0; i < (size_t)(sizeof(sortedElements)/sizeof(int)); ++i)
	{
		if(0 != predicate(&(sortedElements[i]) , BSTreeItr_Get(itr)))
		{
			return 0;
		}
		itr = BSTreeItr_Next(itr);
	}
	return 1;
}

/*-----------main test functions----------*/

void TestCreatBSTree()
{
	char testName[30] = "creat tree";
	BSTree* tree;
	tree = BSTree_Create((LessComparator)LestThan);
	if(NULL != tree)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

void TestCreatBSTreeNull()
{
	char testName[30] = "creat tree null";
	BSTree* tree;
	tree = BSTree_Create(NULL);
	if(NULL == tree)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestInsert(size_t _capacity)
{
	char testName[30] = "insert tree";
	BSTree* tree;
	size_t i;
	BSTreeItr insertItr;
	int* element;
	Result result = PASSED;
	tree = BSTree_Create((LessComparator)LestThan);
	
	for(i = 0; i < _capacity; ++i)
	{
		element = malloc(sizeof(int));
		*element = rand();
		insertItr = BSTree_Insert(tree, element);
		if(insertItr == NULL)
		{
			result = FAILED;
			break; 
		}
	}
	PrintTest(result, testName);
	BSTree_Destroy(tree, destroyer);
}

void TestInsertNull()
{
	char testName[30] = "insert tree Null";
	
	int* element;
	BSTreeItr insertItr;
	element = malloc(sizeof(int));
	*element = 5;
	
	insertItr = BSTree_Insert(NULL, element);
	
	if(NULL == insertItr)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	free(element);
}

void TestBegin()
{
	char testName[30] = "begin";
	int array[] = {50,60,30,40,10,11,45,35};
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	
	InsertArray(tree, array, (size_t)(sizeof(array)/sizeof(int)));
	insertItr = BSTreeItr_Begin(tree);
	if(10 == *((int*)(BSTreeItr_Get(insertItr))))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

void TestBeginEmpty()
{
	char testName[30] = "begin empty";
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	insertItr = BSTreeItr_Begin(tree);
	if(NULL == BSTreeItr_Get(insertItr))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

void TestBeginNull()
{
	char testName[30] = "begin null";
	BSTreeItr insertItr;
	
	insertItr = BSTreeItr_Begin(NULL);
	if(NULL == insertItr)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestEnd()
{
	char testName[30] = "end";
	int array[] = {50,60,30,40,10,11,45,35};
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	
	InsertArray(tree, array, (size_t)(sizeof(array)/sizeof(int)));
	insertItr = BSTreeItr_End(tree);
	if(NULL == BSTreeItr_Get(insertItr))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

void TestEndEmpty()
{
	char testName[30] = "end empty";
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	insertItr = BSTreeItr_End(tree);
	if(NULL == BSTreeItr_Get(insertItr))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

void TestEndNull()
{
	char testName[30] = "end null";
	BSTreeItr insertItr;
	
	insertItr = BSTreeItr_End(NULL);
	if(NULL == insertItr)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestGetNext()
{
	char testName[30] = "get next";
	int array[] = {50,60,30,40,10,11,45,35};
	int arraySorted[] = {10, 11, 30, 35, 40, 45, 50, 60};
	size_t i;
	Result result = PASSED;
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	InsertArray(tree, array, (size_t)(sizeof(array)/sizeof(int)));
	insertItr = BSTreeItr_Begin(tree);
	
	for(i = 0; i < (size_t)(sizeof(array)/sizeof(int)); ++i)
	{
		if(arraySorted[i] != *((int*)BSTreeItr_Get(insertItr)))
		{
			result = FAILED;
			break;
		}
		insertItr = BSTreeItr_Next(insertItr);
	}
	if(NULL != BSTreeItr_Get(insertItr))
	{
		result = FAILED;
	}
	
	PrintTest(result, testName);
	BSTree_Destroy(tree, destroyer);
}

void TestGetNextEnd()
{
	char testName[30] = "get next end";
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	insertItr = BSTreeItr_Begin(tree);
	insertItr = BSTreeItr_Next(insertItr);
	
	if(NULL == BSTreeItr_Get(insertItr))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

void TestGetNextNull()
{
	char testName[30] = "get next null";
	BSTreeItr insertItr;
	
	insertItr = BSTreeItr_Next(NULL);
	
	if(NULL == insertItr)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

void TestGetPrev()
{
	char testName[30] = "get prev";
	int array[] = {50,60,30,40,10,11,45,35};
	int arraySorted[] = {60,50,45,40,35,30,11,10};
	size_t i;
	Result result = PASSED;
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	InsertArray(tree, array, (size_t)(sizeof(array)/sizeof(int)));
	insertItr = BSTreeItr_End(tree);
	
	for(i = 0; i < (size_t)(sizeof(array)/sizeof(int)); ++i)
	{
		insertItr = BSTreeItr_Prev(insertItr);
		if(arraySorted[i] != *((int*)BSTreeItr_Get(insertItr)))
		{
			result = FAILED;
			break;
		}
	}
	
	PrintTest(result, testName);
	BSTree_Destroy(tree, destroyer);
}

void TestGetPrevBeginning()
{
	char testName[30] = "get prev beginning";
	BSTree* tree;
	BSTreeItr insertItr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	insertItr = BSTreeItr_End(tree);
	insertItr = BSTreeItr_Prev(insertItr);
	
	if(NULL == BSTreeItr_Get(insertItr))
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
	BSTree_Destroy(tree, destroyer);
}

/*---------------------------*/

void TestGetPrevNull()
{
	char testName[30] = "get prev null";
	BSTreeItr insertItr;
	
	insertItr = BSTreeItr_Prev(NULL);
	
	if(NULL == insertItr)
	{
		PrintTest(PASSED, testName);
	}
	else
	{
		PrintTest(FAILED, testName);
	}
}

/*------------------------------*/

void TestFindFirst()
{
	char testName[] = "find first";
	BSTree* tree;
	Result result = PASSED;
	int array[] = {50,60,30,36,10,11,45,35,42,43,39,40,41,55};
	size_t i;
	BSTreeItr itr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	InsertArray(tree, array, (size_t)(sizeof(array)/sizeof(int)));
	
	for(i = 0; i < (size_t)(sizeof(array)/sizeof(int)); ++i)
	{
		itr = BSTree_FindFirst(tree, predicate, &(array[i]));
		if(0 != predicate(&(array[i]), BSTreeItr_Get(itr)))
		{
			result = FAILED;
			break;
		}
	}
	PrintTest(result, testName);
	BSTree_Destroy(tree, destroyer);
}

/*------------------------------*/

void TestFindFirstNull()
{
	
}

/*------------------------------*/

void TestRemove()
{
	char testName[] = "remove normal";
	BSTree* tree;
	int array[] = {50,60,30,36,10,11,45,35,42,43,39,40,41,55,47};
	int remove[] = {10, 35, 60, 45};
	int sorted[] = {11,30,36,39,40,41,42,43,47,50,55};
	int data, *retval;
	Result result = PASSED;
	size_t i;
	BSTreeItr itr;
	
	tree = BSTree_Create((LessComparator)LestThan);
	InsertArray(tree, array, (size_t)(sizeof(array)/sizeof(int)));	
	
	for(i = 0; i < (size_t)(sizeof(remove)/sizeof(int)); ++i)
	{
		data = remove[i];
		itr = BSTree_FindFirst(tree, predicate, &data);
		retval = BSTreeItr_Remove(itr);
		if(0 != predicate(&data, retval))
		{
			result = FAILED;
			break;
		}
	}
	if(!CheckTree(tree, sorted))
	{
		result = FAILED;
	}
	PrintTest(result, testName);
	BSTree_Destroy(tree, destroyer);
}

int main()
{
	TestCreatBSTree();
	TestCreatBSTreeNull();
	TestInsert(TREE_SIZE);
	TestInsertNull();
	TestBegin();
	TestBeginEmpty();
	TestBeginNull();
	TestEnd();
	TestEndEmpty();
	TestEndNull();
	TestGetNext();
	TestGetNextEnd();
	TestGetNextNull();
	TestGetPrev();
	TestGetPrevBeginning();
	TestGetPrevNull();
	TestFindFirst();
	TestFindFirstNull();
	TestRemove();
	
	return 1;
}
