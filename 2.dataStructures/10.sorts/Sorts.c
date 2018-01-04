#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "ADTErr.h"
#include "vector.h"
#include "Sorts.h"



/*-------------------compare functions------------------------*/
int compareBiggerThan(int a, int b)
{
	return (a > b);
}

int compareSmallerThan(int a, int b)
{
	return (b > a);
}

Compare GetCompare(size_t _option)
{
	switch(_option)
	{
		case 0:
			return compareBiggerThan;
			break;
		case 1:
			return compareSmallerThan;
			break;
	}
	return NULL;
}

/*--------------------Hash functions-----------------------------*/

static int getDigit(int num, void* digit)
{
	int divider = 1;
	int i;
	for(i = 0; i < (int)digit; ++i)
	{
		divider *= 10;
	}
	return ((int)num % (int)divider) / ((int)divider / 10);
}

static int SameIs(int num, void* dummy)
{
	return (int)num;
}

/*--------------------static functions-----------------------*/


static int swapMax(Vector* _vector, size_t _i, size_t _j)
{
	int a, b;
	VectorGet(_vector, _i, &a);
	VectorGet(_vector, _j, &b);
	if(a > b)
	{
		VectorSet(_vector, _i, b);
		VectorSet(_vector, _j, a);
		return 1;
	}
	return 0;
}

static void swapInVector(Vector* _vector, int _a, int _b, size_t _aIdx, size_t _bIdx)
{
	VectorSet(_vector, _aIdx, _b);
	VectorSet(_vector, _bIdx, _a);
}

static int IsVectorEmpty(Vector* _vector)
{
	size_t numItems;
	VectorItemsNum(_vector, &numItems);
	return (numItems == 0);
}

static void getLastItem(Vector* _vector, int* _item)
{
	size_t numItems;
	VectorItemsNum(_vector, &numItems);
	VectorGet(_vector, numItems, _item);
}

/*----------------------static quicksort functions-----------------------*/
/*set a pivot value to be the value in _start index and return its value*/
static int getPivot(Vector* _vector, size_t _start, size_t _end)
{
	int first, pivot;
	size_t pivotIdx;
	pivotIdx = (_start + _end) / 2;
	VectorGet(_vector, _start, &first);
	VectorGet(_vector, pivotIdx, &pivot);
	swapInVector(_vector, first, pivot, _start, pivotIdx);
	return pivot;
}

/*-----------------------------static mergeSort functions----------------------------*/

static void CopyFromHelperToVec(int* _array, Vector* _dest, size_t _begin, size_t _end)
{
	size_t i;
	size_t _destIdx = _begin;
	for(i = _begin; i < _end; ++i)
	{
		VectorSet(_dest, _destIdx, _array[i]);
		++_destIdx;
	}
}

static void CopyTailToArray(Vector* _vec, int* _array, size_t _leftBegin, size_t _leftEnd, size_t _runIdx)
{
	size_t i;
	for(i = _leftBegin; i < _leftEnd; ++i)
	{
		VectorGet(_vec, i, &_array[_runIdx]);
		++_runIdx;
	}
}

static size_t MergeCompare(Vector* _vec, int* _helper, size_t* _leftIdx, size_t* _rightIdx, size_t _end ,Compare _compareFunc)
{
	int left, right;
	size_t runIdx = *_leftIdx;
	size_t middleIdx = *_rightIdx;
	VectorGet(_vec, *_leftIdx, &left);
	VectorGet(_vec, *_rightIdx, &right);
	while(*_leftIdx < middleIdx && *_rightIdx < _end)
	{
		if(_compareFunc(right, left))
		{
			_helper[runIdx] = left;
			++(*_leftIdx);
			VectorGet(_vec, *_leftIdx, &left);
		}
		else
		{
			_helper[runIdx] = right;
			++(*_rightIdx);
			VectorGet(_vec, *_rightIdx, &right);
		}
		++runIdx;
	}
	return runIdx;
}

