#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "stack.h"
#include "ADTErr.h"

#define DEFAULT_SIZE 5
#define DEFAULT_BRAKET_SIZE 5 
struct Stack
{

    Vector *m_vector;

} ;

Stack* StackCreate( size_t _size, size_t _blockSize)
{
	Vector* newVect;
	Stack* newStack = malloc(sizeof(Stack));
	if(!newStack)
	{
		return NULL;
	}
	newVect = VectorCreate(_size, _blockSize);
	if(!newVect)
	{
		free(newStack);
		return NULL;
	}
	(*newStack).m_vector = newVect;
	return newStack;
}

void StackDestroy(Stack* _stack)
{
	if(_stack)
	{
		if((*_stack).m_vector)
		{
			VectorDestroy((*_stack).m_vector);
		}
		free(_stack);
	}
}

ADTErr StackPush(Stack* _stack, int  _item)
{
	if(!_stack || !(*_stack).m_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorAdd((*_stack).m_vector,  _item);
}

ADTErr StackPop(Stack* _stack, int* _item)
{
	if(!_stack || !(*_stack).m_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDelete((*_stack).m_vector,  _item);
}

ADTErr StackTop(Stack* _stack, int* _item)
{
	Vector* myVec;
	if(!_stack || !(*_stack).m_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	myVec = (*_stack).m_vector;
	return VectorGet(myVec, (*myVec).m_nItems , _item);
}

int StackIsEmpty(Stack *_stack)
{
	int result;
	ADTErr error;
	Vector* myVec;
	if(!_stack || !(*_stack).m_vector)
	{
		return 1;
	}
	myVec = (*_stack).m_vector;
	error = VectorGet(myVec, 1, &result);
	if(ERR_OK != error)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*  Unit-Test functions  */

void StackPrint(Stack *_stack)
{
	if(_stack && (*_stack).m_vector)
	{
		VectorPrint((*_stack).m_vector);
	}

}

int isBraketCorrect(char* string)
{	
	int i = 0;
	ADTErr error;
	int stackTop;
	char nextChar = 'a';
	Stack* braketStack;
	braketStack = StackCreate(DEFAULT_SIZE, DEFAULT_BRAKET_SIZE);
	while(nextChar != '\0')
	{
		nextChar = string[i];
		switch(nextChar)
		{
			/* if charecter is open brackets push to stack */
			case '(':
				StackPush(braketStack, ')');
				break;
			
			case '[':
				StackPush(braketStack, ']');
				break;
				
			case '{':
				 StackPush(braketStack, '}');
				 break;
				 
			/* if charecter is close brackets compare against top */
			case ')':
			case ']':
			case '}':
				error = StackPop(braketStack, &stackTop);
				if(stackTop != nextChar || error == ERR_UNDERFLOW)
				{
					return 0;
				}
			break;
		}
		++i;
	}
	if(StackIsEmpty(braketStack))
	{
		return 1;
	}
	return 0;
}


