#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person.h"


typedef enum 
{
	PASSED,
	FAILED
} Result;
/********************helper functions************/
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



/*****************************test functions*************************************/

void TestInsertHeadEmpty(Person* head)
{
	Result result = FAILED;
	head = ListInsertHead(NULL, head);
	if(58 == head->m_age)
	{
		result = PASSED;
	}
	PrintTest(result, "insert head empty\n");
}

void TestInsertHeadNormal(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	if(25 == head->m_age)
	{
		result = PASSED;
	}
	PrintTest(result, "insert head normal\n");
}

void TestRemoveHeadNormal(Person* head)
{
	Result result = FAILED;
	Person* removedHead;
	Person next = {1,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListRemoveHead(head, &removedHead);
	if(0 == removedHead->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove head normal\n");
}

void TestRemoveHeadEmpty(Person* head)
{
	Result result = FAILED;
	Person* removedHead;
	ListRemoveHead(NULL, &removedHead);
	if(NULL == removedHead)
	{
		result = PASSED;
	}
	PrintTest(result, "remove head empty\n");
}

void TestInsertByKeyNormal(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key normal\n");
}

void TestInsertByKeyHead(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 0, &next2);
	if(2 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key head\n");
}
void TestInsertByKeyEmpty(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	head = NULL;
	head = ListInsertByKey(head, 0, &next);
	if(1 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key empty\n");	
}

void TestInsertByKeyNullPointer(Person* head)
{
	Result result = FAILED;
	head = ListInsertByKey(head, 0, NULL);
	if(0 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key NULL pointer\n");	
}
void TestInsertByKeyTooLarge(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 10, &next2);
	if(1 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key too large\n");
}
void TestInsertByKeySmall(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, -5, &next2);
	if(1 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key too large\n");
}

void TestInsertByKeyRecNormal(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKeyRec(head, 1, &next2);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key recursive normal\n");
}

void TestInsertByKeyRecHead(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKeyRec(head, 0, &next2);
	if(2 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key recursive head\n");
}
void TestInsertByKeyRecEmpty(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	head = NULL;
	head = ListInsertByKeyRec(head, 0, &next);
	if(1 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key recursive empty\n");	
}

void TestInsertByKeyRecNullPointer(Person* head)
{
	Result result = FAILED;
	head = ListInsertByKeyRec(head, 0, NULL);
	if(0 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key recursive NULL pointer\n");	
}
void TestInsertByKeyRecTooLarge(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKeyRec(head, 10, &next2);
	if(1 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key recursive too large\n");
}
void TestInsertByKeyRecSmall(Person* head)
{
	Result result = FAILED;
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	head = ListInsertHead(head, &next);
	head = ListInsertByKeyRec(head, -5, &next2);
	if(1 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "insert by key recursive too large\n");
}
void TestRemoveByKeyNormal(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKey(head, 1, &deleted);
	if(0 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key normal\n");
}
void TestRemoveByKeyHead(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKey(head, 0, &deleted);
	if(2 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key at head\n");
}
void TestRemoveByKeyEmpty(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	free(deleted);
	head = ListRemoveByKey(NULL, 0, &deleted);
	if(NULL == head)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key empty\n");
}

void TestRemoveByKeyNullPointer(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKey(head, 1, NULL);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key NULL pointer\n");
}

void TestRemoveByKeyTooLarge(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKey(head, 10, &deleted);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key index too large\n");
}

void TestRemoveByKeySmall(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKey(head, -10, &deleted);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key index too small\n");
}

void TestRemoveByKeyRecNormal(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKeyRec(head, 1, &deleted);
	if(0 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key recursive normal\n");
}
void TestRemoveByKeyRecHead(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKeyRec(head, 0, &deleted);
	if(2 == head->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key recursive at head\n");
}
void TestRemoveByKeyRecEmpty(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	free(deleted);
	head = ListRemoveByKeyRec(NULL, 0, &deleted);
	if(NULL == head)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key recursive empty\n");
}

void TestRemoveByKeyRecNullPointer(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKeyRec(head, 1, NULL);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key recursive NULL pointer\n");
}

void TestRemoveByKeyRecTooLarge(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKeyRec(head, 10, &deleted);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key recursive index too large\n");
}

void TestRemoveByKeyRecSmall(Person* head)
{
	Result result = FAILED;
	Person* deleted = malloc(sizeof(Person));
	Person next = {1,"nadav",25,NULL};
	Person next2 = {2,"nadav",25,NULL};
	free(deleted);
	head = ListInsertHead(head, &next);
	head = ListInsertByKey(head, 1, &next2);
	head = ListRemoveByKeyRec(head, -10, &deleted);
	if(2 == head->m_next->m_id)
	{
		result = PASSED;
	}
	PrintTest(result, "remove by key recursive index too small\n");
}

int main()
{
	Person* head = malloc(sizeof(Person));
	head->m_id = 0;
	strcpy(head->m_name, "nadav");
	head->m_next = NULL;
	head->m_age = 58;
	TestInsertHeadEmpty(head);
	TestInsertHeadNormal(head);
	
	TestRemoveHeadNormal(head);
	TestRemoveHeadEmpty(head);
	
	TestInsertByKeyNormal(head);
	TestInsertByKeyHead(head);
	TestInsertByKeyEmpty(head);
	TestInsertByKeyNullPointer(head);
	TestInsertByKeyTooLarge(head);
	TestInsertByKeySmall(head);
	
	TestInsertByKeyRecNormal(head);
	TestInsertByKeyRecHead(head);
	TestInsertByKeyRecEmpty(head);
	TestInsertByKeyRecNullPointer(head);
	TestInsertByKeyRecTooLarge(head);
	TestInsertByKeyRecSmall(head);
	
	TestRemoveByKeyNormal(head);
	TestRemoveByKeyHead(head);
	TestRemoveByKeyEmpty(head);
	TestRemoveByKeyNullPointer(head);
	TestRemoveByKeyTooLarge(head);
	TestRemoveByKeySmall(head);
	
	TestRemoveByKeyRecNormal(head);
	TestRemoveByKeyRecHead(head);
	TestRemoveByKeyRecEmpty(head);
	TestRemoveByKeyRecNullPointer(head);
	TestRemoveByKeyRecTooLarge(head);
	TestRemoveByKeyRecSmall(head);
	free(head);
	return 1;
}
