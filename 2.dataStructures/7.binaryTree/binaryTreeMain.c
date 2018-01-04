#include <stdio.h>
#include "ADTErr.h"
#include "binaryTree.h"

typedef enum
{
	PASSED,
	FAILED
} Result;

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

static Tree* BuildTree()
{
	Tree* newTree;
	newTree = TreeCreate();
	TreeInsert(newTree, 5);
	TreeInsert(newTree, 7);
	TreeInsert(newTree, 9);
	TreeInsert(newTree, 2);
	TreeInsert(newTree, 3);
	TreeInsert(newTree, 8);
	return newTree;
}

/*******main test functions********/

void TestTreeCreate()
{
	Result result = FAILED;
	Tree* newTree;
	newTree = TreeCreate();
	if(NULL != newTree)
	{
		result = PASSED;
	}
	PrintTest(result, "create tree");
	TreeDestroy(newTree);
}

void TestTreeDestroyNullTree()
{
	TreeDestroy(NULL);
	PrintTest(PASSED, "destroy tree NULL pointer");
}

void TestTreeDestroyTwice()
{
	Tree* newTree;
	newTree = TreeCreate();
	TreeDestroy(newTree);
	TreeDestroy(newTree);
	PrintTest(PASSED, "destroy tree twice");
}

void TestTreeInsertEmpty()
{
	ADTErr error;
	Result result = FAILED;
	Tree* newTree;
	newTree = TreeCreate();
	error = TreeInsert(newTree, 5);
	if(ERR_OK == error)
	{
		result = PASSED;
	}
	PrintTest(result, "tree insert while tree is empty");
	TreeDestroy(newTree);
}

void TestInsertNormal()
{
	ADTErr error;
	Result result = FAILED;
	Tree* newTree;
	newTree = TreeCreate();
	TreeInsert(newTree, 5);
	TreeInsert(newTree, 7);
	error = TreeInsert(newTree, 9);
	if(ERR_OK == error)
	{
		result = PASSED;
	}
	PrintTest(result, "tree insert normal");
	TreeDestroy(newTree);
}

void TestTreeInsertNullTree()
{
	ADTErr error;
	Result result = FAILED;
	error = TreeInsert(NULL, 9);
	if(ERR_NOT_INITIALIZED == error)
	{
		result = PASSED;
	}
	PrintTest(result, "tree insert NULL tree");
}

void TestIsDataFoundNormal()
{
	Result result = FAILED;
	Tree* newTree;
	newTree = BuildTree();
	if(TreeIsDataFound(newTree, 5) && TreeIsDataFound(newTree, 9))
	{
		result = PASSED;
	}
	PrintTest(result, "is data found while data is in tree");
	TreeDestroy(newTree);
}

void TestIsDataFoundNotFound()
{
	Tree* newTree;
	Result result = FAILED;
	newTree = BuildTree();
	if(!TreeIsDataFound(newTree, 0))
	{
		result = PASSED;
	}
	PrintTest(result, "is data found while data is NOT in tree");
	TreeDestroy(newTree);
}

void TestIsDataFoundNullTree()
{
	Result result = FAILED;
	if(!TreeIsDataFound(NULL, 0))
	{
		result = PASSED;
	}
	PrintTest(result, "is data found while tree is NULL");
}

void TestIsTreeFullWhileFull()
{
	Result result = FAILED;
	Tree* newTree;
	newTree = TreeCreate();
	TreeInsert(newTree, 5);
	TreeInsert(newTree, 3);
	TreeInsert(newTree, 9);
	TreeInsert(newTree, 2);
	TreeInsert(newTree, 4);
	TreeInsert(newTree, 10);
	TreeInsert(newTree, 8);
	if(isFullTree(newTree))
	{
		result = PASSED;
	}
	PrintTest(result, "is tree full while tree is full");
	TreeDestroy(newTree);
}

void TestIsTreeFullWhileNotFull()
{
	Result result = FAILED;
	Tree* newTree;
	newTree = BuildTree();
	if(!isFullTree(newTree))
	{
		result = PASSED;
	}
	PrintTest(result, "is tree full while tree is NOT full");
	TreeDestroy(newTree);
}

int main()
{
	TestTreeCreate();

	TestTreeDestroyNullTree();
	TestTreeDestroyTwice();

	TestTreeInsertEmpty();
	TestInsertNormal();
	TestTreeInsertNullTree();

	TestIsDataFoundNormal();
	TestIsDataFoundNotFound();
	TestIsDataFoundNullTree();

	TestIsTreeFullWhileNotFull();
	TestIsTreeFullWhileFull();
	
	return 1;
	}
