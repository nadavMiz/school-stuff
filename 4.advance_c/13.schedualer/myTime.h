#ifndef __MY_TIME_H__
#define __MY_TIME_H__

#include <stddef.h>
#include <time.h>

/*************************/
/*TIME API FUNCTIONS*/
/*************************/

typedef struct Time Time;

/** 
 * @brief convert the interval between task calls to Time type.
 * @param[in] _milliSecs - the time interval to convert
 * @return Time type of the interval
 */ 
Time* TimeCreate(int _millisecond);

/**
 * @brief get the current time
 * @param[in] _clockID clock id to initialize the time with
 * @return the current time
 */
void TimeGetCurrent(const clockid_t _clockID, Time* _time);

/**
 * @brief safely destroy an instance of Time
 * @param[in] _time - Time to destroy
 * @return void
 */
void TimeDestroy(Time* _time);

/**
 * @brief fuction that checks if _a is smaller than _b
 * @param[in] _a - time to check if smaller
 * @param[in] _b - time to compare _a with
 * @return 1 if _a iss smaller than _b, 0 otherwise.
 */
int	TimeLessThan(const Time* _a, const Time* _b);

/**
 * @brief wait until _time. if _time has already arrived do nothing
 * @param[in] _time - the time to wait to from crurent time
 * @param[in] _clockID - clock id to calculate by
 */
void TimeSleepUntil(const Time* _time, clockid_t _clockID);

/**
 * @brief add two times together. puts the result in _result
 * @param[in] _result - one of the times to add. where to put the result
 * @param[in] _added - one of the times to add. does not change the value
 * @return void
 */
void TimeAdd(Time* _result, const Time* _added);

/*------------------for testing--------------------------*/

long getMiliSec(Time* _time);

time_t GetSeconds(Time* _time);

#endif /*__MY_TIME_H__*/