static void Merge(Vector* _vec, int* _helper, size_t _begin, size_t _end, size_t _middle, Compare _compareFunc)
{
	size_t leftIdx = _begin;
	size_t rightIdx = _middle;
	size_t runIdx;
	/* compare and sort the two arrays */
	runIdx = MergeCompare(_vec, _helper, &leftIdx, &rightIdx, _end , _compareFunc);
	/*copy the left tail to the head :] */
	if(leftIdx < _middle)
	{
		CopyTailToArray(_vec, _helper, leftIdx, _middle, runIdx);
		runIdx = _end;
	}
	/* copy the helper array back to vector */
	CopyFromHelperToVec(_helper, _vec, _begin, runIdx);
}


/*-------------------static count sort functions-------------------------*/

static int GetMaxVal(Vector* _vec, size_t _vecSize)
{
	size_t i;
	int maxVal, currentVal;
	VectorGet(_vec, 1, &maxVal);
	for(i = 2; i <= _vecSize; ++i)
	{
		VectorGet(_vec, i, &currentVal);
		if(currentVal > maxVal)
		{
			maxVal = currentVal;
		}
	}
	return maxVal;
}

void GetMinVal(Vector* _vec, int _start, int vecLength, int* _minVal, size_t* _minIdx)
{
	int i, currentVal;
	*_minIdx = _start;
	for(i = _start + 1; i <= vecLength; ++i)
	{
		VectorGet(_vec, i, &currentVal);
		if(currentVal < *_minVal)
		{
			*_minVal = currentVal;
			*_minIdx = i;
		}
	}
}

/*----------------------main functions------------------------*/

ADTErr BubbleSort(Vector* _vector)
{
	size_t i;
	size_t j;
	size_t vecSize;
	int isSorted = 1;
	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vector, &vecSize);
	if(vecSize <= 1)
	{
		return ERR_OK;
	}
	for(i = 0; i < vecSize; ++i)
	{
		for(j = 1; j < vecSize - i; ++j)
		{
			if(swapMax(_vector, j, j + 1))
			{
				isSorted = 0;
			}
		}
		if(isSorted)
		{
			break;
		}
		isSorted = 1;
	}
	return ERR_OK;
}

ADTErr ShakeSort(Vector* _vector)
{
	size_t i;
	size_t j = 1;
	size_t vecSize;
	int isSorted = 1;
	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vector, &vecSize);
	if(vecSize <= 1)
	{
		return ERR_OK;
	}
	for(i = 0; i < vecSize; ++i)
	{
		for(j = j; j < vecSize - i; ++j)
		{
			if(swapMax(_vector, j, j + 1))
			{
				isSorted = 0;
			}
		}
		if(isSorted)
		{
			break;
		}
		isSorted = 1;
		for(j = j; j > i + 1; --j)
		{
			if(swapMax(_vector, j - 1, j))
			{
				isSorted = 0;
			}
		}
		if(isSorted)
		{
			break;
		}
		isSorted = 1;
	}
	return ERR_OK;
}

/*----------------------------------------------------------------------*/

/**/
static size_t QuickSortStep(Vector* _vector, size_t _start, size_t _end)
{
	int pivotVal, currentVal, endVal, pivotIdx;
	pivotIdx = _start;
	pivotVal = getPivot(_vector, _start, _end);
	VectorGet(_vector, _end, &endVal);
	while(_start < _end)
	{
		++_start;
		VectorGet(_vector, _start, &currentVal);
		if(currentVal > pivotVal)
		{
			while(_start < _end && endVal > pivotVal)
			{	
				--_end;
				VectorGet(_vector, _end, &endVal);
			}
			swapInVector(_vector, currentVal, endVal, _start, _end);
			--_end;
			VectorGet(_vector, _end, &endVal);
		}
	}
	swapInVector(_vector, pivotVal, endVal, pivotIdx, _end);
	return _end;
}

static void QuickSortHelper(Vector* _vector, int _start, int _end)
{
	int middle;
	if(_end - _start < 1)
	{
		return;
	}
	middle = QuickSortStep(_vector, (size_t)_start, (size_t)_end);
	QuickSortHelper(_vector, middle + 1, _end);
	QuickSortHelper(_vector, _start, middle - 1);
}

ADTErr QuickSortRec(Vector* _vector)
{
	size_t lastIdx;
	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vector, &lastIdx);
	QuickSortHelper(_vector, 1, lastIdx);
	return ERR_OK;
}

