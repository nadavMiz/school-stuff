#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Sorts.h"

/*----------------build functions------------------*/

static Vector* BuildVector(int _capacity, int maxNum)
{
	Vector* vector;
	int i;
	int nextElem;
	srand(time(NULL));
	vector = VectorCreate(_capacity, 15);
	for(i = 0; i < _capacity; ++i)
	{
		nextElem = rand();
		if(maxNum > 0)
		{
			nextElem %= maxNum;
		}
		VectorAdd(vector,  nextElem);
	}
	return vector;
}

static Vector* VectorBuildSorted(int _capacity)
{
	Vector* vector;
	int i;
	vector = VectorCreate(_capacity, 15);
	for(i = 0; i < _capacity; ++i)
	{
		VectorAdd(vector,  i);
	}
	return vector;
}

static Vector* BuildReverseVector(int _capacity)
{
	Vector* vector;
	int i;
	vector = VectorCreate(_capacity, 15);
	for(i = _capacity; i > 0; --i)
	{
		VectorAdd(vector,  i);
	}
	return vector;
}

static Vector* BuildVectorSameElement(int _capacity)
{
	Vector* vector;
	int i;
	vector = VectorCreate(_capacity, 15);
	for(i = _capacity; i > 0; --i)
	{
		VectorAdd(vector,  1);
	}
	return vector;
}

/*-------------check functions---------------*/

static int isSorted(Vector* _vector)
{
	int next;
	int current;
	size_t capacity;
	int i;
	VectorItemsNum(_vector, &capacity);
	for(i = 1; i < capacity; ++i)
	{
		VectorGet(_vector, i, &current);
		VectorGet(_vector, i + 1, &next);
		if(current > next)
		{
			return 0;
		}
	}
	return 1;
}

static int isSortedDesc(Vector* _vector)
{
	int next;
	int current;
	size_t capacity;
	int i;
	VectorItemsNum(_vector, &capacity);
	for(i = 1; i < capacity; ++i)
	{
		VectorGet(_vector, i, &current);
		VectorGet(_vector, i + 1, &next);
		if(current < next)
		{
			return 0;
		}
	}
	return 1;
}

/*--------------------------------------*/

void TestBubbleSort(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildVector(_capacity, 0);
	BubbleSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED bubble sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED bubble sort\n");
	}
	
}

void TestBubbleSortSorted(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = VectorBuildSorted(_capacity);
	BubbleSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED bubble sort sorted\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED bubble sort sorted\n");
	}
	VectorDestroy(vector);
}

void TestBubbleSortWorst(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildReverseVector(_capacity);
	BubbleSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED bubble sort worst case\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED bubble sort worst case\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/

void TestShakeSort(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildVector(_capacity, 0);
	ShakeSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED shake sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED shake sort\n");
	}
	
}

void TestShakeSortSorted(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = VectorBuildSorted(_capacity);
	ShakeSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED shake sort sorted\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED shake sort sorted\n");
	}
	VectorDestroy(vector);
}

void TestShakeSortWorst(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildReverseVector(_capacity);
	ShakeSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED shake sort worst case\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED shake sort worst case\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/

void TestQuickSort(int _capacity)
{
	clock_t endClock;
	clock_t beginClock;
	Vector* vector;
	vector = BuildVector(_capacity, 0);
	beginClock = clock();
	QuickSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED quick sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED quick sort\n");
	}
	
}

void TestQuickSortBest(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = VectorBuildSorted(_capacity);
	QuickSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED quick sort best case\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED quick sort best case\n");
	}
	VectorDestroy(vector);
}

void TestQuickSortWorst(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildVectorSameElement(_capacity);
	QuickSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED quick sort worst\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED quick sort worst\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/

void TestQuickSortRec(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildVector(_capacity, 0);
	QuickSortRec(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED quick sort recursive\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED quick sort recursive\n");
	}
	
}

void TestQuickSortRecBest(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = VectorBuildSorted(_capacity);
	QuickSortRec(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED quick sort recursive best case\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED quick sort recursive best case\n");
	}
	VectorDestroy(vector);
}

void TestQuickSortRecWorst(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildVectorSameElement(_capacity);
	QuickSortRec(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED quick sort recursive worst case\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED quick sort recursive worst case\n");
	}
	VectorDestroy(vector);
}
/*--------------------------------------*/

void TestInsertionSort(int _capacity)
{
	Vector* vector;
	clock_t beginClock = clock();
	clock_t endClock;
	Compare compareFunc;
	compareFunc = GetCompare(0);
	vector = BuildVector(_capacity, 0);
	InsertionSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		endClock = clock();
		printf("PASSED Insertion sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED Insertion sort\n");
	}
	
}

void TestInsertionSortBest(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	Compare compareFunc;
	compareFunc = GetCompare(0);
	vector = VectorBuildSorted(_capacity);
	InsertionSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED Insertion sort sorted\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED Insertion sort sorted\n");
	}
	VectorDestroy(vector);
}

void TestInsertionSortWorst(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	Compare compareFunc;
	compareFunc = GetCompare(0);
	vector = BuildReverseVector(_capacity);
	InsertionSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED Insertion sort worst\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED Insertion sort worst\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/

void TestInsertionSortDesend(int _capacity)
{
	Vector* vector;
	clock_t beginClock = clock();
	clock_t endClock;
	Compare compareFunc;
	compareFunc = GetCompare(1);
	vector = BuildVector(_capacity, 0);
	InsertionSort(vector, compareFunc);
	if(isSortedDesc(vector))
	{
		endClock = clock();
		printf("PASSED Insertion sort descending\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED Insertion sort descending\n");
	}
	VectorDestroy(vector);
	
}

/*--------------------------------------*/

void TestShellSort(int _capacity)
{
	Vector* vector;
	clock_t beginClock = clock();
	clock_t endClock;
	Compare compareFunc;
	compareFunc = GetCompare(0);
	vector = BuildVector(_capacity, 0);
	ShellSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		endClock = clock();
		printf("PASSED shell sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED shell sort\n");
	}
	
}

