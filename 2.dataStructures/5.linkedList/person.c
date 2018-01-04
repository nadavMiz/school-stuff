#include <stdio.h>
#include "person.h"

/***************************************************************************/
Person* ListInsertHead(Person* _head, Person* _p)
{
	if(NULL == _head)
	{
		return _p;
	}
	if(NULL == _p)
	{
		return _head;
	}
	_p->m_next = _head;
	return _p;
}

/***************************************************************************/

Person* ListRemoveHead(Person* _head, Person** _item)
{
	Person* newHead;
	if(NULL == _head)
	{
		*_item = NULL;
		return NULL;
	}
	*_item = _head;
	/* set the next item on the list as the new head */
	newHead = _head->m_next;
	/* remove th head from the list */
	_head->m_id = 0;
	_head->m_next = NULL;
	/* return */
	return newHead;
}

/***************************************************************************/
Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
	int i;
	Person* currentNode = _head;
	if(NULL == _head && 0 == _key)
	{
		return _p;
	}
	if(0 > _key || NULL == _head || NULL == _p)
	{
		return _head;
	}
	/* if it is the head node insert it so */
	if(0 == _key)
	{
		_p->m_next = _head;
		return _p;
	}
	/* look for the node previous to the key in the list and connect _p between it and the next node */
	for(i = 0; i < _key-1; ++i)
	{
		currentNode = currentNode->m_next;
		if(NULL == currentNode)
		{
			return _head;
		}
	}
	_p->m_next = currentNode->m_next;
	currentNode->m_next = _p;
	return _head;
}

/**********************************************************/

void ListInsertByKeyRecHelper(Person* _currentNode, int key, Person* _p)
{
	if(NULL == _currentNode)
	{
		return;
	}
	if(0 == key)
	{
		_p->m_next = _currentNode->m_next;
		_currentNode->m_next = _p;
		return;
	}
	ListInsertByKeyRecHelper(_currentNode->m_next, key - 1, _p);
}


Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	if(0 == _key && NULL==_head)
	{
		return _p;
	}
	if(0 > _key || NULL == _head || NULL == _p)
	{
		return _head;
	}
	/* if it is the head node insert it so */
	if(0 == _key)
	{
		_p->m_next = _head;
		return _p;
	}
	ListInsertByKeyRecHelper(_head, _key - 1, _p);
	return _head;
}

/**********************************************************/

Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
	int i;
	Person* currentNode = _head;
	Person* newHead;
	if(0 > _key || NULL == _head || NULL == _p)
	{
		return _head;
	}
	/* if remove the head*/
	if(0 == _key)
	{
		*_p = _head;
		newHead = _head->m_next;
		_head->m_id = 0;
		_head->m_next = NULL;
		return newHead;
	}
	/* look for the node previous to the key in the list*/
	for(i = 0; i < _key - 1; ++i)
	{
		currentNode = currentNode->m_next;
		if(NULL == currentNode)
		{
			*_p = NULL;
			return _head;
		}
	}
	/* remove the next node */
	*_p = currentNode->m_next;
	if(NULL != currentNode->m_next)
	{
		currentNode->m_next->m_id = 0;
		currentNode->m_next = currentNode->m_next->m_next;
	}
	return _head;
}

/****************************************************************/
void ListRemoveByKeyRecHelper(Person* _currentNode, int _key, Person** _p)
{
	if(NULL == _currentNode)
	{
		*_p = NULL;
		return;
	}
	if(0 == _key)
	{
		*_p = _currentNode->m_next;
		if(NULL != _currentNode->m_next)
		{
			_currentNode->m_next->m_id = 0;
			_currentNode->m_next = _currentNode->m_next->m_next;
		}
	}
	ListRemoveByKeyRecHelper(_currentNode->m_next, _key - 1, _p);
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p)
{
	Person* newHead;
	if(0 > _key || NULL == _head || NULL == _p)
	{
		return _head;
	}
	/* if remove the head*/
	if(0 == _key)
	{
		*_p = _head;
		_head->m_id = 0;
		newHead = _head->m_next;
		_head->m_next = NULL;
		return newHead;
	}
	ListRemoveByKeyRecHelper(_head, _key - 1, _p);
	return _head;
}

/****************************************************************/
void PrintList(Person* _head)
{
	int i = 0;
	while(NULL != _head)
	{
		printf("%d) id: %d, name: %s, age: %d \n", i, _head->m_id, _head->m_name, _head->m_age);
		_head = _head->m_next;
	}
}





