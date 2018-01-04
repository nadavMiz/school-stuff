#include <stdio.h>

void swap(int *a, int *b){
	int temp;
	temp = *b;
	*b = *a;
	*a  = temp;
}

void sort(int* array, int arrayLength){
	if(arrayLength <= 0) return;
	for(int i = 1; i < arrayLength; ++i){
		for(int j = i; j > 0; --j){
			if (array[j] < array[j-1]){
				swap(&array[j], &array[j-1]);
			}
			else break;
		}
	}
}

void main(){
	int arrayLength, nextNumber;
	printf("how many elements do you want? ;) \n");
	scanf("%d", &arrayLength);
	int array[arrayLength];
	printf("please enter your numbers one by one \n");
	for(int i = 0; i < arrayLength; ++i){
		scanf("%d", &nextNumber);
		array[i] = nextNumber;
	}
	sort(array, arrayLength);
	for(int i = 0; i < arrayLength; ++i){
		printf("%d " ,array[i]);
	}
	printf("\n");
}