void TestShellSortBest(int _capacity)
{
	clock_t beginClock;
	clock_t endClock;
	Vector* vector;
	Compare compareFunc;
	compareFunc = GetCompare(0);
	vector = VectorBuildSorted(_capacity);
	beginClock = clock();
	ShellSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED shell sort sorted\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED shell sort sorted\n");
	}
	VectorDestroy(vector);
}

void TestShellSortWorst(int _capacity)
{
	clock_t beginClock;
	clock_t endClock;
	Vector* vector;
	Compare compareFunc;
	beginClock = clock();
	compareFunc = GetCompare(0);
	vector = BuildReverseVector(_capacity);
	ShellSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED shell sort worst\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED shell sort worst\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/

void TestSelectionSort(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Vector* vector;
	vector = BuildVector(_capacity, 0);
	SelectionSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED selection sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED selection sort\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/

void TestMergeSort(int _capacity)
{
	clock_t beginClock = clock();
	clock_t endClock;
	Compare compareFunc;
	Vector* vector;
	compareFunc = GetCompare(0);
	vector = BuildVector(_capacity, 0);
	MergeSort(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED merge sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED merge sort\n");
	}
	VectorDestroy(vector);
}

void TestMergeSortRec(int _capacity)
{
	clock_t beginClock;
	clock_t endClock;
	Compare compareFunc;
	Vector* vector;
	compareFunc = GetCompare(0);
	vector = BuildVector(_capacity, 0);
	beginClock = clock();
	MergeSortRec(vector, compareFunc);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED merge recursive sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED merge recursive sort\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/


void TestCountSort(int _capacity)
{
	clock_t beginClock;
	clock_t endClock;
	Vector* vector;
	vector = BuildVector(_capacity, 5000);
	beginClock = clock();
	CountSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED count sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED count sort\n");
	}
	VectorDestroy(vector);
}

/*-----------------------------------------------------------*/

void TestRadixSort(int _capacity)
{
	clock_t beginClock;
	clock_t endClock;
	Vector* vector;
	vector = BuildVector(_capacity, 100000);
	beginClock = clock();
	RadixSort(vector);
	endClock = clock();
	if(isSorted(vector))
	{
		printf("PASSED radix sort\n");
		printf("time: %f\n", (double)(endClock - beginClock) / CLOCKS_PER_SEC);
	}
	else
	{
		printf("FAILED radix sort\n");
	}
	VectorDestroy(vector);
}

/*--------------------------------------*/
int main()	
{
	printf("-------best case times-----------");
	printf("\n1000 elements\n");
	TestBubbleSortSorted(1000);
	TestShakeSortSorted(1000);
	TestQuickSortBest(1000);
	TestQuickSortRecBest(1000);
	TestInsertionSortBest(1000);
	
	printf("\n10000 elements\n");
	TestBubbleSortSorted(10000);
	TestShakeSortSorted(10000);
	TestQuickSortBest(10000);
	TestQuickSortRecBest(10000);
	TestInsertionSortBest(10000);
	
	printf("\n50000 elements\n");
	TestBubbleSortSorted(50000);
	TestShakeSortSorted(50000);
	TestQuickSortBest(50000);
	TestQuickSortRecBest(50000);
	TestInsertionSortBest(50000);
	
	printf("\n10000 elements times\n");

	printf("-------typical case times--------");
	printf("\n1000 elements \n");
	TestBubbleSort(1000);
	TestShakeSort(1000);
	TestQuickSort(1000);
	TestInsertionSort(1000);
	TestQuickSortRec(1000);
	TestSelectionSort(1000);
	TestMergeSort(1000);
	TestMergeSortRec(1000);
	TestCountSort(1000);
	TestRadixSort(1000);
	
	printf("\n10000 elements \n");
	TestBubbleSort(10000);
	TestShakeSort(10000);
	TestQuickSort(10000);
	TestQuickSortRec(10000);
	TestInsertionSort(10000);
	TestSelectionSort(10000);
	TestMergeSort(10000);
	TestMergeSortRec(10000);
	TestCountSort(10000);
	TestRadixSort(10000);
	
	printf("\n50000 elements \n");
	TestBubbleSort(50000);
	TestShakeSort(50000);
	TestQuickSort(50000);
	TestQuickSortRec(50000);
	TestInsertionSort(50000);
	TestSelectionSort(50000);
	TestMergeSort(50000);
	TestMergeSortRec(50000);
	TestCountSort(50000);
	TestRadixSort(50000);
	
	printf("-------worst case times--------");
	printf("\n1000 elements \n");
	TestBubbleSortWorst(1000);
	TestShakeSortWorst(1000);
	TestQuickSortWorst(1000);
	TestQuickSortRecWorst(1000);
	TestInsertionSortWorst(1000);
	
	printf("\n10000 elements \n");
	TestBubbleSortWorst(10000);
	TestShakeSortWorst(10000);
	TestQuickSortWorst(10000);
	TestQuickSortRecWorst(10000);
	TestInsertionSortWorst(10000);
	
	printf("\n50000 elements \n");
	TestBubbleSortWorst(50000);
	TestShakeSortWorst(50000);
	TestInsertionSortWorst(50000);
	TestQuickSortWorst(50000);
	TestQuickSortRecWorst(50000);
	return 1;
}
