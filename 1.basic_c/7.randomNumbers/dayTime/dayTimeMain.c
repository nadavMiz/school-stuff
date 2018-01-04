#include "dayTime.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
cTime_t* dayTime1 = malloc(sizeof(cTime_t));
cTime_t* dayTime2 = malloc(sizeof(cTime_t));
cDate_t* date1 = malloc(sizeof(cDate_t));

int userInput;
unsigned int hour, minute, second, day, month, year;
int status = 1;
while (status){
	printf("what would you like to do?\n");
	printf("1) set time 1\n");
	printf("2) set time 2\n");
	printf("3) set date1\n");
	printf("4) print time 1\n");
	printf("5) print date 1\n");
	printf("6) add time 2 to 1\n");
	printf("any other number - exit\n");
	scanf("%d",&userInput);
	switch(userInput){
		case 1:
			printf("enter number of hours\n");
			scanf("%d",&hour);
			printf("enter number of minutes\n");
			scanf("%d",&minute);
			printf("enter number of seconds\n");
			scanf("%d",&second);
			setTime(dayTime1, hour, minute, second);
			break;
		case 2:
			printf("enter number of hours\n");
			scanf("%d",&hour);
			printf("enter number of minutes\n");
			scanf("%d",&minute);
			printf("enter number of seconds\n");
			scanf("%d",&second);
			setTime(dayTime2, hour, minute, second);
			break;
		case 3:
			printf("enter year number\n");
			scanf("%d",&year);
			printf("enter month number\n");
			scanf("%d",&month);
			printf("enter day number\n");
			scanf("%d",&day);
			setDate(date1, day, month, year);
			break;
		case 4:
			printf("what format?\n");
			scanf("%d",&userInput);
			printTime(dayTime1, userInput);
			break;
		case 5:
			printf("what format?\n");
			scanf("%d",&userInput);
			printDate(date1, userInput);
			break;
		case 6:
			addTime(dayTime1, dayTime2);
			break;
		default:
			status = 0;
			break;
		}
	}
free(dayTime1);
free(dayTime2);
return 0;
}