ADTErr QuickSort(Vector* _vector)
{
	size_t end;
	int start = 1;
	Vector* endPoints;
	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vector, &end);
	++end;
	endPoints = VectorCreate(end/2, 15);
	VectorAdd(endPoints, end);
	while(!IsVectorEmpty(endPoints))
	{
		getLastItem(endPoints, (int*)&end);
		if(end - start <= 1)
		{
			VectorDelete(endPoints, &start);
			++start;
			continue;
		}
		VectorAdd(endPoints, QuickSortStep(_vector, start, end - 1));
	}
	return ERR_OK;
}

/*----------------------------------------------------------------*/

static void Insertion(Vector* _vec, size_t _start, size_t _step, Compare _compareFunc)
{
	size_t vecLength, i, j;
	int currentNum, preNum;
	
	VectorItemsNum(_vec, &vecLength);
	for(i = _start + _step; i <= vecLength; i += _step)
	{
		VectorGet(_vec, i, &currentNum);
		for(j = i - _step; j >= _start; j -= _step)
		{
			VectorGet(_vec, j, &preNum);
			if(_compareFunc(currentNum, preNum))
			{
				break;
			}
			swapInVector(_vec, preNum, currentNum, j, j + _step);
		}
	}
}

ADTErr InsertionSort(Vector* _vec, Compare _compareFunc)
{
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	Insertion(_vec, 1, 1, _compareFunc);
	return ERR_OK;
}


/*----------------------------------------------------------------------*/

ADTErr SelectionSort(Vector* _vec)
{
	size_t vecLength, i, minIdx;
	int minVal, currentVal;
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vec, &vecLength);
	for(i = 1; i <= vecLength; ++i)
	{
		VectorGet(_vec, i, &currentVal);
		minVal = currentVal;
		GetMinVal(_vec, i, vecLength, &minVal, &minIdx);
		if(currentVal > minVal)
		{
			swapInVector(_vec, currentVal, minVal, i, minIdx);
		}
	}
	return ERR_OK;
}

/*-----------------------------------------------------------------------------*/

ADTErr ShellSort(Vector* _vec, Compare _compareFunc) /*TODO change shell sort*/
{
	size_t interval, start, vecLength;
	
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vec, &vecLength);
	for(interval = vecLength / 2; interval > 0 ; interval /= 2)
	{
		for(start = 1; start <= interval; ++start)
		{
			Insertion(_vec, start, interval, _compareFunc);
		}
	}
	return ERR_OK;
}

/*----------------------------------------------------------------------------------*/

static void MergeRecHelp(Vector* _vec, int* _helper, size_t _begin, size_t _end, Compare _compareFunc)
{
	size_t middle;
	if(_end - _begin < 2)
	{
		return;
	}
	middle = (_begin + _end) /2;
	MergeRecHelp(_vec, _helper, _begin, middle, _compareFunc);
	MergeRecHelp(_vec, _helper, middle, _end, _compareFunc);
	Merge(_vec, _helper, _begin, _end, middle, _compareFunc);
}

ADTErr MergeSortRec(Vector* _vec, Compare _compareFunc)
{
	int* helperArray;
	size_t vecLength;
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vec, &vecLength);
	helperArray = malloc((vecLength + 1) * sizeof(int));
	if(NULL == helperArray)
	{
		return ERR_ALLOCATION_FAILED;
	}
	MergeRecHelp(_vec, helperArray, 1, vecLength + 1, _compareFunc);
	free(helperArray);
	return ERR_OK;
}

/*------------------------------------------------------------------*/

void MergePartition(Vector* _vec, int* _helper, Compare _compareFunc)
{
	size_t step, i, lastMiddle, end;
	VectorItemsNum(_vec, &end);
	lastMiddle = end;
	for(step = 2; step < end; step *= 2)
	{
		for(i = 1; i <= end - step; i += step)
		{
			Merge(_vec, _helper, i, i + step, (2*i + step) / 2, _compareFunc);
		}
		/* if there is a last group merge it using the begginning of the the previous last group as the middle*/
		if(i < lastMiddle)
		{
			Merge(_vec, _helper, i, end + 1, lastMiddle, _compareFunc);
			lastMiddle = i;
		}
	}
	/* do the last step ( merge the entire vector ) */
	Merge(_vec, _helper, 1, end + 1, lastMiddle, _compareFunc);
}

