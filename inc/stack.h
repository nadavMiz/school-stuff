#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack Stack;

/* templet of user defined function to make an action on an element in the stack*/
typedef int (*ActionFunction) (void* _element, void* _context)

/* enumerator of possible stack errors */
typedef enum
{
	STACK_OK,
	STACK_NOT_INITIAIZED,
	STACK_ALLOCATION_FAILED,
	STACK_EMPTY,
	
} StackError;

/**
 * @brief creates a new stack
 * 
 * @return pointer to the new stack / NULL on fail
 */
Stack* StackCreate();

/**
 * @brief destroys a stack changes the stacks pointer to NULL
 * @param[in] _stack - pointer to the stack to destroy
 * @param[in] _destroyFunc - Pointer to a destory function for the data.
 *
 * @return void
 */
void StackDestroy(Stack** _stack, ActionFunction _destroyFunc);

/**
 * @brief inserts a new item to the top of the stack
 * @param[in] _stack: stack to insert element to
 * @param[in] _item: item to insert
 *
 * @return OK on success. error on FAIL
 * @retval STACK_OK: insert was successful
 * @retval STACK_NOT_INITIAIZED: stack was not initialized
 * @retval STACK_ALLOCATION_FAILED: node allocation failed
 */
ADTErr StackPush(Stack* _stack, void*  _item);

/**
 * @brief remove item from the top of the stack
 * @param[in] _stack: stack to remove item from.
 * @param[in] _item: pointer to store the removed item in
 *
 * @return OK on success/ error on fail
 * @retval STACK_OK: item was removed successfully
 * @retval STACK_NOT_INITIAIZED: the stack was not initialized
 * @retval STACK_EMPTY: stack was empty.
 */
ADTErr StackPop(Stack* _stack, void** _item);

/**
 * @brief get the top element in the stack without removing it
 * @param[in] _stack: the stack to get the top element from
 * @param[in] _item: pointer to store the top item
 * 
 * @return OK on success/ error on fail
 * @retval STACK_OK: item was gotten successfully
 * @retval STACK_NOT_INITIAIZED: stack was not initialized
 * @retval STACK_EMPTY: stack was empty
 */
ADTErr StackTop(Stack* _stack, void** _item);

/**
 * @brief check if stack is empty
 * @param[in] _stack: stack to check
 * @return 1 if empty, 0 if not
 */
int StackIsEmpty(Stack *_stack);

/*  Unit-Test functions  */

/**
 * @brief prints all the elements in the stack
 * @param[in] _stack: stack to print
 * @param[in] _printFunc: user defined function that prints an eement in the stack
 * @return void 
 */
void StackPrint(Stack *_stack, (void) (*_printFunc) (void* _element));

#endif /* #ifndef __STACK_H__ */
