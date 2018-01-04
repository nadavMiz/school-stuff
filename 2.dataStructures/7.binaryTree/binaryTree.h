#ifndef __BINARY_TREE__
#define __BINARY_TREE__
#include "ADTErr.h"

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
	
} TreeTraverse;

typedef struct Node Node;

typedef struct Tree Tree;

/*************Linked list function*********************/

/*
reverse a linked list so that each element will point to the previous one instead of the next one.
input _Head: the head node of the linked list you want to reverse
returns: the new head of the reversed linked list
*/
Node* Flip(Node* _node);

/*************tree functions***************************/

/*
creates a new instence of the tree struct.
returns: pinter to the new tree. returns NULL if a problem accurred
*/
Tree* TreeCreate();

/*
destroys an instence of the tree struct. does nothing if the instance was already destroyed.
*/
void TreeDestroy(Tree* _tree);

/*
insert a new elemnt to a tree.
input _tree: the tree to put the element to.
input data: the new data to put in the tree
returns ERR_OK if the insert was successful. an error otherwise
*/
ADTErr TreeInsert(Tree* _tree, int data);

/*
checks if a data is in the tree.
input _tree: the tree to search
input _data: the element to search in the tree.
returns: 1 if the element is in the tree. 0 otherwise
*/
int TreeIsDataFound(Tree* _tree, int _data);


/*
prints the tree to the screen
*/
void TreePrint(Tree* _tree, TreeTraverse _traverseMode);

/*
returns 1 if tree is full, 0 if it isn't if if a problem accured(tree not initialized)
*/
int isFullTree(Tree* _tree);



#endif /* ifndef __BINARY_TREE__ */
