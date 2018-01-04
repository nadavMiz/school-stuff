#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <stddef.h>

typedef int(*SearchFunc)(int*, size_t, int);

/*
regular linear search. assumes all values were initialized
input:
	_array: the array to search
	_arrayLength: length of the array
	_search: value to search
return:
	1: value was found. 0:otherwise
*/
int LinearSearch(int* _array, size_t _arrayLength, int _search);

/*
preforms a linear search with adding search value at end and moving searched value backward to improve performence
assumes all values were initialized and that the array has an extra slot to put the searched item.
input:
	_array: the array to search (have to have an extra slot to put the searched item)
	_arrayLength: length of the array
	_search: value to search
return:
	1: value was found. 0:otherwise
*/
int ModifiedLinearSearch(int* _array, size_t _arrayLength, int _search);

/*
reforms a jump search. assumes all values were initialized.
input:
	_array: the array to search
	_arrayLength: length of the array
	_search: value to search
return:
	1: value was found. 0:otherwise
*/
int JumpSearch(int* array, size_t arrayLength, int _search);

/*binary search where you assume where the value is*/
int ProportionalSearch(int* array, size_t arrayLength, int _search);

#endif /* #ifndef __SEARCH_H__ */
