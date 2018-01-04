#include <stdexcept> // runtime_error

#include "lifetimePolicy.h"

LifetimePolicy::LifetimePolicy(const TimeValue& _timeOut):
	m_timeOut(_timeOut){}

const TimeValue& LifetimePolicy::GetNextTime()
{
	if(m_sockets.empty())
	{
		throw std::runtime_error("LifetimePolicy: no next time");
	}
	
	std::map<TimeValue, SocketPtr>::iterator nextSocket = m_sockets.begin();
	
	m_waitTime.SetToCurrentTime();
	
	m_waitTime -= nextSocket->first;
	if(m_waitTime.IsNegative())
	{
		m_waitTime.Clear();
	}
	
	return m_waitTime;
}

const std::vector<SocketPtr>& LifetimePolicy::GetSocketsToDelete()
{
	TimeValue currentTime;
	currentTime.SetToCurrentTime();

	m_socketsToDelete.clear();
		
	for(std::map<TimeValue, SocketPtr>::iterator itr = m_sockets.begin(); itr != m_sockets.end(); ++itr)
	{
		if(itr->first < currentTime)
		{
			m_socketsToDelete.push_back(itr->second);	
		}
		else
		{
			break;
		}
	}
	
	return m_socketsToDelete;
}

void LifetimePolicy::UpdateSetTime()
{
	m_nextTimeOut.SetToCurrentTime();
	m_nextTimeOut += m_timeOut;
}

void LifetimePolicy::UpdateTimeOut(SocketPtr _socket)
{
	std::map<TimeValue, SocketPtr>::iterator itr = m_sockets.find()
}
