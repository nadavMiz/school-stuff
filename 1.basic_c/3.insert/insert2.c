#include <stdio.h>
#include <stdlib.h>

struct DynamicArray{
	int capacity;
	int index;
	int* array;
};

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


int main() {
	// create a new dinamic array struct
	struct DynamicArray dynamicArray = {.capacity = 5,.index = 0};
	int* array = malloc(dynamicArray.capacity * sizeof(int));
	if(!array){
		printf("not enough memory \n");
		return 0;
	}
	dynamicArray.array = array;
	// get input and enter it into the array
	int nextNumber = 1;
	printf("enter numbers one by one. to end enter 0 \n");
	while(nextNumber){
		scanf("%d", &nextNumber);
		insert(&dynamicArray, nextNumber);
	}
	//print the array and its attributes
	printf("the array is: ");
	for(int i = 0; i < dynamicArray.index - 1; ++i){
		printf("%d " ,dynamicArray.array[i]);
	}
	printf("\n");
	printf("the capacity is: %d \nthe last index is: %d \n", dynamicArray.capacity, dynamicArray.index - 1);
	free(dynamicArray.array);
	return 0;
}
