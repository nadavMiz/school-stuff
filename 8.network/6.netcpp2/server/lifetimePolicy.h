#ifndef __LIFETIME_POLICY_H__
#define __LIFETIME_POLICY_H__

#include <vector>
#include <map>
#include <tr1/memory>

#include "timeValue.h"
#include "socket.h"
#include "uncopyable.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<Socket> SocketPtr;

class LifetimePolicy: private Uncopyable
{
public:
	LifetimePolicy(const TimeValue& _timeOut);
	//~LifetimePolicy(); default DTOR
	
	void AddSocket(SocketPtr _socket);
	const TimeValue& GetNextTime(); //throw runtime_error if no next time
	const std::vector<SocketPtr>& GetSocketsToDelete();
	void UpdateSetTime();
	void UpdateTimeOut(SocketPtr _socket);
	void RemoveSocket(SocketPtr _socket);

private:
	/* data */
	std::multimap<TimeValue, SocketPtr> m_sockets;
	std::vector<SocketPtr> m_socketsToDelete;
	TimeValue m_waitTime;
	TimeValue m_nextTimeOut;
	TimeValue m_timeOut;
};

}
#endif /* __LIFETIME_POLICY_H__ */

