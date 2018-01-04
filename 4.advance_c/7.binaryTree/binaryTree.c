#include <stdlib.h>
#include <stdio.h>
#include "../../inc/bin_tree.h"

#define MAGIC_NUMBER 33333

#define ROOT(tree) ((tree)->m_sentinel.m_left)
#define SENTINEL(tree) (&((tree->m_sentinel)))
#define IS_NULL_TREE(tree) ((NULL == tree) || (MAGIC_NUMBER != (tree)->m_magicNumber))
#define IS_TREE_EMPTY(tree) (NULL == ROOT(tree))
#define IS_SENTINEL(tree) (NULL == (tree)->m_parent)

/*-----------------tree struct----------------*/

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_left;
	Node* m_right;
	Node* m_parent;
};

struct BSTree
{
	Node m_sentinel;
	LessComparator m_less;
	size_t m_magicNumber;
};

typedef void (*TraversalFunction) (Node* _node, ActionFunction _action, void* _context, BSTreeItr* _last);

/*---------------------static functions--------------------*/

static void destroyNode(Node** _node, void (*_destroyer)(void*))
{
	_destroyer((*_node)->m_data);
	free((*_node));
	*_node = NULL;
}

static void destroyAllNodes(Node** _node, void (*_destroyer)(void*))
{
	if(NULL == (*_node))
	{
		return;
	}
	
	destroyAllNodes(&((*_node)->m_left), _destroyer);
	destroyAllNodes(&((*_node)->m_right), _destroyer);
	destroyNode(_node, _destroyer);
}

static Node* CreateNode(void* _item)
{
	Node* myNode;
	myNode = malloc(sizeof(Node));
	myNode->m_data = _item;
	return myNode;
}

static Node* FindParentLeaf(BSTree* _tree, void* _item)
{
	Node* currentNode = SENTINEL(_tree);
	Node* nextNode = ROOT(_tree);
	while(NULL != nextNode)
	{
		currentNode = nextNode;
		if(_tree->m_less(_item, currentNode->m_data))
		{
			nextNode = currentNode->m_left;
		}
		else
		{
			nextNode = currentNode->m_right;
		}
	}
	return currentNode;
}

/*-----------static iterator functions-------------*/

static BSTreeItr GoLeftest(BSTreeItr _itr)
{
	while(NULL != ((Node*)_itr)->m_left)
	{
		_itr = (BSTreeItr)(((Node*)_itr)->m_left);
	}
	return _itr;
}

static BSTreeItr GoRightest(BSTreeItr _itr)
{
	while(NULL != ((Node*)_itr)->m_right)
	{
		_itr = (BSTreeItr)(((Node*)_itr)->m_right);
	}
	return _itr;
}

static BSTreeItr GetNext(BSTreeItr _itr)
{
	if(((Node*)_itr)->m_parent->m_left == _itr)
	{
		return ((Node*)_itr)->m_parent;
	}
	return GetNext(((Node*)_itr)->m_parent);
}

static BSTreeItr GetPrev(BSTreeItr _itr)
{
	if(NULL == ((Node*)_itr)->m_parent)
	{
		return NULL;
	}
	if(((Node*)_itr)->m_parent->m_right == _itr)
	{
		return ((Node*)_itr)->m_parent;
	}
	return GetPrev(((Node*)_itr)->m_parent);
}

static void SwapNodes(Node* _a, Node* _b)
{
	void* tmp = _b->m_data;
	_b->m_data = _a->m_data;
	_a->m_data = tmp;
}

/*---------------static remove function--------------------*/

static void ConnectChildToParent(Node* _currentNode, Node* _child)
{
	if(_currentNode == _currentNode->m_parent->m_right)
	{
		_currentNode->m_parent->m_right = _child;
	}
	else
	{
		_currentNode->m_parent->m_left = _child;
	}
}

static void* RemoveWithoutLeft(Node* _toDelete)
{
	void* data = _toDelete->m_data;
	
	/*replace the node whith its right child if it exists*/
	ConnectChildToParent(_toDelete, _toDelete->m_right);
	if(NULL != _toDelete->m_right)
	{
		_toDelete->m_right->m_parent = _toDelete->m_parent;
	}
	
	free(_toDelete);
	return data;
}

static void* RemoveWhithoutRight(Node* _toDelete)
{
	void* data = _toDelete->m_data;
	
	/*replace the left child with the node to delete*/
	ConnectChildToParent(_toDelete, _toDelete->m_left);
	_toDelete->m_left->m_parent = _toDelete->m_parent;
	
	free(((Node*)_toDelete));
	return data;
}

static void* RemoveWithTwoChilds(Node* _toDelete)
{
	Node* toReplace;
	
	toReplace = (Node*)GoLeftest((BSTreeItr)(_toDelete->m_right));
	SwapNodes(_toDelete, toReplace);
	
	return RemoveWithoutLeft(toReplace);
}

/*-------------------main tree functions-------------------*/

BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* myTree;
	
	if(NULL == _less)
	{
		return NULL;
	}
	
	myTree = malloc(sizeof(BSTree));
	if(NULL == myTree)
	{
		return NULL;
	}
	myTree->m_sentinel.m_right = SENTINEL(myTree);
	myTree->m_less = _less;
	myTree->m_magicNumber = MAGIC_NUMBER;
	
	return myTree;
}

/*---------------------------------------------*/

