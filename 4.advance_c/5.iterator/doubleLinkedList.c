#include <stdlib.h>
#include <stdio.h>

#include "doubleLinkedList.h"

#define LIST_MAGIC_NUMBER 0X222222

#define HEAD(list) (list->m_head.m_next)
#define TAIL(list) (list->m_tail.m_prev)
#define TAIL_SENTINAL(list) (&((list)->m_tail))
#define IS_NULL_LIST(list) (NULL == (list) ||  LIST_MAGIC_NUMBER != (list)->m_magicNumber)
#define IS_EMPTY_LIST(list) (TAIL(list) == &((list)->m_head))
#define IS_BIGGER(list_a, list_b) ((list_a) > (list_b))

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	int m_magicNumber;
	Node m_head;
	Node m_tail;
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
	while(NULL != _head->m_next)
	{
		nextNode = _head->m_next;
		_destroyElemFunc(_head->m_data, NULL);
		free(_head);
		_head = nextNode;
	}
}

static void InsertHead(List* _list, Node* _newHead)
{
	HEAD(_list)->m_prev = _newHead;
	_newHead->m_next = HEAD(_list);
	_newHead->m_prev = &(_list->m_head);
	HEAD(_list) = _newHead;
}

static void InsertTail(List* _list, Node* _newTail)
{
	TAIL(_list)->m_next = _newTail;
	_newTail->m_prev = TAIL(_list);
	_newTail->m_next = &(_list->m_tail);
	TAIL(_list) = _newTail;
}

static void ListInsertBeforeNode(Node* _node, Node* _toInsert)
{
	if(NULL != _node->m_prev)
	{
		_node->m_prev->m_next = _toInsert;
	}
	_toInsert->m_next = _node;
	_toInsert->m_prev = _node->m_prev;
	_node->m_prev = _toInsert;
}

static void ListDeleteNode(Node* _toDelete)
{
	_toDelete->m_next->m_prev = _toDelete->m_prev;
	_toDelete->m_prev->m_next = _toDelete->m_next;
	free(_toDelete);
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
	HEAD(newList) = &(newList->m_tail);
	TAIL(newList) = &(newList->m_head);
	return newList;
}

void ListDestroy(List** _list, UserActionFunc _destoryFunc)
{
		DestroyNodes((*_list)->m_head.m_next, _destoryFunc);
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
	if(IS_EMPTY_LIST(_list))
	{
		return LIST_IS_EMPTY;
	}
	
	/* get the data */
	*_data = HEAD(_list)->m_data;
	/* remove the head */
	HEAD(_list)->m_next->m_prev = &(_list->m_head);
	HEAD(_list) = HEAD(_list)->m_next;
	
	return LIST_OK;
}

ListErrors ListPopTail(List* _list, void* *_data)
{
	if(IS_NULL_LIST(_list))
	{
		return LIST_UNINITIALIZED;
	}
	if(IS_EMPTY_LIST(_list))
	{
		return LIST_IS_EMPTY;
	}
	
	/* get the data */
	*_data = TAIL(_list)->m_data;
	/*remove the tail*/
	TAIL(_list)->m_prev->m_next = &(_list->m_tail);
	TAIL(_list) = TAIL(_list)->m_prev;
	
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
	currentNode = HEAD(_list);
	while(&(_list->m_tail) != currentNode)
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
	currentNode = TAIL(_list);
	while(&(_list->m_tail) != currentNode)
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
	
	currentNode = HEAD(_list);
	while(&(_list->m_tail) != currentNode)
	{
		++count;
		currentNode = currentNode->m_next;
	}
	return count;
}

int ListIsEmpty(const List* _list)
{
	int result;
	if(IS_NULL_LIST(_list))
	{
		return 1;
	}
	result = IS_EMPTY_LIST(_list);
	return result;
}

size_t ListForEach(const List* _list, UserActionFunc _action, void* _context)
{
	Node* currentNode;
	size_t countSuccess = 0;
	if(IS_NULL_LIST(_list) || NULL == _action)
	{
		return 0;
	}
	currentNode = HEAD(_list);
	while(&(_list->m_tail) != currentNode)
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


/*--------------------iterator functions-----------------------*/


ListItr ListItr_Begin(const List* _list)
{
	if(IS_NULL_LIST(_list))
	{
		return NULL;
	}
	return (ListItr)HEAD(_list);
}

ListItr ListItr_End(const List* _list)
{
	if(IS_NULL_LIST(_list))
	{
		return NULL;
	}
	return (ListItr)TAIL_SENTINAL(_list);
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	return _a == _b;
}

ListItr ListItr_Next(ListItr _itr)
{
	if(NULL == _itr || NULL == ((Node*)_itr)->m_next)
	{
		return _itr;
	}
	return ((Node*)_itr)->m_next;
}

ListItr ListItr_Prev(ListItr _itr)
{
	if(NULL == _itr || NULL == ((Node*)_itr)->m_prev->m_prev)
	{
		return _itr;
	}
	return ((Node*)_itr)->m_prev;
}

void* ListItr_Get(ListItr _itr)
{
	if(NULL == _itr || NULL == ((Node*)_itr)->m_next)
	{
		return NULL;
	}
	return ((Node*)_itr)->m_data;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	Node* returnVal;
	if(NULL == _itr || NULL == ((Node*)_itr)->m_next)
	{
		return NULL;
	}
	
	returnVal = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	return returnVal;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node* newNode;
	if(NULL == _itr)
	{
		return NULL;
	}
	newNode = CreateNode(_element);
	ListInsertBeforeNode((Node*)_itr, newNode);
	return newNode;
}

ListItr ListItr_Remove(ListItr _itr)
{
	void* retval;
	if(NULL == _itr)
	{
		return NULL;
	}
	retval = ((Node*)_itr)->m_data;
	ListDeleteNode((Node*)_itr);
	return retval;
}



