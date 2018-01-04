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
	intptr numPtr;
	int success;
	int status = 1;
	int index;
	intptr adress;
	while(status == 1){
		printf("what would you like to do? \n1) add \n2) insert\n3) find \n4) remove \nany other number - stop \n");
		scanf("%d", &nextNumber);
		switch(nextNumber){
			case 1:
				// add number
				printf("please enter a number \n");
				scanf("%d", &nextNumber);
				numPtr = malloc(sizeof(int));
				if(numPtr){
					*numPtr = nextNumber;
					status = insert(dynamicArray, numPtr);
				}
				else status = 0;
				if(status == 0) printf("not enough memory \n");
				break;

			case 2:
				// insert number at index
				printf("please enter a number \n");
				scanf("%d", &nextNumber);
				printf("please enter an index \n");
				scanf("%d", &index);
				numPtr = malloc(sizeof(int));
				if(numPtr){
					*numPtr = nextNumber;
					status = insertAtN(dynamicArray, numPtr, index);
				}
				else status = 0;
				if(status == 0) printf("not enough memory \n");
				// if the index is too large (status = 2) say so
				else if (status == 2){
					printf("index is out of bounds \n");
					status = 1;
				}
				break;

			case 3:
				// find element
				printf("please enter a number to find \n");
				scanf("%d", &nextNumber);
				adress = find(dynamicArray ,nextNumber);
				if(!adress){
					printf("the number is not present \n");
				}
				else{
					printf("the adress of the number is: %p \n", adress);
					printf("the number is: %d \n", *adress);
				}
				break;

			case 4:
				// delete element
				printf("please enter a number to delete \n");
				scanf("%d", &nextNumber);
				success = delete(dynamicArray, nextNumber);
				if (!success){
					printf("the number is not present \n");
				}
				break;
				

			default:
				status = 3;
				break;
		}
	}
	//print the array and its attributes
	printf("the array is: ");
	for(int i = 0; i < (*dynamicArray).noe; ++i){
		printf("%d " ,*(*dynamicArray).array[i]);
	}
	printf("\n");
	printf("the capacity is: %d \nthe number of elements is: %d \n", (*dynamicArray).capacity, (*dynamicArray).noe);
	destroy(dynamicArray);
	return 0;
}
