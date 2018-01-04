#include "DynamicArray.h"
#include <stdlib.h>
int increaseCapacity(DynamicArray* DA){
	if(!DA) return 0;
	intptr* pointer = realloc((*DA).array, (*DA).capacity * 2 * sizeof(intptr));
	// if the realocation of memmory was unsuccessful return without doing anything.
	if(!pointer) {
		return 0;
	}
	// if the realocation was succesful double the arrays capacity and set the new array pointer
	(*DA).array = pointer;
	(*DA).capacity = (*DA).capacity * 2;
	return 1;
}

int shiftRight(DynamicArray* DA ,int firstIndex){
	if(!DA || firstIndex < 0 || firstIndex >= (*DA).noe) return 0;
	// if the array reached its maximum capicity realocate more space
	if((*DA).noe == (*DA).capacity){
		int increaseSuccess = increaseCapacity(DA);
		//if the capacity increase did not work return 0
		if(increaseSuccess == 0) return 0;
	}

	//shift all the elements right
	for (int i = (*DA).noe; i > firstIndex; --i){
		(*DA).array[i] = (*DA).array[i-1];
	}
	//fill the empty element with NULL
	(*DA).array[firstIndex] = NULL;
	// increase the number of elements
	++(*DA).noe;
}

void shiftLeft(DynamicArray* DA ,int shiftToIndex){
	if(!DA || shiftToIndex < 0) return;
	// shift the elements to the left
	for(int i = shiftToIndex; i < (*DA).noe; ++i){
		(*DA).array[i] = (*DA).array[i + 1];
	}
	// decrease the number of elements
	--((*DA).noe);
}

int insert(DynamicArray* DA, intptr element) {
	if(!DA) return 0;
	// if the array reached its maximum capicity realocate more space
	if((*DA).noe == (*DA).capacity){
		int increaseSuccess = increaseCapacity(DA);
		//if the capacity increase did not work return 0
		if(increaseSuccess == 0) return 0;
	}

	// enter the element to the array.
	(*DA).array[(*DA).noe] = element;
	++((*DA).noe);
	return 1;
}

int insertAtN (DynamicArray* DA, intptr element, int index){
	// if the index is out of bounds say so (return 2)
	if (!DA) return 2;
	if(index > (*DA).noe || index < 0) return 2;

	else if(index == (*DA).noe){
		return insert(DA, element);
	}
	//shift the array right from the index and enter the element there
	if(!shiftRight(DA, index)) return 0;
	(*DA).array[index] = element;
	return 1;
}

int delete(DynamicArray* DA, int searchNum){
	if (!DA) return 0;
	for(int i = 0; i < (*DA).noe; ++i){
		if(*((*DA).array[i]) == searchNum){
			free((*DA).array[i]);
			shiftLeft(DA, i);
			return 1;
		}
	}
	return 0;
}

intptr find(DynamicArray* DA, int element){
	if(!DA) return NULL;
	for(int i = 0; i < (*DA).noe; ++i){
		if(*((*DA).array[i]) == element){
			return (*DA).array[i];
		}
	}
	return NULL;
}

struct DynamicArray* create(int capacity){
	if (capacity <= 0) capacity = 1;
	//create the dynamic arrays pointer
	struct DynamicArray* dynamicArrayPointer;
	dynamicArrayPointer = malloc(sizeof(struct DynamicArray));
	if(!dynamicArrayPointer) return NULL;

	// set the DAs capacity and index
	(*dynamicArrayPointer).capacity = capacity;
	(*dynamicArrayPointer).noe = 0;

	// create the DAs array
	intptr* array = malloc(capacity * sizeof(intptr));
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