ADTErr MergeSort(Vector* _vec, Compare _compareFunc)
{
	int* helperArray;
	size_t vecLength;
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_vec, &vecLength);
	helperArray = malloc((vecLength + 1) * sizeof(int));
	if(NULL == helperArray)
	{
		return ERR_ALLOCATION_FAILED;
	}
	MergePartition(_vec, helperArray, _compareFunc);
	free(helperArray);
	return ERR_OK;
}

/*------------------------------------------------------------------------*/


/*counts the numer of instences of each number and puts them in _counts array*/
static void CountSortCounting(Vector* _vec, size_t* _counts, size_t _vecSize, GetKey _getKey, void* _input)
{
	int elem;
	size_t i;
	for(i = 1; i <= _vecSize; ++i)
	{
		VectorGet(_vec, i, &elem);
		++_counts[_getKey(elem, _input)];
	}
}

/* sum the counts so we'd know the index of each element in count */
static void AddCounts( size_t* _counts, size_t _countSize)
{
	size_t i;
	for(i = 1; i < _countSize; ++i)
	{
		_counts[i] += _counts[i - 1];
	}
}

/*sort the vector into _helper array*/
static void SortToHelper(Vector* _vec, int* _helper, size_t* _counts, size_t _vecSize, GetKey _getKey, void* _input)
{
	size_t i;
	int elem;
	for(i = _vecSize; i > 0; --i)
	{
		VectorGet(_vec, i, &elem);
		_helper[_counts[_getKey(elem, _input)]] = elem;
		--_counts[_getKey(elem, _input)];
	}
}

/*main function that does the count sort*/
static void CountSortMain(Vector* _vec, int* _helper, size_t* _counts, size_t _countSize 
							,size_t _vecSize, GetKey _getKey ,void* _input)
{
	CountSortCounting(_vec, _counts, _vecSize, _getKey, _input);
	AddCounts(_counts, _countSize);
	SortToHelper(_vec, _helper, _counts, _vecSize, _getKey ,_input);
	CopyFromHelperToVec(_helper, _vec, 1, _vecSize + 1);
}

static int GetCountSize(Vector* _vec, GetKey _getKey, void* _input)
{
	int maxNum;
	size_t vecSize;
	VectorItemsNum(_vec, &vecSize);
	if(getDigit == _getKey)
	{
		return 10;
	}
	else
	{
		maxNum = GetMaxVal(_vec, vecSize);
		return maxNum + 1;
	}
}

static ADTErr CountSortForReal(Vector* _vec, GetKey _getKey, void* _input)
{
	int* helper;
	size_t* counts;
	size_t countSize;
	size_t vecSize;
	
	VectorItemsNum(_vec, &vecSize);
	countSize = GetCountSize(_vec, _getKey, _input);
	
	counts = calloc(countSize , sizeof(size_t));
	if(NULL == counts)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	helper = calloc(vecSize + 1, sizeof(int));
	if(NULL == helper)
	{
		free(counts);
		return ERR_ALLOCATION_FAILED;
	}
	CountSortMain(_vec, helper, counts, countSize, vecSize, _getKey, _input);
	free(helper);
	free(counts);
	return ERR_OK;
}

ADTErr CountSort(Vector* _vec)
{
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	return CountSortForReal(_vec, SameIs, 0);
}

/*-----------------------------------------------------------------------*/

static int GetNumDigits(Vector* _vec)
{
	size_t vecSize;
	int divider = 10;
	int numDigits = 1;
	int maxVal;
	VectorItemsNum(_vec, &vecSize);
	maxVal = GetMaxVal(_vec, vecSize);
	while(0 < maxVal / divider)
	{
		divider *= 10;
		++numDigits;
	}
	return numDigits;
}

ADTErr RadixSort(Vector* _vec)
{
	int numDigits;
	int digit;
	ADTErr error;
	
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	numDigits = GetNumDigits(_vec);
	
	for(digit = 1; digit <= numDigits; ++digit)
	{
		error = CountSortForReal(_vec, getDigit, (void*)digit);
		if(error != ERR_OK)
		{
			return error;
		}
	}
	
	return ERR_OK;
}

