#include <stdlib.h>
#include <stdio.h>

#include "doubleLinkedList.h"

#define LIST_MAGIC_NUMBER 0X222222

#define IS_NULL_LIST(list) (NULL == (list) ||  LIST_MAGIC_NUMBER != (list)->m_magicNumber)

typedef struct Node Node;

struct List
{
	int m_magicNumber;
	Node* m_head;
	Node* m_tail;
};

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

/*----------static functions----------*/

/* creats a new node with the data _data */
static Node* CreateNode(void* _data)
{
	Node* newNode;
	newNode = calloc(1 ,sizeof(Node));
	if(NULL == newNode)
	{
		return NULL;
	}
	newNode->m_data = _data;
	return newNode;
}

/* destroys all the nodes in a liked list from _head*/
static void DestroyNodes(Node* _head, UserActionFunc _destroyElemFunc)
{
	Node* nextNode;
	while(NULL != _head)
	{
		nextNode = _head->m_next;
		_destroyElemFunc(_head->m_data, NULL);
		free(_head);
		_head = nextNode;
	}
}

static void InsertHead(List* _list, Node* _newHead)
{
	_newHead->m_next = _list->m_head;
	if(NULL != _list->m_head)
	{
		_list->m_head->m_prev = _newHead;
	}
	else
	{
		_list->m_tail = _newHead;
	}
	_list->m_head = _newHead;
}

static void InsertTail(List* _list, Node* _newTail)
{
	_newTail->m_prev = _list->m_tail;
	if(NULL != _list->m_tail)
	{
		_list->m_tail->m_next = _newTail;
	}
	else
	{
		_list->m_head = _newTail;
	}
	_list->m_tail = _newTail;
}

static void removeHead(List* _list)
{
	_list->m_head = _list->m_head->m_next;
	if(NULL != _list->m_head)
	{
		_list->m_head->m_prev = NULL;
	}
	else
	{
		_list->m_tail = NULL;
	}
}

static void removeTail(List* _list)
{
	_list->m_tail = _list->m_tail->m_prev;
	if(NULL != _list->m_tail)
	{
		_list->m_tail->m_next = NULL;
	}
	else
	{
		_list->m_head = NULL; 
	}
}

/*-----------main functions-------------*/

List* ListCreate(void)
{
	List* newList;
	newList = calloc(1, sizeof(List));
	if(NULL == newList)
	{
		return NULL;
	}
	newList->m_magicNumber = LIST_MAGIC_NUMBER;
	return newList;
}

void ListDestroy(List** _list, UserActionFunc _destoryFunc)
{
		DestroyNodes((*_list)->m_head, _destoryFunc);
		(*_list)->m_magicNumber = 0;
		free(*_list);
		(*_list) = NULL;
}

ListErrors ListPushHead(List* _list, void* _data)
{
	Node* newNode = NULL;
	/* error check */
	if(IS_NULL_LIST(_list))
	{
		return LIST_UNINITIALIZED;
	}
	
	/*create the new head*/
	newNode = CreateNode(_data);
	if(NULL == newNode)
	{
		return LIST_ALLOCATION_FAILED;
	}
	InsertHead(_list , newNode);
	return LIST_OK;
}

ListErrors ListPushTail(List* _list, void* _data)
{
	Node* newNode = NULL;
	if(IS_NULL_LIST(_list))
	{
		return LIST_UNINITIALIZED;
	}
	newNode = CreateNode(_data);
	if(NULL == newNode)
	{
		return LIST_ALLOCATION_FAILED;
	}
	InsertTail(_list, newNode);
	return LIST_OK;
}

ListErrors ListPopHead(List* _list, void* *_data)
{
	if(IS_NULL_LIST(_list))
	{
		return LIST_UNINITIALIZED;
	}
	if(NULL == _list->m_head)
	{
		return LIST_IS_EMPTY;
	}
	
	/* get the data */
	*_data = _list->m_head->m_data;
	
	removeHead(_list);
	
	return LIST_OK;
}

ListErrors ListPopTail(List* _list, void* *_data)
{
	if(IS_NULL_LIST(_list))
	{
		return LIST_UNINITIALIZED;
	}
	if(NULL == _list->m_tail)
	{
		return LIST_IS_EMPTY;
	}
	
	/* get the data */
	*_data = _list->m_tail->m_data;
	
	removeTail(_list);
	
	return LIST_OK;
}

ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item)
{
	Node* currentNode;
	*_item = NULL;
	if(IS_NULL_LIST(_list) || NULL == _predicateFunc)
	{
		return LIST_UNINITIALIZED;
	}
	currentNode = _list->m_head;
	while(NULL != currentNode)
	{
		if(_predicateFunc(currentNode->m_data, _context))
		{
			*_item = currentNode->m_data;
			break;
		}
		currentNode = currentNode->m_next;
	}
	return LIST_OK;
}

ListErrors FindFirstBackward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item)
{
	Node* currentNode;
	*_item = NULL;
	if(IS_NULL_LIST(_list) || NULL == _predicateFunc)
	{
		return LIST_UNINITIALIZED;
	}
	currentNode = _list->m_tail;
	while(NULL != currentNode)
	{
		if(_predicateFunc(currentNode->m_data, _context))
		{
			*_item = currentNode->m_data;
			break;
		}
		currentNode = currentNode->m_prev;
	}
	return LIST_OK;
}

size_t ListCountItems(const List* _list)
{
	Node* currentNode;
	size_t count = 0;
	if(IS_NULL_LIST(_list))
	{
		return 0;
	}
	
	currentNode = _list->m_head;
	while(NULL != currentNode)
	{
		++count;
		currentNode = currentNode->m_next;
	}
	return count;
}

int ListIsEmpty(const List* _list)
{
	if(IS_NULL_LIST(_list) || NULL == _list->m_head)
	{
		return 1;
	}
	return 0;
}

size_t ListForEach(const List* _list, UserActionFunc _action, void* _context)
{
	Node* currentNode;
	size_t countSuccess = 0;
	if(IS_NULL_LIST(_list) || NULL == _action)
	{
		return 0;
	}
	currentNode = _list->m_head;
	while(NULL != currentNode)
	{
		countSuccess += (size_t)_action(currentNode->m_data, _context);
		currentNode = currentNode->m_next;
	}
	return countSuccess;
}

void PrintList(const List* _list, UserActionFunc _printElement)
{
	printf("the vector elements are: ");
	ListForEach(_list, _printElement, NULL);
	printf("\n");
}

