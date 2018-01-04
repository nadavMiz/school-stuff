#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

int main(){
	int initialCapacity = 5;
	// create a new Calendar struct
	calendar_t* calendar = NULL;
	// get input and enter it into the array
	int status = 1;
	int option;
	meetingPtr meeting = NULL;
	float startHour;
	float endHour;
	int roomNumber;
	int success;
	while(status == 1){
		printf("what would you like to do? \n");
		printf("1) create calendar\n");
		printf("2) add new meeting \n");
		printf("3) remove a meeting \n");
		printf("4) find a meeting \n");
		printf("5) print calendar \n");
		printf("6) destroy clendar \n");
		printf("any other number - stop \n");
		scanf("%d", &option);
		switch(option){
			case 1:
				if(calendar){
					printf("calendar already exists\n");
					break;
				}
				calendar = CreateCalendar(initialCapacity);
				if(!calendar){
					printf("not enough memory \n");
				}
				break;
			case 2:
				printf("please enter start hour \n");
				scanf("%f", &startHour);
				printf("please enter end hour \n");
				scanf("%f", &endHour);
				printf("please enter room number \n");
				scanf("%d", &roomNumber);
				meeting = CreateMeeting(startHour, endHour, roomNumber);
				if(!meeting){
					printf("couldn't create meeting\n");
					break;
				}
				success = InsertMeeting(calendar, meeting);
				if(success != 1){
					switch(success){
						case 0:
							printf("not enough memmory\n");
							break;
						case 2:
							printf("overlapping meetings\n");
							break;
						case 3:
							printf("calender missing\n");
							break;
					}
				DestroyMeeting(meeting);
				}
				break;
			case 3:
				printf("enter start hour of the meeting to remove\n");
				scanf("%f", &startHour);
				success = RemoveMeeting(calendar, startHour);
				if(!success) printf("\nmeeting not found\n\n");
				break;
			case 4:
				printf("enter start hour of the meeting you want to find\n");
				scanf("%f", &startHour);
				meeting = FindMeeting(calendar, startHour);
				if(!meeting) printf("meeting not found \n");
				else{
					printf("the meetings adress is: %p \n", meeting);
					printf("the meeting is: \n");
					printf(" start hour: %.2f, end hour: %.2f, ",(*meeting).startHour, (*meeting).endHour);
					printf("room number: %d\n", (*meeting).roomNum);
				}
				break;
			case 5:
				PrintCalendar(calendar);
				break;
			case 6:
				if(calendar){
					DestroyCalendar(calendar);
					calendar = NULL;
					}
				else printf("no calendar present\n");
				break;
			default:
				status = 3;
				break;
		}
	}
	DestroyCalendar(calendar);
	return 0;
}	
