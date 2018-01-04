#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "recursion.h"
/****************************board & column structs**************************/

typedef struct
{
	int m_noe;
	int m_capacity;
	int* m_array;
} Column;

typedef struct
{
	unsigned int m_diskNum;
	Column* m_origin;
	Column* m_dest;
	Column* m_helper;
	
} HanoiBoard;


Column* createCol(int _capacity)
{
	Column*  myCol = malloc(sizeof(Column));
	if(NULL == myCol)
	{
		return NULL;
	}
	myCol->m_array = malloc(_capacity * sizeof(int));
	if(NULL == myCol->m_array)
	{
		free(myCol);
		return NULL;
	}
	myCol->m_capacity = _capacity;
	myCol->m_noe = 0;
	return myCol;
}

void destroyCol(Column* _myCol)
{
	if(NULL != _myCol)
	{
		if(NULL != _myCol->m_array)
		{
			free(_myCol->m_array);
		}
		free(_myCol);
	}
}

ADTErr pushCol(Column* _myCol, int _elem)
{
	if(_myCol->m_noe == _myCol->m_capacity)
	{
		return ERR_OVERFLOW;
	}
	_myCol->m_array[_myCol->m_noe] = _elem;
	++_myCol->m_noe;
	return ERR_OK;
}

ADTErr popCol(Column* _myCol, int* _dest)
{
	if(_myCol->m_noe == 0)
	{
		return ERR_UNDERFLOW;
	}
	/* get the last item and change it to 0 */
	(*_dest) = _myCol->m_array[_myCol->m_noe - 1];
	_myCol->m_array[_myCol->m_noe - 1] = 0;
	--_myCol->m_noe;
	return ERR_OK;
}

int getCol(Column* _myCol, int _index)
{
	return _myCol->m_array[_index];
}

HanoiBoard* createHanoiBoard(unsigned int _numberOfDisks)
{
	int i;
	HanoiBoard* myBoard = malloc(sizeof(HanoiBoard));
	if(NULL != myBoard)
	{
		myBoard->m_origin = createCol(_numberOfDisks);
		if(NULL != myBoard->m_origin)
		{
			myBoard->m_dest = createCol(_numberOfDisks);
			if(NULL != myBoard->m_dest)
			{
				myBoard->m_helper = createCol(_numberOfDisks);
				if(NULL != myBoard->m_helper)
				{
					for(i = _numberOfDisks; i >0; --i)
					{
						pushCol(myBoard->m_origin, i);
					}
					myBoard->m_diskNum = _numberOfDisks;
					return myBoard;
				}
				destroyCol(myBoard->m_dest);
			}
			destroyCol(myBoard->m_origin);
		}
		free(myBoard);
	}
	return NULL;
}

void DestroyHanoiBoard(HanoiBoard* _board)
{
	if(NULL != _board)
	{
		destroyCol(_board->m_origin);
		destroyCol(_board->m_dest);
		destroyCol(_board->m_helper);
		free(_board);
	}
}

void printHanoi(HanoiBoard* _board)
{
	int i;
	for(i = _board->m_diskNum - 1; i >= 0; --i)
	{	
		printf("|%d| |%d| |%d|\n", getCol(_board->m_origin, i), getCol(_board->m_helper, i), getCol(_board->m_dest, i));
	}
	printf("-------------------\n");
}

ADTErr CheckHanoi(HanoiBoard* _board)
{
	int i;
	ADTErr error = ERR_OK;
	for(i = 0; i < _board->m_diskNum; ++i)
	{
		if(getCol(_board->m_dest, i) != _board->m_diskNum - i)
		{
			error = ERR_GENERAL;
		}
	}
	if(_board->m_origin->m_noe != 0 || _board->m_helper->m_noe != 0)
	{
		error = ERR_GENERAL;
	}
	return error;
}

/***********************main functions***************************/
int* RecursBinarySearch(int* _array, int _arrayLength, int _search)
{
	int* result;
	int* middle;
	int* end;
	if(_arrayLength == 0)
	{
		return NULL;
	}
	/* stop condition*/
	if (_arrayLength == 1)
	{
		if (_array[0] == _search)
		{
			return _array;
		}
		else
		{
			return NULL;
		}
	}
	/* binary search */
	end = _array + _arrayLength - 1;
	middle = _array + (_arrayLength - 1) / 2;
	if(*middle == _search)
	{
		return middle;
	}
	else if( _search < *middle)
	{
		_arrayLength =  middle - _array + 1;
	}
	else
	{
		_array = middle + 1;
		_arrayLength = end - _array + 1;
	}
	result = RecursBinarySearch(_array, _arrayLength, _search);
	return result;
}

/*****************************************************/
void RecusStringReverseHelper(char* _string, char* _dest, int _Lastidx)
{
	if(_Lastidx < 0)
	{
		return;
	}
	_dest[0] = _string[_Lastidx];
	RecusStringReverseHelper(_string, _dest + 1, _Lastidx - 1);
}

