#include "DynamicArray.h"
#include <stdlib.h>

int insert(struct DynamicArray* dynamicArray, int element) {
	int* pointer = (*dynamicArray).array;
	// if the array reached its maximum capicity realocate more space (twice more space)
	if((*dynamicArray).index == (*dynamicArray).capacity){
		pointer = realloc((*dynamicArray).array, (*dynamicArray).capacity * 2 * sizeof(int));
		// if the realocation of memmory was unsuccessful return without doing anything.
		if(!pointer) {
			return 0;
		}
		else{
			// if the realocation was succesful double the arrays capacity
			(*dynamicArray).capacity = (*dynamicArray).capacity * 2;
		}
	}
	// enter the element to the array and update the arrays location.
	pointer[(*dynamicArray).index] = element;
	++((*dynamicArray).index);
	(*dynamicArray).array = pointer;
	return 1;
}

struct DynamicArray* create(int capacity){
	struct DynamicArray* dynamicArrayPointer;
	dynamicArrayPointer = malloc(sizeof(struct DynamicArray));
	if(!dynamicArrayPointer) return NULL;
	(*dynamicArrayPointer).capacity = capacity;
	(*dynamicArrayPointer).index = 0;
	int* array = malloc((*dynamicArrayPointer).capacity * sizeof(int));
	if(!array) return NULL;
	(*dynamicArrayPointer).array = array;
	return dynamicArrayPointer;
}


void destroy(struct DynamicArray* dynamicArray){
	free((*dynamicArray).array);
	free(dynamicArray);
}
