#include <stdio.h>
#include "vector.h"
#include "stack.h"
#include "ADTErr.h"
void testStackCreateNormal()
{
	Stack* myStack;
	int intial_size = 15;
	int block_size = 10;
	myStack = StackCreate(intial_size, block_size);
	if(myStack)
	{
		printf("PASSED create stack normal \n");
	}
	else
	{
		printf("FAILED create stack normal \n");
	}
	StackDestroy(myStack);
}

void testStackCreateNoInitialSize()
{
	Stack* myStack;
	int intial_size = 0;
	int block_size = 10;
	myStack = StackCreate(intial_size, block_size);
	if(myStack)
	{
		printf("PASSED create stack normal \n");
	}
	else
	{
		printf("FAILED create stack normal \n");
	}
	StackDestroy(myStack);
}

void testStackCreateNoBlockSize()
{
	Stack* myStack;
	int intial_size = 15;
	int block_size = 0;
	myStack = StackCreate(intial_size, block_size);
	if(myStack)
	{
		printf("PASSED create stack normal \n");
	}
	else
	{
		printf("FAILED create stack normal \n");
	}
	StackDestroy(myStack);
}

void testStackInvalidInput()
{
	Stack* myStack;
	int intial_size = -15;
	int block_size = -10;
	myStack = StackCreate(intial_size, block_size);
	if(!myStack)
	{
		printf("PASSED create stack invalid input \n");
	}
	else
	{
		printf("FAILED create stack invalid input \n");
	}
	StackDestroy(myStack);
}


void testStackPushNormal()
{
	Stack* myStack;
	ADTErr error;
	myStack = StackCreate(15, 10);
	error = StackPush(myStack,  5);
	if (error == ERR_OK)
	{
		printf("PASSED push normal\n");
	}
	else
	{
		printf("FAILED push normal\n");
	}
	StackDestroy(myStack);
}

void testStackPushNoBlockSize()
{
	int i;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(2, 0);
	for(i = 0; i < 3; ++i)
	{
		error = StackPush(myStack,  i);
	}
	if (error != ERR_OVERFLOW)
	{
		printf("FAILED push no block size NULL\n");
	}
	else
	{
		printf("PASSED push no block size NULL\n");
	}	
	StackDestroy(myStack);
}
void testStackPushWithRealoc()
{
	int i;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(2, 3);
	for(i = 0; i < 3; ++i)
	{
		error = StackPush(myStack,  i);
	}
	if (error == ERR_OK)
	{
		printf("PASSED push with realocate\n");
	}
	else
	{
		printf("FAILED push with realocate\n");
	}
	StackDestroy(myStack);
}

void testStackPushNoCapacity()
{
	int i;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(0, 3);
	for(i = 0; i < 3; ++i)
	error = StackPush(myStack,  5);
	if (error == ERR_OK)
	{
		printf("PASSED push no capacity \n");
	}
	else
	{
		printf("FAILED push no capacity \n");
	}
	StackDestroy(myStack);
}
void testStackPushInvalidVector()
{
	ADTErr error;
	Stack* myStack;
	error = StackPush(myStack,  2);
	if (error != ERR_NOT_INITIALIZED)
	{
		printf("FAILED push NULL vector\n");
	}
	else
	{
		printf("PASSED push NULL vector\n");
	}
	StackDestroy(myStack);	
}

void testStackPop()
{
	int i;
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(15, 10);
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	error = StackPop(myStack,  &result);
	if (error == ERR_OK && result == 4)
	{
		printf("PASSED pop normal\n");
	}
	else
	{
		printf("FAILED pop normal\n");
	}
	StackDestroy(myStack);
}
void testStackPopEmpty()
{
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(15, 10);
	error = StackPop(myStack,  &result);
	if (error == ERR_UNDERFLOW)
	{
		printf("PASSED pop empty vector\n");
	}
	else
	{
		printf("FAILED pop empty vector\n");
	}
	StackDestroy(myStack);
}
void testStackPopNullDest()
{
	int i;
	int* result = NULL;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(15, 10);
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	error = StackPop(myStack,  result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED pop no destination int\n");
	}
	else
	{
		printf("FAILED pop no destination int\n");
	}
	StackDestroy(myStack);
}
void testStackPopNullVector()
{
	int i;
	int result;
	ADTErr error;
	Stack* myStack;
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	error = StackPop(myStack,  &result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED pop NULL vector int\n");
	}
	else
	{
		printf("FAILED pop NULL vector int\n");
	}
	StackDestroy(myStack);
}

void testStackPopWithRealoc()
{
	int i;
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(5, 5);
	for(i = 0; i < 16; ++i)
	{
		StackPush(myStack,  i);
	}
	for(i = 0; i < 7; ++i)
	{
		error = StackPop(myStack,  &result);
	}
	if (error == ERR_OK && result == 9)
	{
		printf("PASSED pop with realoc\n");
	}
	else
	{
		printf("FAILED pop with realoc\n");
	}
	StackDestroy(myStack);
}

