#include <stdio.h>

int ex1(int lines){
	for(int i = 1; i <= lines; ++i){
		for(int j = 0; j<i; ++j){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int ex2(int lines){
	for(int i = 1; i <= lines; ++i){
		for(int j = 0; j<i; ++j){
			printf("*");
		}
		printf("\n");
	}
	for(int i = lines-1; i>=1; --i){
		for(int j = 0; j<i; ++j){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int ex3(int lines){
	for(int i = 1; i <= lines; ++i){
		for(int j = lines; j>i; --j){
			printf(" ");
		}
		printf("*");
		for(int j = 1; j<i; ++j){
			printf("**");
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int main(){
	printf("please enter number of lines \n");
	int lines;
	scanf("%d", &lines);
	ex1(lines);
	ex2(lines);
	ex3(lines);
	return 0;
}
