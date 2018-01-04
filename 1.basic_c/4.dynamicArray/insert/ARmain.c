#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"

int main() {
	int initialCapacity = 5;
	// create a new dinamic array struct
	struct DynamicArray* dynamicArray;
	dynamicArray = create(initialCapacity);
	if(!dynamicArray){
		printf("not enough memory \n");
		return 0;
	}
	// get input and enter it into the array
	int nextNumber;
	int insertSuccesful = 1;
	while(1){
		printf("what would you like to do? \n1) add number \n2) exit \n");
		scanf("%d", &nextNumber);
		if(nextNumber == 2) break;
		if(nextNumber == 1) {
			printf("please enter a number \n");
			scanf("%d", &nextNumber);
			insertSuccesful = insert(dynamicArray, nextNumber);
			if(!insertSuccesful){
				printf("not enough memory \n");
				break;
			}
		}
		else printf("invalid option \n");
	}
	//print the array and its attributes
	printf("the array is: ");
	for(int i = 0; i < (*dynamicArray).index - 1; ++i){
		printf("%d " ,(*dynamicArray).array[i]);
	}
	printf("\n");
	printf("the capacity is: %d \nthe last index is: %d \n", (*dynamicArray).capacity, (*dynamicArray).index - 1);
	destroy(dynamicArray);
	return 0;
}
