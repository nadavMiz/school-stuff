#ifndef __TIME_VALUE_H__
#define __TIME_VALUE_H__

#include <sys/time.h>

namespace netcpp
{

class TimeValue
{
public:	
	TimeValue();
	TimeValue(long _sec, long _msec);
	void Clear();
	void SetToCurrentTime();
	void SetSecond(long _sec);
	void SetMilisecond(long _msec);
	bool IsNegative();
	
	TimeValue& operator+=(const TimeValue& _time);
	TimeValue& operator-=(const TimeValue& _time);
	TimeValue operator+(const TimeValue& _time);
	TimeValue operator-(const TimeValue& _time);
	bool operator<(const TimeValue& _time) const;
	bool operator>(const TimeValue& _time) const;
	bool operator==(const TimeValue& _time) const;
	bool operator<=(const TimeValue& _time) const;
	bool operator>=(const TimeValue& _time) const;
	bool operator!=(const TimeValue& _time) const;
	
	operator struct timeval() const;
	
private:
	struct timeval m_time;
};

inline TimeValue::TimeValue()
{
	m_time.tv_sec = 0;
	m_time.tv_usec = 0;
}

inline TimeValue::TimeValue(long _sec, long _msec)
{
	m_time.tv_sec = _sec;
	m_time.tv_usec = _msec;
}

inline void TimeValue::Clear()
{
	timerclear(&m_time);
}

inline TimeValue::operator struct timeval() const
{
	return m_time;
}

inline void TimeValue::SetToCurrentTime()
{
	gettimeofday(&m_time, 0);
}

inline TimeValue& TimeValue::operator+=(const TimeValue& _time)
{
	timeradd(&m_time, &_time.m_time, &m_time);
	
	return *this;
}

inline TimeValue& TimeValue::operator-=(const TimeValue& _time)
{
	timersub(&m_time, &_time.m_time, &m_time);
	
	return *this;
}

inline TimeValue TimeValue::operator+(const TimeValue& _time)
{
	TimeValue newTime = *this;
	return newTime += _time;
}

inline TimeValue TimeValue::operator-(const TimeValue& _time)
{
	TimeValue newTime = *this;
	return newTime -= _time;
}

inline bool TimeValue::operator<(const TimeValue& _time) const
{
	return timercmp(&m_time, &_time.m_time, <);
}

inline bool TimeValue::operator>(const TimeValue& _time) const
{
	return timercmp(&m_time, &_time.m_time, >);
}

inline bool TimeValue::operator!=(const TimeValue& _time) const
{
	return timercmp(&m_time, &_time.m_time, !=);
}

inline bool TimeValue::operator<=(const TimeValue& _time) const
{
	return !(*this > _time);
}

inline bool TimeValue::operator>=(const TimeValue& _time) const
{
	return !(*this < _time);
}

inline bool TimeValue::IsNegative()
{
	return (m_time.tv_sec < 0 || m_time.tv_usec < 0);
}

}
#endif /* __TIME_VALUE_H__ */

