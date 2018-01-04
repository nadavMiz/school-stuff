#include "files.h"
#include <stdio.h>
#include <string.h>

int main(){
	int running = 1;
	int userInput;
	int numSentences;
	FILE* myFile = NULL;
	myFile = fopen("alice", "r");
	if(myFile == NULL){
		perror("fopen");
		printf("problem reading file\n");
		return -1;
	}
	while(running){
		printf("what would you like to do?\n");
		printf("1) findLastN\n");
		printf("2) lettersFrequency\n");
		printf("3) wordFrequency\n");
		scanf("%d", &userInput);
		getchar();
		switch(userInput){
			case 1:
				printf("enter number of sentences\n");
				scanf("%d", &numSentences);
				getchar();
				findLastN(myFile, numSentences);
				break;
			case 2:
				lettersFrequency(myFile);
				break;
			case 3:
				wordFrequency(myFile);
				break;
			default:
				running = 0;
				break;
		}
	}
	fclose(myFile);
	return 1;
}
