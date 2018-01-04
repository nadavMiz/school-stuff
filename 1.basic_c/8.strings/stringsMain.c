#include <stdio.h>
#include "myStrings.h"

int main(){
	int userInput;
	char myString[20];
	char myString2[20];
	int myInt;
	int result;
	int loop = 1;
	while(loop){
		printf("what would you like to do\n");
		printf("1) string to int \n");
		printf("2) int to string \n");
		printf("3) reverse string \n");
		printf("4) is palindrome \n");
		printf("5) myStrcmp \n");
		printf("6) myStrcat \n");
		printf("any other number - quit\n");
		scanf("%d", &userInput);
		switch(userInput){
			case 1:
				printf("please enter string\n");
				scanf("%s" ,myString);
				myInt = myAtoi(myString);
				printf("your number is: %d\n", myInt);
				break;

			case 2:
				printf("please enter integer \n");
				scanf("%d", &myInt);
				myItoa(myInt, myString);
				printf("your string is: %s\n", myString);
				break;

			case 3:
				printf("enter string to reverse\n");
				scanf("%s", myString);
				reverseString(myString);
				printf("your reversed string is: %s \n", myString);
				break;

			case 4:
				printf("enter string to check\n");
				scanf("%s", myString);
				result = isPalindrom(myString);
				if(result) printf("your string is a plaindrom\n");
				else printf("your string is not a palindrom\n");
				break;
			case 5:
				printf("enter string1\n");
				scanf("%s", myString);
				printf("enter string2\n");
				scanf("%s", myString2);
				result = myStrcmp(myString, myString2);
				printf("the result is: %d\n", result);
				
				break;
			case 6:
				printf("enter string1\n");
				scanf("%s", myString);
				printf("enter string2\n");
				scanf("%s", myString2);
				myStrcat(myString, myString2);
				printf("the result is: %s\n", myString);
				break;

			default:
				loop = 0;
				break;
		}
	}
}
