#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursion2.h"

#define maxStringLength 128

static void printTriangleHelper(unsigned int _numStars, unsigned int _numBlacks)
{
	int i;
	for(i = 0; i < _numBlacks; ++i)
	{
		printf(" ");
	}
	for(i = 0; i < _numStars; ++i)
	{
		printf("*");
	}
	printf("\n");
	if(_numBlacks > 0)
	{
		printTriangleHelper(_numStars + 2, _numBlacks - 1);
	}
}

void printTriangle(unsigned int _numStars)
{
	if(_numStars % 2 == 0)
	{
		printTriangleHelper( 2, _numStars / 2 - 1);
	}
	else
	{
		printTriangleHelper( 1, _numStars / 2);
	}
}

/***************************************************/
static void printReverseTriangleHelper(int _numStars, int _numBlanks)
{
	int i;
	if(_numStars <= 0)
	{
		return;
	}
	for(i = 0; i < _numBlanks; ++i )
	{
		printf(" ");
	}
	for(i = 0; i < _numStars; ++i)
	{
		printf("*");
	}
	printf("\n");
	printReverseTriangleHelper(_numStars - 2, _numBlanks + 1);
}

void printReverseTriangle(unsigned int _numStars)
{
	printReverseTriangleHelper(_numStars, 0);
}

/*****************************************************/



void multypecationTable(unsigned int _row, unsigned int _column, unsigned int _base)
{
	printf("%d\t ", _row * _column);
	if(_column == _base && _row == _base)
	{
		return;
	}
	if(_column == _base)
	{
		printf("\n");
		multypecationTable(_row + 1, 1, _base);
	}
	else
	{
		multypecationTable(_row, _column + 1, _base);
	}
}

/******************************************************/

double average(int* array, int _arrayLength)
{
	if(_arrayLength > 1)
	{
		return (array[0] + average(array + 1, _arrayLength - 1)) / 2;
	}
	return array[0];
}

/******************************************************/

void swap(char* a, char* b)
{
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void printPermutations(char* string, unsigned int _lastIdx, unsigned int _currentIdx)
{
	if(0 == _lastIdx)
	{
		printf("%s\n", string);
		return;
	}
	if(_currentIdx > _lastIdx)
	{
		return;
	}
	swap(&string[_currentIdx], &string[_lastIdx]);
	printPermutations(string, _lastIdx - 1, 0);
	swap(&string[_currentIdx], &string[_lastIdx]);
	printPermutations(string, _lastIdx, _currentIdx + 1);
}

/***********************************************/

void StupidPrintPermutations(const char* string, int permLength)
{
	if(permLength == 1)
	{
		
	}
}
