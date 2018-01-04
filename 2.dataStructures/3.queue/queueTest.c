#include <stdio.h>
#include "queue.h"

#define DEFAULT_SIZE 10
#define DEFAULT_INSERT_SIZE 6

typedef enum
{
	FAILED,
	PASSED
} TestResult;
/*****************helper functions********************/
void printTestResult(TestResult testResult, char* testName)
{
	if(testResult == PASSED)
	{
		printf("PASSED ");
	}
	else
	{
		printf("FAILED ");
	}
	printf("%s\n", testName);
}

ADTErr insertLoop(Queue* _queue, int _times)
{
	int i;
	ADTErr result;
	for(i = 0; i < _times; ++i)
	{
		result = QueueInsert(_queue, i);
	}
	return result;
}

ADTErr removeLoop(Queue* _queue, int _times, int* _dest)
{
	int i;
	ADTErr result;
	for(i = 0; i < _times; ++i)
	{
		result = QueueRemove(_queue, _dest);
	}
	return result;
}

/*******************test functions***********************/
void testCreateNormal()
{
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	if(NULL == myQueue)
	{
		testResult = FAILED;
	}
	else
	{
		testResult = PASSED;
	}
	printTestResult(testResult, "create queue normal");
}

void testCreateSizeZero()
{
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(0);
	if(NULL == myQueue)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "create queue size zero");
}

void testQueueInsertNormal()
{
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	insertLoop(myQueue, DEFAULT_INSERT_SIZE);
	
	printTestResult(PASSED, "insert normal");
}

void testQueueInsertFull()
{
	ADTErr error;
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	error = insertLoop(myQueue, DEFAULT_SIZE + 1);
	if(error == ERR_OVERFLOW)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "insert full");
}

void testQueueInsertWithLoop()
{
	int dest;
	ADTErr error;
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	insertLoop(myQueue, DEFAULT_SIZE - 1);
	removeLoop(myQueue, 5, &dest);
	error = insertLoop(myQueue, 2);
	if(error == ERR_OK)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "insert with loop");
}


void testRemoveNormal()
{
	int dest;
	ADTErr error;
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	insertLoop(myQueue, DEFAULT_SIZE - 1);
	error = removeLoop(myQueue, 1, &dest);
	if(error == ERR_OK)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "remove normal");
}

void testRemoveEmpty()
{
	int dest;
	ADTErr error;
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	error = removeLoop(myQueue, 1, &dest);
	if(error == ERR_UNDERFLOW)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "remove empty");
}


void testRemoveNullDest()
{
	ADTErr error;
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	insertLoop(myQueue, DEFAULT_INSERT_SIZE);
	error = removeLoop(myQueue, 1, NULL);
	if(error == ERR_OK)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "remove with loop");
}

void testRemoveWithLoop()
{
	int dest;
	ADTErr error;
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	insertLoop(myQueue, DEFAULT_SIZE);
	removeLoop(myQueue, DEFAULT_SIZE, &dest);
	insertLoop(myQueue, DEFAULT_INSERT_SIZE);
	error = removeLoop(myQueue, DEFAULT_INSERT_SIZE, &dest);
	if(error == ERR_OK)
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "remove null dest");
}

void testIsEmptyWhileEmpty()
{
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	if(QueueIsEmpty(myQueue))
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "is empty while empty");
}

void testIsEmptyWhilefull()
{
	TestResult testResult;
	Queue* myQueue;
	myQueue = QueueCreate(DEFAULT_SIZE);
	insertLoop(myQueue, DEFAULT_SIZE);
	if(!QueueIsEmpty(myQueue))
	{
		testResult = PASSED;
	}
	else
	{
		testResult = FAILED;
	}
	printTestResult(testResult, "is empty while full");
}

void wildTest()
{
	int dest;
	ADTErr error;
	Queue* myQueue;
	myQueue = QueueCreate(30);
	error = insertLoop(myQueue, 15);
	if(error != ERR_OK)
	{
		printTestResult(FAILED, "wild test0");
	}
	error = removeLoop(myQueue, 5, &dest);
	if(error != ERR_OK)
	{
		printTestResult(FAILED, "wild test1");
	}
	error = insertLoop(myQueue, 15);
	if(error != ERR_OK)
	{
		printTestResult(FAILED, "wild test2");
	}
	error = removeLoop(myQueue, 30, &dest);
	if(error != ERR_UNDERFLOW)
	{
		printTestResult(FAILED, "wild test3");
	}
	if(!QueueIsEmpty(myQueue))
	{
		printTestResult(FAILED, "wild test4");
	}
	error = insertLoop(myQueue, 15);
	if(error != ERR_OK)
	{
		printTestResult(FAILED, "wild test2");
	}
	printTestResult(PASSED, "wild test");
	QueuePrint(myQueue);
}




int main()
{
	testCreateNormal();
	testCreateSizeZero();
	
	testQueueInsertNormal();
	testQueueInsertFull();
	testQueueInsertWithLoop();
	
	testRemoveNormal();
	testRemoveEmpty();
	testRemoveNullDest();
	testRemoveWithLoop();
	
	testIsEmptyWhilefull();
	testIsEmptyWhileEmpty();
	
	wildTest();
	return 1;
}
