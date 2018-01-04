#ifndef SELECT_SET_H
#define SELECT_SET_H

#include <sys/select.h> /* fd_set */

#include "timeValue.h" /* timeValue */
#include "socket.h" /* Socket */

namespace netcpp
{

class SelectSet
{
public:
	SelectSet();
	//~SelectSet(); default DTOR
	
	unsigned int Wait();
	unsigned int WaitUntil(TimeValue& _time);
	void Set(const Socket& _selectable);
	bool IsSet(const Socket& _selectable);
	void ClearOne(const Socket& _selectable);
	void ClearAll();

private:
	unsigned int WaitImp(struct timeval* _time);

private:
	/* data */
	fd_set m_fdSet;
	fd_set m_activeFDs;
};


inline unsigned int SelectSet::Wait()
{
	return WaitImp(0);
}

inline unsigned int SelectSet::WaitUntil(TimeValue& _time)
{
	struct timeval time = _time;
	return WaitImp(&time);
}


}
#endif /* SELECT_SET_H */

