#ifndef __RECURSION_H__
#define __RECURSION_H__
#include "ADTErr.h"

#define CHESS_BOARD_SIZE 8 

/*
search for a number in an array
_array: the array to search
_arrayLength: the length of the array
_search: number to search
returns: pointer to first apearance of the number in the array
*/
int* RecursBinarySearch(int* _array, int _arrayLength, int _search);

/*
revese a string
_string: string to reverse
_dest: location to put the reversed string
*/
void RecusStringReverse(char* _string, char* _dest);

/*
solves the tower of hanoi problem
_numberOfDisks: number of disks in the problem
_isPrintBoard: boolean value: 1 = print the board after every step. 0 = don't
returns: OK if succeeded. else an error.
*/
ADTErr Hanoi(unsigned int _numberOfDisks, int _isPrintBoard);

/*
finds the maximum value in an array
_array: the array to search
_arrayLength: length of the array
_dest: destination to hold the result
returns: OK if succeeded. else an error.
*/
ADTErr FindMax(int* _array, unsigned int _arrayLength, int* _dest);

/*
finds a solution to the eight queen problem.
_queenNum: number of queens left to place
_isPrintBoard: boolean value: 1 = print the result 0: don't
returns: OK if succeeded. else an error.
*/
int Queens(int board[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE] ,unsigned int _queenNum, int _isPrintBoard);



#endif /* endif __RECURSION_H__ */