void RecusStringReverse(char* _string, char* _dest)
{
	int lastIdx;
	lastIdx = strlen(_string);
	_dest[lastIdx] = '\0';
	RecusStringReverseHelper(_string, _dest, lastIdx - 1);
}
/*******************************************************/


void HanoiHelper(unsigned int _numberOfDisks, Column* _origin, Column* _dest, Column* _helper, HanoiBoard* _board, int _isPrintBoard)
{
	int moveDisk;
	if(_numberOfDisks > 0)
	{
		HanoiHelper(_numberOfDisks - 1, _origin, _helper, _dest, _board, _isPrintBoard);
		popCol(_origin, &moveDisk);
		pushCol(_dest, moveDisk);
		if(_isPrintBoard)
		{
			printHanoi(_board);
		}
		HanoiHelper(_numberOfDisks - 1, _helper, _dest, _origin, _board, _isPrintBoard);
		
	}
}

ADTErr Hanoi(unsigned int _numberOfDisks, int _isPrintBoard)
{
	ADTErr error;
	HanoiBoard* board = createHanoiBoard(_numberOfDisks);
	if(!board)
	{
		return ERR_ALLOCATION_FAILED;
	}
	if(_isPrintBoard)
	{
		printHanoi(board);
	}
	HanoiHelper(_numberOfDisks, board->m_origin, board->m_dest, board->m_helper, board, _isPrintBoard);
	error = CheckHanoi(board);
	DestroyHanoiBoard(board);
	return error;
	
}

/**************************************************************************/

void FindMaxHelper(int* _array, unsigned int _arrayLength, int* _dest)
{
	if (0 == _arrayLength)
	{
		return;
	}
	if(_array[0] > *_dest)
	{
		*_dest = _array[0];
	}
	FindMaxHelper(_array + 1, _arrayLength - 1, _dest);
}

ADTErr FindMax(int* _array, unsigned int _arrayLength, int* _dest)
{
	if(!_array || !_dest)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_arrayLength == 0)
	{
		return ERR_EMPTY_ARRAY;
	}
	*_dest = _array[0];
	FindMaxHelper(_array, _arrayLength, _dest);
	return ERR_OK;
}

/**************************************************************************/
int myMax(int a, int b)
{
	return ((a) > (b) ? (a) : (b));
}

int myMin(int a, int b)
{
	return ((a) < (b) ? (a) : (b));
}

void printQueens(int _board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE])
{
	char isQueen = '0';
	int i;
	int j;
	for(i = 0; i < CHESS_BOARD_SIZE; ++i)
	{
		for(j = 0; j < CHESS_BOARD_SIZE; ++j)
		{
			(_board[i][j] < 0) ? (isQueen = 'X'): (isQueen = '0');
			printf("%c ", isQueen);
		}
		printf("\n");
	}
}

/* _toErace = 1: erase queen 0: place queen*/
void MarkQueen(int _board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], int _queenRow, int _queenCol, int _queenNum, int _toErace)
{
	int row;
	int col;
	int queenMark = 1;
	_queenNum = (_queenNum+1)*(-1);
	if(_toErace)
	{
		_queenNum = 0;
		queenMark *= -1;
	}
	/* mark verticaly */
	for(row = 0; row < CHESS_BOARD_SIZE; ++row)
	{
		_board[row][_queenCol] += queenMark;
	}
	/* mark horizontaly */
	for(col = 0; col < CHESS_BOARD_SIZE; ++col)
	{
		_board[_queenRow][col] += queenMark;
	}
	/* mark to right diaganoly */
	col = myMax(0, _queenCol - _queenRow);
	row = myMax(0, _queenRow - _queenCol);
	while(col < CHESS_BOARD_SIZE && row < CHESS_BOARD_SIZE)
	{
		_board[row][col] += queenMark;
		++row;
		++col;
	}
	/* mark to left diaganoly */
	col = myMin(CHESS_BOARD_SIZE, _queenCol + _queenRow);
	row = myMax(0, _queenRow - (CHESS_BOARD_SIZE - _queenCol));
	while(col > 0 && row < CHESS_BOARD_SIZE)
	{
		_board[row][col] += queenMark;
		++row;
		--col;
	}
	/* mark the queen itself */
	_board[_queenRow][_queenCol] = _queenNum;
}

int Queens(int _board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE] ,unsigned int _queenNum, int _isPrintBoard)
{
	int row;
	int col;
	int isSolved = 0;
	if (_queenNum == 0)
	{
		if(_isPrintBoard)
		{
			printQueens(_board);
		}
		return 1; 
	}
	for(row = 0; row < CHESS_BOARD_SIZE; ++row)
	{
		for (col = 0; col < CHESS_BOARD_SIZE; ++col)
		{
			if(_board[row][col] == 0)
			{
				MarkQueen(_board, row, col,  8 - _queenNum, 0);
				isSolved = Queens(_board , _queenNum - 1, _isPrintBoard);
				if(1 == isSolved)
				{
					return isSolved;
				}
				else
				{
					MarkQueen(_board, row, col,  8 - _queenNum, 1);
				}
			}
		}
	}
	return isSolved;
}



