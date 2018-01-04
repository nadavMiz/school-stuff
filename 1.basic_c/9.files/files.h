#ifndef FILES_H
#define FILES_H
#include <stdio.h>

/* struct containing a word and the nunber of accurences */
typedef struct{

	char word[20];
	int count;

} word_t;

/* struct of a dynamic array */
typedef struct{
	int capacity;
	int noe; // number of elements
	word_t** array;
} DynamicArray;

/*
prints the last N lines of file myfile
param myfile: file to read
param N: number of lines to print
return 0:failed 1: succeeded.
*/
int findLastN(FILE* myfile, int N);
/*
prints all the letters in my myfile and their number of accurences
param myfile: file to check
return 0:failed 1: succeeded.
*/
int lettersFrequency(FILE* myfile);
/*
prints all the words in myfile and the number of their accurences.
param myfile: file to check
return 0:failed 1: succeeded.
*/
int wordFrequency(FILE* myfile);

#endif
