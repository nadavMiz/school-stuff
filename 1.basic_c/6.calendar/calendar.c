#include <stdlib.h>
#include <stdio.h>
#include "calendar.h"

int IncreaseCapacity(calendar_t* calendar){
	if(!calendar) return 0;
	meetingPtr* pointer = realloc((*calendar).array, (*calendar).capacity * 2 * sizeof(meetingPtr));
	// if the realocation of memmory was unsuccessful return without doing anything.
	if(!pointer) {
		return 0;
	}
	// if the realocation was succesful double the arrays capacity and set the new array pointer
	(*calendar).array = pointer;
	(*calendar).capacity = (*calendar).capacity * 2;
	return 1;
}

void PrintMeeting(meetingPtr meeting){
	if(!meeting) return;
	printf("start hour: %.2f, end hour: %.2f, room number: %d\n", (*meeting).startHour, (*meeting).endHour, (*meeting).roomNum);
}

int ShiftRight(calendar_t* calendar ,int firstIndex){
	if(!calendar || firstIndex < 0 || firstIndex > (*calendar).noe) return 0;
	// if the array reached its maximum capicity realocate more space
	if((*calendar).noe == (*calendar).capacity){
		int increaseSuccess = IncreaseCapacity(calendar);
		//if the capacity increase did not work return 0
		if(increaseSuccess == 0) return 0;
	}
	//shift all the elements right
	for (int i = (*calendar).noe; i > firstIndex; --i){
		(*calendar).array[i] = (*calendar).array[i-1];
	}
	//fill the empty element with NULL
	(*calendar).array[firstIndex] = NULL;
	// increase the number of elements
	++(*calendar).noe;
}

void ShiftLeft(calendar_t* calendar ,int shiftToIndex){
	if(!calendar || shiftToIndex < 0|| shiftToIndex > (*calendar).noe) return;
	// shift the elements to the left
	for(int i = shiftToIndex; i < (*calendar).noe; ++i){
		(*calendar).array[i] = (*calendar).array[i + 1];
	}
	// decrease the number of elements
	--((*calendar).noe);
}

/* creates a pointer to a new calendar */
calendar_t* CreateCalendar(int capacity){
	// check and correct input varubles
	if(capacity <= 0) capacity = 1;
	//create pointer to a new calendar
	calendar_t* calendarPtr = malloc(sizeof(calendar_t));
	if(!calendarPtr) return NULL;
	// create the appoinments array
	(*calendarPtr).array = malloc(capacity * sizeof(meetingPtr));
	if(!(*calendarPtr).array){
		free(calendarPtr);
		return NULL;
	}
	// fill in the varubles ;)
	(*calendarPtr).capacity = capacity;
	(*calendarPtr).noe = 0;
	return calendarPtr;
}

/* creates pointer to a new meeting */
meeting_t* CreateMeeting(float begin, float end, int roomNum){
	// check input
	if( begin < 0.0 || begin > end || end > 24.0 || roomNum < 0) return NULL;
	//create pointer to a new meeting
	meeting_t* newMeeting = malloc(sizeof(meeting_t));
	if(!newMeeting) return NULL;
	// fill the meeting atributes
	(*newMeeting).startHour = begin;
	(*newMeeting).endHour = end;
	(*newMeeting).roomNum = roomNum;
	return newMeeting;
}

void DestroyCalendar(calendar_t* calendar){
	if(calendar){
		if((*calendar).array){
			for(int i = 0; i < (*calendar).noe; ++i){
				free((*calendar).array[i]);
			}
		free((*calendar).array);
		}
	free(calendar);
	}
}

/* insert meeting to the calender */
int InsertMeeting(calendar_t* calendar, meetingPtr meeting){
	// check input
	if(!calendar || !meeting) return 3;
	// define stuff
	float searchBegin = (*meeting).startHour;
	float searchEnd = (*meeting).endHour;
	float nextBegin;
	float preEnd = -1;
	int meetingIndex = 0;
	// if the array is empty just enter the element.
	if((*calendar).noe == 0){
		(*calendar).array[0] = meeting;
		++(*calendar).noe;
		return 1;
	}
	/* find the index of the meeting */
	// if it is the first meeting
	nextBegin = (*(*calendar).array[0]).startHour;
	if(searchBegin > nextBegin){
		// if it is one of the middle meetings
		for(meetingIndex = 1; meetingIndex < (*calendar).noe; ++meetingIndex){
			nextBegin = (*(*calendar).array[meetingIndex]).startHour;
			if(searchBegin < nextBegin){
				preEnd = (*(*calendar).array[meetingIndex-1]).endHour;
				break;
			}
		}
		// if it is the last meeting
		if(meetingIndex == (*calendar).noe){
			preEnd = (*(*calendar).array[meetingIndex - 1]).endHour;
			nextBegin = 25;
		} 
	}

	/* check if the meeting isn't overlapping */ 
	if(searchBegin >= preEnd && searchEnd <= nextBegin){
		// if it isnt overlapping, enter the meeting to the array
		if(!ShiftRight(calendar, meetingIndex)) return 0;
		(*calendar).array[meetingIndex] = meeting;
		return 1;
	}
	return 2;
	
}

meetingPtr FindMeeting(calendar_t* calendar, int beginHour){
// find the messege
	if(beginHour < 0 || beginHour > 24) return NULL;
	meetingPtr currentMeeting;
	for(int i = 0; i < (*calendar).noe; ++i){
		currentMeeting = (*calendar).array[i];
		if (beginHour == (*currentMeeting).startHour){
			return currentMeeting;
		}
	}
	return NULL;	
}

int RemoveMeeting(calendar_t* calendar, int beginHour){
	// find the messege
	if(beginHour < 0 || beginHour > 24) return 0;
	meetingPtr currentMeeting;
	for(int i = 0; i < (*calendar).noe; ++i){
		currentMeeting = (*calendar).array[i];
		// if the messege was found remove it and shift the array left into it
		if (beginHour == (*currentMeeting).startHour){
			free(currentMeeting);
			ShiftLeft(calendar, i);
			return 1;
		}
	}
	return 0;
}

void PrintCalendar(calendar_t* calendar){
	if(!calendar){
		printf("no calender present \n");
		return;
	}
	printf("the meetings are: \n");
	for(int i = 0; i < (*calendar).noe; ++i){
		printf("  %d) ", i);
		PrintMeeting((*calendar).array[i]);
	}
	printf("the number of elements is: %d\n", (*calendar).noe);
	printf("the capacity is: %d\n\n", (*calendar).capacity);
}

void DestroyMeeting(meeting_t* meeting){
	free(meeting);
	
}


