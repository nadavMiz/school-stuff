#include <stdio.h>

float average(int* array, int arrayLength){
	float avg = 0;	
	if (arrayLength <= 0) arrayLength = 0;
	for(int i = 0; i < arrayLength; ++i){
		avg += array[i];
	}
	avg /= arrayLength;
	return avg;
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
	float avg = average(array, arrayLength);
	printf("this is the average: %f \n", avg);
}
