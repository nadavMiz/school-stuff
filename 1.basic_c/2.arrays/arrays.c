#include <stdio.h>
#include <stdlib.h>

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


void onesAndZeros(int* array, int arrayLength){
	int firstOne = 0;
	for(int i = 0; i < arrayLength; ++i){
		if(array[i] == 1){
			break;
		}
		++firstOne;
	}
	for(int i = firstOne + 1; i < arrayLength; ++i){
		if(array[i] == 0){
			swap(&array[i], &array[firstOne]);
			++firstOne;
		}		
	}
}

void evenThanOdd(int* array, int arrayLength){
	for(int i = 0; i < arrayLength; ++i){
		if(array[i] % 2 == 0){
			for(int j = i; j > 0; --j){
				if(array[j - 1] % 2 == 0) break;
				swap(&array[j], &array[j-1]);
			}
		}
	}
}

int mostFrequent(int* array, int arrayLength){
	if(arrayLength <= 0){ 
		return 0;
	}
	int largest;
	int largestCount = 0;
	int current;
	int currentCount;
	for (int i = 0; i < arrayLength; ++i){
		current = array[i];
		currentCount = 1;
		for(int j = i+1; j < arrayLength; ++j){
			if(array[j] == current){
				++currentCount;
			}
		}
		if(currentCount > largestCount){
			largestCount = currentCount;
			largest = current;
		}
	}
	return largest;
}

int binarySearch(int searchNum, int* array, int arrayLength){
	int left = 0;
	int right = arrayLength - 1;
	if(searchNum < array[left] || searchNum > array[right]) return -1;
	if(searchNum == array[left]) return left;
	if(searchNum == array[right]) return right;
	int middle;
	while(right - left > 1){
		middle = (left + right) / 2;
		if(searchNum == array[middle]){
			return middle;		
		}
		else if (searchNum > array[middle]){
			left = middle;
		}
		else{
			right = middle;
		}
	}
	return -1;
}


int main(){
	int exit = 0;
	while (exit == 0){
		printf("what would you like to do? \n");
		printf("1) onesAndZeros\n");
		printf("2) evenThanOdd\n");
		printf("3) mostFrequent\n");
		printf("4) binarySearch \n");
		printf("5) exit \n");
		int userInput;
		scanf("%d", &userInput);
		if(userInput == 5) return 0;
		int arrayLength, nextNumber;
		printf("how many elements do you want? ;) \n");
		scanf("%d", &arrayLength);
		int* array;
		if(array == 0){
			printf("not enouth space \n");
			return 0;
		} 
		array = malloc(arrayLength * sizeof(int));
		printf("please enter your numbers one by one \n");
		for(int i = 0; i < arrayLength; ++i){
			scanf("%d", &nextNumber);
			array[i] = nextNumber;
		}
		int freq;
		int searchNum;
		int numIndex;
		switch(userInput){
			case 1:
				onesAndZeros(array, arrayLength);
				printf("your array is: \n");
				for(int i = 0; i < arrayLength; ++i){
					printf("%d " ,array[i]);
				}
				printf("\n");
				break;
			case 2:
				evenThanOdd(array, arrayLength);
				printf("your array is: \n");
				for(int i = 0; i < arrayLength; ++i){
					printf("%d " ,array[i]);
				}
				printf("\n");
				break;
			case 3:
				freq = mostFrequent(array, arrayLength);
				printf("most frequent number is: %d \n", freq);
				break;
			case 4:
				printf("what number would you like to find \n");
				scanf("%d", &searchNum);
				numIndex = binarySearch(searchNum, array, arrayLength);
				if (numIndex == -1){
					printf("number not present");
				}
				else{
					printf("the numbers index is: %d \n", numIndex);
				}
				break;
			default:
				printf("Invalid option \n");
				break;
		}
		free(array);
	}
}