void  BSTree_Destroy(BSTree* _tree, void (*_destroyer)(void*))
{
	if(IS_NULL_TREE(_tree))
	{
		return;
	}
	destroyAllNodes(&(ROOT(_tree)), _destroyer);
	_tree->m_magicNumber = 0;
	free(_tree);
}

/*---------------------------------------------*/

BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	Node* parent;
	Node* newNode;
	
	/*error checks*/
	if(IS_NULL_TREE(_tree))
	{
		return NULL;
	}
	
	/*create the new node*/
	newNode = CreateNode(_item);
	if(NULL == newNode)
	{
		return SENTINEL(_tree);
	}
	
	/* get the new nodes parent */
	parent = FindParentLeaf(_tree, _item);
	newNode->m_parent = parent;
	
	/*insert the node to its parent*/
	if(IS_TREE_EMPTY(_tree) || _tree->m_less(_item, parent->m_data))
	{
		parent->m_left = newNode;
	}
	else
	{
		parent->m_right = newNode;
	}
	return (BSTreeItr)newNode;
}

/*------------------------------------------------*/

BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	if(IS_NULL_TREE(_tree))
	{
		return NULL;
	}
	if(IS_TREE_EMPTY(_tree))
	{
		return (BSTreeItr)SENTINEL(_tree);
	}
	return GoLeftest((BSTreeItr)ROOT(_tree));
}

BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(IS_NULL_TREE(_tree))
	{
		return NULL;
	}
	return (BSTreeItr)SENTINEL(_tree);
}

/*----------------------------------------------------*/

int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	if(_a == _b)
	{
		return 1;
	}
	return 0;
}

/*-----------------------------------------------------*/

BSTreeItr BSTreeItr_Next(BSTreeItr _itr)
{
	BSTreeItr next;
	
	if( NULL == _itr || NULL == ((Node*)_itr)->m_parent)
	{
		return _itr;
	}
	next = (((Node*)_itr)->m_right);
	
	if(NULL != next)
	{
		return GoLeftest(next);
	}
	
	return GetNext((Node*)_itr);
}

/*----------------------------------------------------------*/

BSTreeItr BSTreeItr_Prev(BSTreeItr _itr)
{
	BSTreeItr prev;
	
	if(NULL == _itr)
	{
		return NULL;
	}
	
	prev = (((Node*)_itr)->m_left);
	
	if(NULL != prev)
	{
		return GoRightest(prev);
	}
	
	prev = GetPrev((Node*)_itr);
	return (NULL != prev) ? prev : _itr;
}

/*---------------------------------------------------------*/

void* BSTreeItr_Get(BSTreeItr _itr)
{
	if(NULL == _itr || IS_SENTINEL((Node*)_itr))
	{
		return NULL;
	}
	return ((Node*)_itr)->m_data;
}

/*---------------------------------------------------------*/

BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
	Node* currentNode;
	int direction;
	
	if(IS_NULL_TREE(_tree) || NULL == _predicate)
	{
		return NULL;
	}
	
	currentNode = ROOT(_tree);
	while(NULL != currentNode)
	{
		direction = _predicate(_context, currentNode->m_data);
		if(0 == direction)
		{
			return (BSTreeItr)currentNode;
		}
		if(0 < direction)
		{
			currentNode = currentNode->m_right;
		}
		else
		{
			currentNode = currentNode->m_left;
		}
	}
	return NULL;
}

/*---------------------------------------------------------*/

void* BSTreeItr_Remove(BSTreeItr _itr)
{
	Node* node = (Node*)_itr;
	if(NULL == node)
	{
		return NULL;
	}
	
	if(NULL == node->m_left)
	{
		return RemoveWithoutLeft(node);
	}
	
	if(NULL == node->m_right)
	{
		return RemoveWhithoutRight(node);
	} 
	
	return RemoveWithTwoChilds(node);
}

/*-----------------------------------------------------------*/

static void InOrderForEach(Node* _node, ActionFunction _action, void* _context, BSTreeItr* _last)
{
	if(NULL == _node)
	{
		return;
	}
	InOrderForEach(_node->m_left, _action, _context, _last);
	_action(_node->m_data, _context);
	InOrderForEach(_node->m_right, _action, _context, _last);
	*_last = (BSTreeItr)_node;
}

static void PreOrderForEach(Node* _node, ActionFunction _action, void* _context, BSTreeItr* _last)
{
	if(NULL == _node)
	{
		return;
	}
	_action(_node->m_data, _context);
	PreOrderForEach(_node->m_left, _action, _context, _last);
	PreOrderForEach(_node->m_right, _action, _context, _last);
	*_last = (BSTreeItr)_node;
}

static void PostOrderForEach(Node* _node, ActionFunction _action, void* _context, BSTreeItr* _last)
{
	if(NULL == _node)
	{
		return;
	}
	PostOrderForEach(_node->m_right, _action, _context, _last);
	_action(_node->m_data, _context);
	PostOrderForEach(_node->m_left, _action, _context, _last);
	*_last = (BSTreeItr)_node;
}

BSTreeItr BSTree_ForEach(const BSTree* _tree, TreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
{
	BSTreeItr last = NULL;
	static TraversalFunction traversalFuncs[3] = {PreOrderForEach, InOrderForEach, PostOrderForEach};
	
	traversalFuncs[_mode](ROOT(_tree), _action, _context, &last);
	
	return last;
}

