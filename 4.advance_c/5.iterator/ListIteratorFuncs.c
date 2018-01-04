#include "doubleLinkedList.h"
#include "ListIteratorFuncs.h"

/*-----------------static functions--------------------*/

static void SwapItr(ListItr _a, ListItr _b, void* _aElem, void* _bElem)
{
	ListItr_Set(_a, _bElem);
	ListItr_Set(_b, _aElem);
}

/*------------------main functions---------------------*/

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunc _predicate, void* _context)
{
	size_t count = 0;
	void* currentElement;
	ListItr currentItr = _begin;
	
	if(NULL == _begin || NULL == _end || NULL == _predicate)
	{
		return 0;
	}
	
	while(!ListItr_Equals(currentItr, _end))
	{
		currentElement = ListItr_Get(currentItr);
		if(_predicate(currentElement, _context))
		{
			++count;
		}
		currentItr = ListItr_Next(currentItr);
	}
	return count;
}

/*--------------------------*/

static int bubbleNode(ListItr _begin, ListItr _end, LessFunction _less)
{
	int isSorted = 1;
	ListItr currentItr = _begin;
	ListItr nextItr;
	void* currentElem;
	void* nextElem;
	
	currentElem = ListItr_Get(currentItr);
	
	for(currentItr = _begin; !ListItr_Equals(currentItr, _end); currentItr = ListItr_Next(currentItr))
	{
		/* get the next itr*/
		nextItr = ListItr_Next(currentItr);
		nextElem = ListItr_Get(nextItr);
		
		/*compare and swap if needed*/
		if(_less(nextElem, currentElem))
		{
			SwapItr(currentItr, nextItr, currentElem, nextElem);
			isSorted = 0;
		}
		else
		{
			currentElem = nextElem;
		}
	}
	return isSorted;
}

void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
	ListItr currentItr;
	ListItr currentEnd = ListItr_Prev(_end);
	
	if(NULL == _begin || NULL == _end || NULL == _less)
	{
		return;
	}
	
	for(currentItr = ListItr_Next(_begin); !ListItr_Equals(currentItr, _end); currentItr = ListItr_Next(currentItr))
	{
		if(bubbleNode(_begin, currentEnd, _less))
		{
			break;
		}
		currentEnd = ListItr_Prev(currentEnd);
	}
}

/*-------------------------------------------------*/

/* delete node from a list and add it before dest. returns the new dest (the node itself) */
static void MoveNode(ListItr _iter, ListItr _dest)
{
	void* element;
	
	element = ListItr_Remove(_iter);
	ListItr_InsertBefore(_dest, element);
}

ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr nextItr;
	ListItr currentItr = _begin;

	if(NULL == _dest || NULL == _begin || NULL == _end)
	{
		return NULL;
	}
	while(!ListItr_Equals(currentItr, _end))
	{
		nextItr = ListItr_Next(currentItr);
		MoveNode(currentItr, _dest);
		currentItr = nextItr;
	}
	return _dest;
}

/*-------------------------------------------------------------------------------*/

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr current;
	for(current = _begin; !ListItr_Equals(current, _end); current = ListItr_Next(current))
	{
		if(_predicate(ListItr_Get(current), _context))
		{
			return current;
		}
	}
	return NULL;
}

/* compares two nodes and move the bigger one before dest. change the moved node 
   to its previous and destCurrent to the new dest */
/*static void MergeInsertBigger(Node** firstCurrent, Node** secondCurrent, Node** destCurrent, LessFunction _less)
{

}

ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	Node* firstCurrent = ((Node*)_firstEnd)->m_prev;
	Node* secondCurrent = ((Node*)_secondEnd)->m_prev;
	Node* destCurrent = ((Node*)_destBegin)->m_prev;
*/	
	/* compare elements from the two sub-lists and move the larger elemet to dest  */
	/*while(firstCurrent != ((Node*)_firstBegin)->m_prev || secondCurrent != ((Node*)_secondBegin)->m_prev)
	{
		MergeInsertBigger(&firstCurrent, &secondCurrent, &destCurrent, _less);
	}
	*/
	/* move the rest of the remaining sub-list to dest */
	/*if(firstCurrent == ((Node*)_firstBegin)->m_prev)
	{
		destCurrent = ListItr_Splice(destCurrent, secondCurrent, _secondBegin);
	}
	else
	{
		destCurrent = ListItr_Splice(destCurrent, firstCurrent, _firstBegin);
	}
	return destCurrent;
}
*/
