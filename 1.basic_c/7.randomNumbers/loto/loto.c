#include "loto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 49

int in(int searchNum, int* array, int arrayLength){
	for(int i = 0; i < arrayLength; ++i){
		if(array[i] == searchNum) return 1;
	}
	return 0;
}

int getLotoNumbers(int* lotoNumbers,unsigned int numLotoNums){
	srand(time(NULL));
	/* generate random loto numbers */
	int nextNum;
	int repeatNumber;
	for(int i = 0; i < numLotoNums; i++){
		do{
			repeatNumber = 0;
			// generate a new number
			nextNum = rand() % MAXNUM + 1;
			// check if the number repeats a previous one. if it does generate a new one
			if(in(nextNum, lotoNumbers, i)) repeatNumber = 1;
		} while(repeatNumber);
	lotoNumbers[i] = nextNum;
	}
	return 1;
}

void printTheLoto(int* lotoNumbers, unsigned int numLotoNums){

	/* print the loto ;>) */
	int i;
	int number = 0;
	int tens = MAXNUM / 10;
	int ones = MAXNUM % 10;
	printf("  1 2 3 4 5 6 7 8 9 10 \n");
	for(i = 0; i < tens; ++i){
		printf("%d ", i);
		for(int j = 0; j < 10; ++j){
			++number; 
			if(in(number, lotoNumbers, numLotoNums)) printf("+ ");
			else printf("- ");
			}
		printf("\n");
	}
	printf("%d ", i);
	for(int i = 0; i < ones; ++i){
		++number; 
		if(in(number, lotoNumbers, numLotoNums)) printf("+ ");
		else printf("- ");
	}
printf("\n");
}



