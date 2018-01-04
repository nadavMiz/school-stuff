#ifndef DAYTIME_H
#define DAYTIME_H
/*
structure repressenting time of the day 
*/
typedef struct{
	unsigned int seconds;
	unsigned int minutes;
	unsigned int hours;
} cTime_t ;

/*
structure repressenting a date
*/
typedef struct{
	unsigned int year;
	unsigned int month;
	unsigned int day;
} cDate_t;

/**************** time struct functions *******************/

/* 
changes the attributes of a cTime_t struct. normalize the time if necessary
returns 0: if failed. 1: if succeded
*/
int setTime(cTime_t* dayTime , unsigned int hours, unsigned int minutes, unsigned int seconds);
/*
prints the time according to the inputed format type.
format types:
	1: 13:23:12
	2:  1:23:12 PM
return 0 if failed. 1: if sccedded
*/
int printTime(cTime_t* dayTime, unsigned int formatType);
/*
returns the hours atribute of a cTime_t struct
*/
int hours(cTime_t* dayTime);
/*
returns the minutes atribute of a cTime_t struct
*/
int minutes(cTime_t* dayTime);
/*
returns the seconds atribute of a cTime_t struct
*/
int seconds(cTime_t* dayTime);
/*
add together two times. store the result in dayTime1
return 1: succedded. 0: failed
*/
int addTime(cTime_t* dayTime1, cTime_t* dayTime2);



/****************** date struct functions *********************/

/*
set(/change) the attributes of a cDate_t struct. normalize the date if needed
return 1: succedded. 0: failed
*/
int setDate(cDate_t* date ,unsigned int day, unsigned int month, unsigned int year);
/*
prints the date stored in date according to formatType format.
formats:
	1: 22/Jan/2001
	2: 22/01/2001 //european
	3: 01/22/2001 //american
return 1: succedded. 0: failed
*/
void printDate(cDate_t* date, unsigned int formatType);
/*
returns the year atribute of a date.
*/
int getYear(cDate_t* date);
/*
returns the month atribute of a date.
*/
int getMonth(cDate_t* date);
/*
returns the day atribute of a date.
*/
int getDay(cDate_t* date);
/*
returns which day of the year according to date.
*/
int getDayInYear(cDate_t* date);
/*
returns if the year in date is a leap year or not
return 1: leap year. 2: not leap year.
*/
int isLeapYear(cDate_t* date);

/*********************** other functions **********************/

/*
add together two times. store the result in dayTime1.
changes date1 if time added exceeds 24 hourss
return 1: succedded. 0: failed
*/
void sumTimeAndChangeDate(cDate_t* date1, cTime_t* dayTime1, cTime_t* dayTime2);
#endif 