void testStackPopWithRealocLessThanCapacity()
{
	int i;
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(5, 5);
	for(i = 0; i < 16; ++i)
	{
		StackPush(myStack,  i);
	}
	for(i = 0; i < 14; ++i)
	{
		error = StackPop(myStack,  &result);
	}
	if (error == ERR_OK && result == 2)
	{
		printf("PASSED pop with realoc\n");
	}
	else
	{
		printf("FAILED pop with realoc\n");
	}
	StackDestroy(myStack);
}

void testStackTop()
{
	int i;
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	error = StackTop(myStack, &result);
	if (error == ERR_OK && result == 4)
	{
		printf("PASSED Top normal\n");
	}
	else
	{
		printf("FAILED Top normal\n");
	}
	StackDestroy(myStack);
}

void testStackTopEmpty()
{
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = StackCreate(10, 5);
	error = StackTop(myStack, &result);
	if (error == ERR_UNDERFLOW)
	{
		printf("PASSED top empty index\n");
	}
	else
	{
		printf("FAILED top empty index\n");
	}
	StackDestroy(myStack);
}


void testStackTopNULLstack()
{
	int i;
	int result;
	ADTErr error;
	Stack* myStack;
	myStack = NULL;
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	error = StackTop(myStack, &result);
	if (error == ERR_NOT_INITIALIZED)
	{
		printf("PASSED top NULL stack\n");
	}
	else
	{
		printf("FAILED top NULL stack\n");
	}
	StackDestroy(myStack);
}

void testStackIsEmptyFull()
{
	int i;
	int result;
	Stack* myStack;
	myStack = StackCreate(10, 5);
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	result = StackIsEmpty(myStack);
	if (0 == result)
	{
		printf("PASSED is empty while full\n");
	}
	else
	{
		printf("FAILED is empty while full\n");
	}
	StackDestroy(myStack);
}

void testStackIsEmptyEmpty()
{
	int result;
	Stack* myStack;
	myStack = StackCreate(10, 5);
	result = StackIsEmpty(myStack);
	if (1 == result)
	{
		printf("PASSED is empty while empty\n");
	}
	else
	{
		printf("FAILED is empty while empty\n");
	}
	StackDestroy(myStack);
}
void testStackIsEmptyNULLVector()
{
	int i;
	int result;
	Stack* myStack;
	for(i = 0; i < 5; ++i)
	{
		StackPush(myStack,  i);
	}
	result = StackIsEmpty(myStack);
	if (result == 1)
	{
		printf("PASSED is empty NULL stack\n");
	}
	else
	{
		printf("FAILED is empty NULL stack\n");
	}
}

void wildTest()
{
	int i;
	int result;
	int isEmpty;
	Stack* myStack;
	myStack = StackCreate(10, 5);
	for(i = 0; i < 10; ++i)
	{
		StackPush(myStack,  i);
	}
	for(i = 0; i < 5; ++i)
	{
		StackPop(myStack, &result);
		if (result != 9 - i)
		{
			printf("FAILED wild test0\n");
			return;
		}
	}
	StackTop(myStack , &result);
	isEmpty = StackIsEmpty(myStack);
	if(result != 4 || isEmpty == 1)
	{
		printf("FAILED wild test1\n");
		return;
	}
	for(i = 0; i < 12; ++i)
	{
		StackPop(myStack, &result);
	}
	isEmpty = StackIsEmpty(myStack);
	if(isEmpty == 0)
	{
		printf("FAILED wild test2\n");
	}
	else
	{
		printf("PASSED wild test\n");
	}
}

void bracketTest()
{
	int normal;
	int wrongOrder;
	int noCloser;
	int toMuchCloser;
	char string1[40] = "dfds(gfhgf)453454[({88})()]fdsfds()";
	char string2[20] = "dfgdfg(()hgjh{)}";
	char string3[30] = "sdfd()hgfhg[()]g(fh[{jhgj}]667";
	char string4[12] = "asd()gfhg{}}";
	
	normal = isBraketCorrect(string1);
	wrongOrder = isBraketCorrect(string2);
	noCloser = isBraketCorrect(string3);
	toMuchCloser = isBraketCorrect(string4);
	if(normal && !wrongOrder && !noCloser && !toMuchCloser)
	{
		printf("PASSED brackets test\n");
	}
	else
	{
		printf("FAILED brackets test\n");
	}
}
	
int main() {
	testStackCreateNormal();
	testStackInvalidInput();
	testStackCreateNoInitialSize();
	testStackCreateNoBlockSize();

	testStackPushNormal();
	testStackPushNoBlockSize();
	testStackPushWithRealoc();
	testStackPushNoCapacity();
	testStackPushInvalidVector();

	testStackIsEmptyFull();
	testStackIsEmptyEmpty();
	testStackIsEmptyNULLVector();

	testStackTop();
	testStackTopEmpty();
	testStackTopNULLstack();

	testStackPop();
	testStackPopEmpty();
	testStackPopNullDest();
	testStackPopNullVector();
	testStackPopWithRealoc();
	testStackPopWithRealocLessThanCapacity();
	wildTest();
	bracketTest();
	return 0;
}

