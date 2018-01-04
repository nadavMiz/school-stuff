#include "dayTime.h"
#include <stdio.h>

/* normalize the time*/
int normalizeTime(cTime_t* dayTime){
	unsigned int sumTime = (*dayTime).seconds + (*dayTime).minutes * 60 + (*dayTime).hours * 3600;
	(*dayTime).seconds = sumTime % 60;
	sumTime /= 60;
	(*dayTime).minutes = sumTime % 60;
	sumTime /= 60;
	(*dayTime).hours = sumTime % 24;
	int days = sumTime / 24;
	return days;
}

/* set the time (normolize if needed) */
int setTime(cTime_t* dayTime , unsigned int hours, unsigned int minutes, unsigned int seconds){
	(*dayTime).seconds = seconds;
	(*dayTime).minutes = minutes;
	(*dayTime).hours = hours;
	normalizeTime(dayTime);
	
	return 1;
}

/* print the time in different formats */
int printTime(cTime_t* dayTime, unsigned int formatType){
	if(!dayTime) return 0;
	switch(formatType){
		case 1:
			printf("%02d:%02d:%02d\n",(*dayTime).hours, (*dayTime).minutes, (*dayTime).seconds);
			break;
		case 2:
			printf("%d:%02d:%02d ",(*dayTime).hours%12, (*dayTime).minutes, (*dayTime).seconds);
			if((*dayTime).hours > 12) printf("PM\n");
			else printf("AM\n");
	}
}

/* get hours from time */
int hours(cTime_t* dayTime){
	if(!dayTime) return -1;
	return (*dayTime).hours;
}

/* get minutes from time */
int minutes(cTime_t* dayTime){
	if(!dayTime) return -1;
	return (*dayTime).minutes;
}

/* get seconds from time */
int seconds(cTime_t* dayTime){
	if(!dayTime) return -1;
	return (*dayTime).seconds;
}

/* add one time to another */
int addTime(cTime_t* dayTime1, cTime_t* dayTime2){
	(*dayTime1).hours += (*dayTime2).hours;
	(*dayTime1).minutes += (*dayTime2).minutes;
	(*dayTime1).seconds += (*dayTime2).seconds;
	int days = normalizeTime(dayTime1);
}

int normalizeDate(cDate_t* date){
	if(!date) return 0;
	int dayTable[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int yearDays;
	int leapYear = 0;
	// add years from months
	(*date).year += (*date).month / 12;
	(*date).month = (*date).month % 12;
	// add years from days
	while(1){
		if((*date).year % 4 == 0) yearDays = 366;
		else yearDays = 365;
		if((*date).day <= yearDays) break;
		(*date).day -= yearDays;
		++(*date).year;
	}
	// add months drom days
	if((*date).year % 4 == 0) dayTable[1] = 29;
	while((*date).day > dayTable[(*date).month]){
		(*date).day -= dayTable[(*date).month];
		(*date).month += 1;
		if((*date).month == 12){
			(*date).year += 1;
			(*date).month = 0;
			if((*date).year % 4 == 0) dayTable[1] = 29;
			else dayTable[1] = 28;
		}
	}
	return 1;
}

int setDate(cDate_t* date, unsigned int day, unsigned int month, unsigned int year){
	(*date).year = year;
	(*date).month = month - 1;
	(*date).day = day;
	normalizeDate(date);
}

void printDate(cDate_t* date, unsigned int formatType){
	switch(formatType){
		case 1:
			printf("date: %02d/", (*date).day);
			switch((*date).month){
				case 0:
					printf("Jan");
					break;
				case 1:
					printf("Feb");
					break;
				case 2:
					printf("Mar");
					break;
				case 3:
					printf("Apr");
					break;
				case 4:
					printf("May");
					break;
				case 5:
					printf("Jun");
					break;
				case 6:
					printf("Jul");
					break;
				case 7:
					printf("Aug");
					break;
				case 8:
					printf("Sep");
					break;
				case 9:
					printf("Oct");
					break;
				case 10:
					printf("Nov");
					break;
				case 11:
					printf("Dec");
					break;				
			}
			printf("/%04d\n", (*date).year);
			break;
		case 2:
			// european format
			printf("%02d/%02d/%04d\n", (*date).day, (*date).month + 1, (*date).year);
			break;
		case 3:
			// american format
			printf("%02d/%02d/%04d\n", (*date).month + 1, (*date).day, (*date).year);
			break;
	}
}

int getYear(cDate_t* date){
	if(!date) return -1;
	return (*date).year;
}

int getMonth(cDate_t* date){
	if(!date) return -1;
	return (*date).month + 1;
}

int getDay(cDate_t* date){
	if(!date) return -1;
	return (*date).day;
}

int getDayInYear(cDate_t* date){
	int dayTable[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if((*date).year % 4) dayTable[1] = 29;
	int result = 0;
		for(int i = 0; i < (*date).month; ++i){
			result += dayTable[i];
		}
	result += (*date).day;
	return result;
}

int isLeapYear(cDate_t* date){
	return (*date).year % 4;
}

void sumTimeAndChangeDate1(cDate_t* date1, cTime_t* dayTime1, cTime_t* dayTime2){
	int days = addTime(dayTime1, dayTime2);
	(*date1).day += days;
	normalizeDate(date1);
}

