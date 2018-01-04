#ifndef _DYNAMIC_VECTOR_
#define _DYNAMIC_VECTOR_

/** 
 * @brief Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 * 
 * @author Author Nadav Mizrahi (nadav.mizrahi16@gmail.com)
 */ 

#include "ADTErr.h" /* ADTErr enum */
#include <stddef.h> /* size_t */

/*
templet for a user defined function that make changes on an element in the vector
returns 1 for success, 0 for failure
*/
typedef int (*UserInputFunc) (void*, void*);


/*
generic vector struct
*/
typedef struct Vector Vector;

/**
 * @brief creates a new vector
 * @param[in] _initialSize - the initial capacity of the vector
 * @param[in] _extensionBblockSize - the number of elements to increase the vector when it fills its capacity
 * @return pointer to the new vector / NULL if failed
 *
 * @warning if _blockSize is 0 the vector will be of fixed size. 
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */
Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);

/**
 * @brief destroy the vector and free all space
 * @param[in] _vector - the vector to destroy
 * @param[in] _destroyElemFunction - pointer to function used to free allocated space to the elements in the vector
 * @return void
 */
void VectorDestroy(Vector** _vector, UserInputFunc _destroyElemFunction);

/**
 * @brief Add item to the end of the vector.
 * @param[in] _vector - the vector to add an item to
 * @param[in] _item - the new element(pointer to element) to add to the vector
 * @return success or error code
 * @retval ERR_OK - the item was added successfuly
 * @retval ERR_NOT_INITIALIZED - the vector was not initialized
 */
ADTErr VectorAdd(Vector *_vector,  void*  _item);

/**
 * @brief Delete item from the end of the vector.
 * @param[in] _vector - the vector to delete item from
 * @param[out] _item - pointer to a value to store the deleted item in.
 * @return success or error code
 * @retval ERR_OK - the item was deleted successfully
 * @retval ERR_NOT_INITIALIZED - the vector was not initialized
 * @retval ERR_UNDERFLOW - the vector was empty
 */
ADTErr VectorDelete(Vector *_vector,  void**  _item);

/**
 * @brief get item at index _index of the vector
 * @param[in] _vector - the vector to get the item from
 * @param[in] _index - the index of the item to get
 * @param[out] _item - pointer to the value to store the item in
 * @retval ERR_OK - the item was gotten successfully
 * @retval ERR_NOT_INITIALIZED - the vector was not initialized
 * @retval ERR_OVERFLOW - inputed index was larger than the number of elements
 */
ADTErr VectorGet(Vector *_vector, size_t _index, void**  _item);

/**
 * @brief set item at a specific index in the vector
 * @param[in] _vector - the vector to set item in
 * @param[in] _index - the index of the item to set
 * @param[in] _item - the item to set in the vector
 * @return success or error code
 * @retval ERR_OK - the item was set successfully
 * @retval ERR_NOT_INITIALIZED - the vector was not initialized
 * @retval ERR_OVERFLOW - inputed index was larger than the number of elements
 *
 * @warning the previous item at _index is not destroyed before the new one is set
 */
ADTErr VectorSet(Vector *_vector, size_t _index, void*  _item);

/**
 * @brief get the number of elements 
 * @param[in] _vector - the vector to get the number of elements of
 * @param[out] _numOfItems - pointer to the variable to store the number of lements in
 * @return success or error code
 * @retval ERR_OK - the operation was successful
 * @retval ERR_NOT_INITIALIZED - the vector was not initialized
 */
ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems);

/**
 * @brief operates a user defined function on each element int he array
 * @param[in] _vec - the vector to operate the function on
 * @param[in] _userFunc - the user defined function
 * @param[in] _input - input to add to the function
 * @return void
 */
int VecForEach(Vector* _vec, UserInputFunc _userFunc, void* _input);

/*  Unit-Test functions  */

/**
 * @brief print the vector
 * @input[in] _vector - vector to print
 * @input[in] _printFunc - function that prints a single element from its pointer
 * @return 1 - succedded. 0 - one of the function calls failed
 */
void VectorPrint(Vector *_vector, UserInputFunc _printFunc);



#endif /*_DYNAMIC_VECTOR_ */
