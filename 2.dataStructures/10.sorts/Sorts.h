#ifndef __EX_SORT_H__
#define __EX_SORT_H__

#include "ADTErr.h"
#include "vector.h"
/*
templet for a function that desides if to swap the elements or not.
*/
typedef int(*Compare)(int, int);

typedef int(*GetKey)(int, void*);

/*
helper function to get various compare functions
input _option:
	0) return (a > b)
	1) return (a < b)
*/
Compare GetCompare(size_t _option);

/*
sort a vector using bubble sort  algorithm
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr BubbleSort(Vector* _vector);

/*
sort a vector using the shakesort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr ShakeSort(Vector* _vector);

/*
sort a vector using the iterative quicksort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr QuickSort(Vector* _vector);

/*
sort a vector using the recursive quicksort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr QuickSortRec(Vector* _vector);


/*
sort a vector using the insertion sort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr InsertionSort(Vector* _vec, Compare _compareFunc);

/*
sort a vector using the shell sort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr ShellSort(Vector* _vec, Compare _compareFunc);

/*
sort a vector using the selection sort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
*/
ADTErr SelectionSort(Vector* _vec);

/*
sort a vector using the merge sort recursive algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
	ERR_ALLOCATION_FAILED: helper memmory allocation failed.
*/
ADTErr MergeSortRec(Vector* _vec, Compare _compareFunc);

/*
sort a vector using the merge sort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
	ERR_ALLOCATION_FAILED: helper memmory allocation failed.
*/
ADTErr MergeSort(Vector* _vec, Compare _compareFunc);

/*
sort a vector using the count sort algorithm.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
	ERR_ALLOCATION_FAILED: helper memmory allocation failed.
*/
ADTErr CountSort(Vector* _vec);

/*
sort a vector using the radix sort algorithm using decimal base.
input:
	_vector: vector to sort.
return:
	ERR_OK: sorting was succesful
	ERR_NOT_INITIALIZED: vector was not initialized
	ERR_ALLOCATION_FAILED: helper memmory allocation failed.
*/
ADTErr RadixSort(Vector* _vec);

#endif /*ifndef __EX_SORT_H__*/
