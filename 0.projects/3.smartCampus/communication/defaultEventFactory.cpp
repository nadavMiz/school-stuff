#include <stdexcept>
#include <sstream>

#include "defaultEventFactory.h"
#include "defaultEvent.h"

namespace smartCampus
{

DefaultEventFactory::~DefaultEventFactory(){}

void DefaultEventFactory::ParseKeyValue(const std::string& _str, std::string& _key, std::string& _value) const
{
	std::size_t pos = _str.find_first_of(EventImp::m_keyValueDelim);
	if(pos == std::string::npos)
	{
		throw std::runtime_error("DefaultEventFactory::CreateEvent: invalid syntax");
	}
	
	_key = _str.substr(0, pos);
	_value = _str.substr(pos + 1, _str.size() - pos - 1);
}

bool DefaultEventFactory::InsertEventHeaderData(const std::string& _str, DefaultEvent* _event) const
{
	std::string key, value;
	ParseKeyValue(_str, key, value);
	
	stringstream valueStream(value);
	
	if("topic" == key)
	{
		valueStream >> _event->m_type;
	}
	else if("section" == key)
	{
		valueStream >> _event->m_room;
	}
	else if("floor" == key)
	{
		valueStream >> _event->m_floor; 
	}
	else if("room" == key)
	{
		valueStream >> _event->m_room;
	}
	else if("agent" != key && "type" != key)
	{
		return false;
	}
	
	return true;
}

void DefaultEventFactory::InsertPayloadValue(const std::string& _str, DefaultEvent* _event) const
{
	std::string key, value;
	ParseKeyValue(_str, key, value);
	
	_event->m_payload.insert(std::pair<std::string,std::string>(key, value));
}

Event DefaultEventFactory::CreateEvent(const ProtocolMsg& _msg)
{
	DefaultEvent* event = new DefaultEvent;
	
	std::vector<std::string>::const_iterator itr;
	for(itr = _msg.m_values.begin(); itr != _msg.m_values.end(); ++itr)
	{	
		if(!InsertEventHeaderData(*itr, event))
		{
			break;
		}
	}
	
	for(; itr != _msg.m_values.end(); ++itr)
	{
		InsertPayloadValue(*itr, event);
	}
	
	return Event(event);
}

}
