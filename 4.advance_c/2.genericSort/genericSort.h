#ifndef __GENERIC_SORT_H__
#define __GENERIC_SORT_H__

#include <stddef.h>
#include "ADTErr.h"

/*
templet for a function that desides if to swap the elements or not.
*/
typedef int (*CompareFunc)(const void*, const void*);


/*
sorts a generic array using bubble sort algorithm
allocates space with the size of _elemSize for a temporery variable to swap two items
input:
	_data: array to sort (can contain any type)
	_arrLength: number of items in the array
	_elemSize: size of the elements in the array
	_compareFunc: boolean function that compares teo elements in the array.
returns:
	ERR_OK: the sorting was successful
	ERR_NOT_INITIALIZED: the array or compareFunction was not initialized
	ERR_INVALID_INPUT: _elemSize is 0
	ERR_ALLOCATION_FAILED: alocation of the temporary swap var failed
*/
ADTErr GenericBubbleSort(void* _data, size_t _arrLength, size_t _elemSize ,CompareFunc _compareFunc);

#endif /* ifndef __GENERIC_SORT_H__ */
