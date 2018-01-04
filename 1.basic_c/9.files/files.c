#include <stdio.h>
#include "files.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define LINE_LENGTH 360
#define LOWER_OFFSET 71
#define UPPER_OFFSET 65
#define LETTERS_IN_THE_ALPHA 26
#define INITIAL_CAPACITY 10

/*********************helper functions***************************/
int increaseCapacity(DynamicArray* DA){
	if(!DA) return 0;
	word_t** pointer = realloc((*DA).array, (*DA).capacity * 2 * sizeof(word_t*));
	// if the realocation of memmory was unsuccessful return without doing anything.
	if(!pointer) {
		return 0;
	}
	// if the realocation was succesful double the arrays capacity and set the new array pointer
	(*DA).array = pointer;
	(*DA).capacity = (*DA).capacity * 2;
	return 1;
}

int insert(DynamicArray* DA, char* word) {
	if(!DA) return 0;
	// if the array reached its maximum capicity realocate more space
	if((*DA).noe == (*DA).capacity){
		int increaseSuccess = increaseCapacity(DA);
		//if the capacity increase did not work return 0
		if(increaseSuccess == 0) return 0;
	}

	// enter the element to the array.
	(*DA).array[(*DA).noe] = malloc(sizeof(word_t));
	strcpy((*(*DA).array[(*DA).noe]).word, word);
	(*(*DA).array[(*DA).noe]).count = 1;
	++((*DA).noe);
	return 1;
}

DynamicArray* create(int capacity){
	if (capacity <= 0) capacity = 1;
	//create the dynamic arrays pointer
	DynamicArray* dynamicArrayPointer;
	dynamicArrayPointer = malloc(sizeof(DynamicArray));
	if(!dynamicArrayPointer) return NULL;

	// set the DAs capacity and index
	(*dynamicArrayPointer).capacity = capacity;
	(*dynamicArrayPointer).noe = 0;

	// create the DAs array
	word_t** array = malloc(capacity * sizeof(word_t*));
	if(!array){ 
		free(dynamicArrayPointer);
		return NULL;
	}
	(*dynamicArrayPointer).array = array;
	return dynamicArrayPointer;
}


void destroy(DynamicArray* DA){
	if(DA){
		if((*DA).array){
			for(int i = 0; i < (*DA).noe; ++i){
				free((*DA).array[i]);
			}
			free((*DA).array);
		}
		free(DA);
	}
}

word_t* find(DynamicArray* DA, char* element){
	if(!DA) return NULL;
	for(int i = 0; i < (*DA).noe; ++i){
		if(strcmp((*(*DA).array[i]).word, element) == 0){
			return (*DA).array[i];
		}
	}
	return NULL;
}

/**********************main functions*******************/
int findLastN(FILE* myfile, int n){
	char line[LINE_LENGTH];
	n = n + 1;
	long int* startLines = malloc(sizeof(int) *(n));
	if(!startLines) return 0;
	int i = 0;
	/* find the location of the last n lines */
	while(!feof(myfile)){
		startLines[i%n] = ftell(myfile);
		fgets(line, LINE_LENGTH, myfile);
		++i;
	}
	/* print the lines */
	fseek(myfile, startLines[(i)%n], 0);
	for(int j = 0; j<(n-1); ++j){
		fgets(line, LINE_LENGTH, myfile);
		printf("%s", line);
	}
	free(startLines);
	fseek(myfile, 0, 0);
}

int lettersFrequency(FILE* myfile){
	if(!myfile) return 0;
	char line[LINE_LENGTH];
	char nextChar = 'a';
	int lineIdx;
	int lettersFreq[2*LETTERS_IN_THE_ALPHA] = {0};
	fgets(line, LINE_LENGTH, myfile);
	/* get the letters frequencies */
	while(!feof(myfile)){
		lineIdx = 0;
		while(nextChar != '\0'){
			nextChar = line[lineIdx];
			if(islower(nextChar)){
				++lettersFreq[nextChar - LOWER_OFFSET];
			}
			if(isupper(nextChar)){
				++lettersFreq[nextChar - UPPER_OFFSET];
			}
			++lineIdx;
		}
		nextChar = 'a';
		fgets(line, LINE_LENGTH, myfile);
	}
	/*print the letter frequencies*/
	for(int i = 0; i < LETTERS_IN_THE_ALPHA; ++i){
		if(lettersFreq[i]){
			printf("%c : %d\n", i + UPPER_OFFSET ,lettersFreq[i]);
		}
	}
	for(int i = LETTERS_IN_THE_ALPHA; i < 2*LETTERS_IN_THE_ALPHA; ++i){
		if(lettersFreq[i]){
			printf("%c : %d\n", i + LOWER_OFFSET ,lettersFreq[i]);
		}
	}
	fseek(myfile, 0, 0);
	return 1;
}


int wordFrequency(FILE* myfile){
	if(!myfile) return 0;
	char line[LINE_LENGTH];
	word_t* word;
	char* token;
	char delimiters[28] = "_{}[]|!@#$%^&*;:(`)?-.,\" \t\n";
	int i;
	DynamicArray* words = create(INITIAL_CAPACITY);
	fgets(line, LINE_LENGTH, myfile);
	/* get the word frequencies */
	while(!feof(myfile)){
		/* get all the words in line */
		token = strtok(line, delimiters);
		while(token != NULL){
			/* if word already exist increase its count */
			word = find(words, token);
			if(word){
				++(*word).count;
			}
			/* if it is a new word insert it to the array */
			else{
					insert(words, token);
				}
			token = strtok(NULL, delimiters);
		}
		fgets(line, LINE_LENGTH, myfile);
	}
	/* print the word count  */
	for(int i = 0; i < (*words).noe; ++i){
		word = (*words).array[i];
		printf("%s : %d \n", (*word).word, (*word).count);
	}
	destroy(words);
	fseek(myfile, 0, 0);
	return 1;
}




