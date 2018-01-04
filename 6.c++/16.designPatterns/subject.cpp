#include "subject.h"
#include "observer.h"

void Subject::Attach(Observer* _obs, const string& _type)
{
	if(0 != _obs)
	{
		m_observers.insert(std::pair<string, Observer*>(_type, _obs));
	}
}

void Subject::Detach(Observer* _obs, const string& _type)
{
	if(0 == _obs)
	{
		return;
	}
	
	multimap<string, Observer*>::iterator itr = m_observers.find(_type);
	while(m_observers.end() != itr && _type == (*itr).first)
	{
		if(_obs == (*itr).second)
		{
			m_observers.erase(itr);
			break;
		}
		++itr;
	}
}

void Subject::Notify(const string& _type) const
{
	multimap<string, Observer*>::const_iterator itr = m_observers.find(_type);
	while(m_observers.end() != itr && _type == (*itr).first)
	{
			(*itr).second->Update(this);
			++itr;
	}
}
