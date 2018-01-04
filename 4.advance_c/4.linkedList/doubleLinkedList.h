#ifndef __GENERIC_DOUBLE_LINKED_LIST_H__
#define __GENERIC_DOUBLE_LINKED_LIST_H__

/** 
 * @brief Create a Generic Double Linked List data type
 * that stores pointer to user provided elements of generic type
 * The Double Linked List is heap allocated and can grow and shrink on demand.
 * 
 * @author Author Nadav Mizrahi (nadav.mizrahi16@gmail.com)
*/


#include <stddef.h> /* type_t */

typedef enum
{
    LIST_OK,
    LIST_UNINITIALIZED,
    LIST_ALLOCATION_FAILED,
    LIST_IS_EMPTY,
    LIST_ITEM_NOT_FOUND
} ListErrors;

typedef struct List List;

/**
 * @brief A template to a user function that can work on an element in the list.
 *
 * @param[in] _element: Pointer to the item in the list.
 * @param[in] _context: a context in which the function should work.
 *
 * @return 1 on success / 0 on fail.
*/
typedef int (*UserActionFunc)(void* _element, void* _context);

typedef int (*PredicateFunc)(void* _element, void* _context);

/**
 * @brief The function creates a list.
 *
 * @return List*: on success / NULL on fail.
*/
List* ListCreate(void);

/**
 * @brief The function destroys a list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _destroyFunc: Pointer to a destory function for the data.
 *
 * @return void
*/
void ListDestroy(List** _list, UserActionFunc _destoryFunc);

/**
 * @brief The function push data to the head of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _data: Pointer to the data to add.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval LIST_ALLOCATION_FAILED if it failed to create node.
*/
ListErrors ListPushHead(List* _list, void* _data);

/**
 * @brief The function push data to the tail of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _data: Pointer to the data to add.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval LIST_ALLOCATION_FAILED if it failed to create node.
*/
ListErrors ListPushTail(List* _list, void* _data);

/**
 * @brief The function removes data from the head of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in/out] _data: Pointer to pointer of variable to receive the deleted item.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval ERR_LIST_IS_EMPTY if the list is empty.
*/
ListErrors ListPopHead(List* _list, void* *_data);

/**
 * @brief The function removes data from the tail of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in/out] _data: Pointer to pointer of variable to receive the deleted item.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval ERR_LIST_IS_EMPTY if the list is empty.
*/
ListErrors ListPopTail(List* _list, void* *_data);

/**
 * @brief The function searches if a data exists in the list.
 *        It will return the first item that matches from the head.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _predicateFunc: Pointer to a function to predicate it according to a context.
 * @param[in] _context: Pointer to the context to pass to the Predicate function.
 * @param[in/out] _item: Pointer to pointer to store the pointer for data.
 *                       If the data is not found then it will be set to NULL.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
*/
ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item);

/**
 * @brief The function searches if a data exists in the list.
 *        It will return the first item that matches from the tail.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _predicateFunc: Pointer to a function to predicate it according to a context.
 * @param[in] _context: Pointer to the context to pass to the Predicate function.
 * @param[in/out] _item: Pointer to pointer to store the pointer for data.
 *                       If the data is not found then it will be set to NULL.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
*/
ListErrors FindFirstBackward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item);

/**
 * @brief The function counts the amount of nodes.
 *
 * @param[in] _list: Pointer to a list.
 *
 * @return The number of nodes in the list.
 *
 * @warning Will return 0 if _list is null.
*/
size_t ListCountItems(const List* _list);

/**
 * @brief The function checks if the list is empty.
 *
 * @param[in] _list: Pointer to a list.
 *
 * @return 1 if empty / 0 if not.
 *
 * @warning Will return 0 if _list is null.
*/
int ListIsEmpty(const List* _list);

/**
 * @brief The function perform an action on each individual item in the list. 
 * @param[in] _list: Pointer to a list.
 * @param[in] _action: Pointer to a function of the action to perform.
 * @param[in] _context: Pointer context value for the action.
 * @return The number of times (items) the action was perform on.
 *
 * @warning On NULL pointer to a list or funciton, the return value will be 0.
*/
size_t ListForEach(const List* _list, UserActionFunc _action, void* _context);


/*----------------test functions----------------*/

/**
 * @brief prints a double linked list
 * @param[in] _list - the list to print
 * @param[in] _printElement - pointer to a user defined function that prints a single element in the list
 */
void PrintList(const List* _list, UserActionFunc _printElement);
#endif /* #ifndef __GENERIC_DOUBLE_LINKED_LIST_H__ */
