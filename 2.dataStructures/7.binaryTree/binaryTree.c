#include <stdlib.h>
#include <stdio.h>
#include "binaryTree.h"
#include "ADTErr.h"

#define MAGIC_NUMBER 666666
/*******************tree struct********************/

struct Node
{
	int m_data;
	unsigned int m_magicNumber;
	struct Node* m_left;
	struct Node* m_right;
	struct Node* m_father;
};

struct Tree
{
	Node* m_root;
	unsigned int m_magicNumber;
};


/*********************linked list function************************/

/*in order to avoid creating a new struct for node m_left repressents m_next in this function*/
Node* Flip(Node* _node)
{
	Node* head;
	if(NULL == _node->m_left)
	{
		return _node;
	}
	head = Flip(_node->m_left);
	_node->m_left->m_left = _node;
	_node->m_left = NULL;
	return head;
}

/**************tree functions*********************/


/*******tree general static functions*********************/

/* return 1 if node is initialized. 0 if it isn't */
static int checkNode(Node* _node)
{
	return ((NULL != _node) && (MAGIC_NUMBER == _node->m_magicNumber)) ? 1 : 0;
}

/* return 1 if tree is initialized. 0 if it isn't */
static int checkTree(Tree* _tree)
{
	return ((NULL != _tree) && (MAGIC_NUMBER == _tree->m_magicNumber)) ? 1 : 0;
}

/* returns 1 if tree is empty, 0 if it isn't */
static int TreeIsEmpty(Tree* _tree)
{
	return ((NULL == _tree->m_root) || (MAGIC_NUMBER != _tree->m_root->m_magicNumber)) ? 1 : 0;
}

/*
creates a new node initilize all the values
returns NULL if memory allocation failed.
*/
static Node* NodeCreate(int _data)
{
	Node* newNode;
	newNode = malloc(sizeof(Node));
	/*TODO use calloc instead of malloc and remove NULL lines*/
	if(NULL != newNode)
	{
		newNode->m_data = _data;
		newNode->m_left = NULL;
		newNode->m_right = NULL;
		newNode->m_father = NULL;
		newNode->m_magicNumber = MAGIC_NUMBER;
	}
	return newNode;
}

/*
check which subtree of _currentNode _data should enter.
return pointer to the pointer to it in _currentNode.
*/
static Node** FindNextNode(Node* _currentNode, int _searchData)
{
	if(_searchData < _currentNode->m_data)
	{
		return &(_currentNode->m_left);
	}
	else
	{
		return &(_currentNode->m_right);
	}
}


/************tree main functions********************/

Tree* TreeCreate()
{
	Tree* newTree = NULL;
	newTree = malloc(sizeof(Tree));
	if(NULL != newTree)
	{
		newTree->m_root = NULL;
		newTree->m_magicNumber = MAGIC_NUMBER;
	}
	return newTree;
}

/*************************************/
/*
recursive function that destroys all nodes in a tree
*/
static void destroyNodes(Node* _node)
{
	if(checkNode(_node))
	{
		destroyNodes(_node->m_left);
		destroyNodes(_node->m_right);
		_node->m_magicNumber = 0;
		free(_node);
	}
}

void TreeDestroy(Tree* _tree)
{
	if(checkTree(_tree))
	{
		destroyNodes(_tree->m_root);
		_tree->m_magicNumber = 0;
		free(_tree);
	}
}

/*************************************/

/*
recursive function that search where a new data should be inserted and insert it there.
*/
static void TreeInsertHelper(Node* _currentNode, Node* _nodeToInsert)
{
	Node** nextNode;
	/* find the path from current node to enter the new node */
	nextNode = FindNextNode(_currentNode, _nodeToInsert->m_data);
	/* if the path is empty enter the new node there */
	if(!checkNode(*nextNode))
	{
		*nextNode = _nodeToInsert;
		_nodeToInsert->m_father = _currentNode;
	}
	/* else continue to search */
	else
	{
		TreeInsertHelper(*nextNode, _nodeToInsert); 
	}
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node* newNode;
	/* check for errors */
	if(!checkTree(_tree))
	{
		return ERR_NOT_INITIALIZED;
	}
	newNode = NodeCreate(_data);
	if(NULL == newNode)
	{
		return ERR_ALLOCATION_FAILED;
	}
	/*if the tree is empty enter the node as its root*/
	if(TreeIsEmpty(_tree))
	{
		_tree->m_root = newNode;
	}
	else
	{
		TreeInsertHelper(_tree->m_root , newNode);
	}
	return ERR_OK;
}

/*************************************************/

static int TreeIsDataFoundHelper(Node* _node, int _data)
{
	Node** nextNodePointer;
	if(!checkNode(_node))
	{
		return 0;
	}
	if(_node->m_data == _data)
	{
		return 1;
	}
	nextNodePointer = FindNextNode(_node, _data);
	return TreeIsDataFoundHelper(*nextNodePointer, _data);
}

int TreeIsDataFound(Tree* _tree, int _data)
{
	if(!checkTree(_tree))
	{
		return 0;
	}
	return TreeIsDataFoundHelper(_tree->m_root, _data);
}

/*************************************************/

static void PreOrderPrint(Node* _node)
{
	if(!checkNode(_node))
	{
		printf("\n");
		return;
	}
	printf("%d ", _node->m_data);
	PreOrderPrint(_node->m_left);
	PreOrderPrint(_node->m_right);
}

static void InOrderPrint(Node* _node)
{
	if(!checkNode(_node))
	{
		printf("\n");
		return;
	}
	InOrderPrint(_node->m_left);
	printf("%d ", _node->m_data);
	InOrderPrint(_node->m_right);
}

static void PostOrderPrint(Node* _node)
{
	if(!checkNode(_node))
	{
		printf("\n");
		return;
	}
	PostOrderPrint(_node->m_right);
	printf("%d ", _node->m_data);
	PostOrderPrint(_node->m_left);
}

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	switch(_traverseMode)
	{
		case PRE_ORDER:
			PreOrderPrint(_tree->m_root);
			break;
		case IN_ORDER:
			InOrderPrint(_tree->m_root);
			break;
		case POST_ORDER:
			PostOrderPrint(_tree->m_root);
			break;
	}
}

/*****************************************/

int isFullTreeHelper(Node* _node)
{
	if(!checkNode(_node->m_left) && !checkNode(_node->m_right))
	{
		return 1;
	}
	if((!checkNode(_node->m_left) && checkNode(_node->m_right)) || (checkNode(_node->m_left) && !checkNode(_node->m_right)))
	{
		return 0;
	}
	return (isFullTreeHelper(_node->m_left) && isFullTreeHelper(_node->m_right));
}

int isFullTree(Tree* _tree)
{
	if(!checkTree(_tree))
	{
		return 0;
	}
	if(TreeIsEmpty(_tree))
	{
		return 1;
	}
	return isFullTreeHelper(_tree->m_root);
}

/*******************************************/

int myMax(int a, int b)
{
	return (a > b) ? a : b;
}

int getTreeHeightHelper(Node* _node)
{
	if(!checkNode(_node))
	{
		return 0;
	}
	return myMax(getTreeHeightHelper(_node->m_left), getTreeHeightHelper(_node->m_right)) + 1;
}

int getTreeHeight(Tree* _tree)
{
	if(!checkTree(_tree))
	{
		return -1;
	}
	if(TreeIsEmpty(_tree))
	{
		return 0;
	}
	return getTreeHeightHelper(_tree->m_root);
}
