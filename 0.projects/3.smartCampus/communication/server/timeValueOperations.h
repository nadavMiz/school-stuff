#ifndef TIME_VALE_OPERATIONS_H
#define TIME_VALE_OPERATIONS_H

#include "timeValue.h"

namespace netcpp
{

int TimeValueToMiliSeconds(const TimeValue& _time);

bool TimeValueIsNegative(const TimeValue& _time);

/*-------------------------------------------------------------------------*/

inline int TimeValueToMiliSeconds(const TimeValue& _time)
{
	return _time.GetSeconds() * 1000 + _time.GetNanoseconds() / 1000000;
}

inline bool TimeValueIsNegative(const TimeValue& _time)
{
	return (_time.GetSeconds() < 0 || _time.GetNanoseconds() < 0);
}

}

#endif /* TIME_VALE_OPERATIONS_H */

