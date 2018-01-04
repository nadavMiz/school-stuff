#ifndef CALENDAR_H
#define CALENDAR_H

/*
file line format:
bein hour end hour room num
*/

typedef struct{
	float startHour;
	float endHour;
	int roomNum;

} meeting_t;

typedef meeting_t* meetingPtr;

typedef struct{
	int capacity;
	int noe;
	meetingPtr* array;

} calendar_t;

calendar_t* CreateCalendar(int capacity);
meeting_t* CreateMeeting(float begin, float end, int roomNum);
void DestroyCalendar(calendar_t* calendar);
int InsertMeeting(calendar_t* calendar, meeting_t* meeting);
int RemoveMeeting(calendar_t* calendar, int beginHour);
void PrintCalendar(calendar_t* calendar);
meetingPtr FindMeeting(calendar_t* calendar, int beginHour);
void DestroyMeeting(meeting_t* meeting);

#endif
