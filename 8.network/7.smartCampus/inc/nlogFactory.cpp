#include "nlogFactory.h"

#include <string>

#include "nlog.h"

NlogFactory NlogFactory::m_logFactory;

NlogFactory::NlogFactory(){}

NlogFactory::~NlogFactory()
{
	for(std::map<std::string, Nlog*>::iterator itr = m_logs.begin(); itr != m_logs.end(); ++itr)
	{
		delete itr->second;
	}
}

Nlog* NlogFactory::GetLog(const std::string& _name)
{

	std::map<std::string, Nlog*>::iterator itr;
	if(m_logs.end() != (itr = m_logs.find(_name)))
	{
		return itr->second;
	}
	
	Nlog* newLog = new Nlog(m_path + _name);
	m_logs.insert(std::pair<std::string, Nlog*>(_name ,newLog));
	
	return newLog;
}
