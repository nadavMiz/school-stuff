#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "doubleLinkedList.h"

Stack* StackCreate()
{
	return ListCreate();
}

void StackDestroy(Stack** _stack, ActionFunction _destroyFunc)
{
	ListDestroy(_stack, _destroyFunc);
}

StackError StackPush(Stack* _stack, void*  _item)
{
	return ListPushHead(_stack, _item) + ERROR_OFFSET;
}

StackError StackPop(Stack* _stack, void** _item)
{
	return ListPopHead(_stack, _item) + ERROR_OFFSET;
}

StackError StackTop(const Stack* _stack, void** _item)
{
	ListErrors error;
	
	error = ListPopHead((List*)_stack, _item);
	if(LIST_OK != error)
	{
		return error + ERROR_OFFSET;
	}
	
	error = ListPushHead((List*)_stack, *_item);
	if(LIST_OK != error)
	{
		return error + ERROR_OFFSET;
	}
	
	return STACK_OK;
}

int StackIsEmpty(const Stack *_stack)
{
	return ListIsEmpty(_stack);
}

void StackPrint(Stack *_stack, ActionFunction _printFunc)
{
	printf("the stack elements are: ");
	ListForEach(_stack, _printFunc, NULL);
	printf("\n");
}


