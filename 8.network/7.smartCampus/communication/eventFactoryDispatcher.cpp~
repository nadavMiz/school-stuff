#include <stdexcept>

#include "eventFactoryDispatcher.h"
#include "defaultEventFactory.h"
#include "intEventFactory.h"

namespace smartCampus
{

EventFactoryDispatcher::EventFactoryDispatcher():
	m_defaultFactory(new DefaultEventFactory)
{
	m_factories.insert(std::pair<std::string, IEventFactoryPtr>("int", 
					IEventFactoryPtr(new nadavElectric::IntEventFactory)));
}
	
std::string EventFactoryDispatcher::GetTopic(const std::string& _str) const
{
	std::size_t pos = _str.find_first_of(EventImp::m_keyValueDelim);
	if(pos == std::string::npos)
	{
		throw std::runtime_error("EventFactoryDispatcher::CreateEvent: invalid syntax");
	}
	
	std::string key = _str.substr(0, pos);
	if(key != "type")
	{
		throw std::runtime_error("EventFactoryDispatcher::CreateEvent: invalid syntax");
	}
	
	return _str.substr(pos + 1, _str.size() - pos - 1);
}
	
Event EventFactoryDispatcher::CreateEvent(const ProtocolMsg& _msg)
{
	std::string topic = GetTopic(_msg.m_values.at(0));
	
	std::map<std::string, IEventFactoryPtr>::iterator itr = m_factories.find(topic);
	if(itr != m_factories.end())
	{
		return itr->second->CreateEvent(_msg);
	}
	return m_defaultFactory->CreateEvent(_msg);
}

}
