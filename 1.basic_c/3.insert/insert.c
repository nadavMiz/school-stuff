#include <stdio.h>
#include <stdlib.h>

int* insert(int* array, int element, int* index, int* capacity) {
	int* pointer = array;
	if(*index == *capacity){
		*capacity = *capacity;
		pointer = realloc(array, *capacity * 2 * sizeof(int));
		if(!pointer) {
			return array; 
		}
		else{
			*capacity = *capacity * 2;
		}
	}
	pointer[*index] = element;
	++(*index);
	return pointer;
}


int main() {
	int capacity = 5;
	int arrayIndex = 0;
	int* array;
	array = malloc(capacity * sizeof(int));
	if(!array){
		printf("not enough memory \n");
		return 0;
	}
	int nextNumber = 1;
	int* tmpArrayPointer;
	printf("enter numbers one by one. to end enter 0 \n");
	while(nextNumber){
		scanf("%d", &nextNumber);
		tmpArrayPointer = insert(array, nextNumber, &arrayIndex, &capacity);
		if(tmpArrayPointer){ 
			array = tmpArrayPointer;
		}
		else{
			printf("not enough memory \n");
			break;
		}
	}
	printf("the array is: ");
	for(int i = 0; i < arrayIndex - 1; ++i){
		printf("%d " ,array[i]);
	}
	printf("\n");
	printf("the capacity is: %d \nthe last index is: %d \n", capacity, arrayIndex);
	free(array);
	return 0;	
}
