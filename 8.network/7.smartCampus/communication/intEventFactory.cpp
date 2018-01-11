#include <stdexcept>
#include <sstream>
#include <iostream>

#include "intEventFactory.h"
#include "intEvent.h"

namespace nadavElectric
{

IntEventFactory::~IntEventFactory(){}

void IntEventFactory::ParseKeyValue(const std::string& _str, std::string& _key, std::string& _value) const
{
	std::size_t pos = _str.find_first_of(EventImp::m_keyValueDelim);
	if(pos == std::string::npos)
	{
		std::cout << _str << std::endl;
		throw std::runtime_error("intEventFactory::CreateEvent: invalid syntax");
	}
	
	_key = _str.substr(0, pos);
	_value = _str.substr(pos + 1, _str.size() - pos - 1);
}

void IntEventFactory::InsertEventHeaderData(const std::string& _str, IntEvent* _event) const
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
		valueStream >> _event->m_section;
	}
	else if("floor" == key)
	{
		valueStream >> _event->m_floor; 
	}
	else if("room" == key)
	{
		valueStream >> _event->m_room;
	}
	else if("data" == key)
	{
		valueStream >> _event->m_data;
	}
}

Event IntEventFactory::CreateEvent(const ProtocolMsg& _msg)
{
	IntEvent* event = new IntEvent;
	event->m_topic = "int";
	
	std::vector<std::string>::const_iterator itr;
	for(itr = _msg.m_values.begin(); itr != _msg.m_values.end(); ++itr)
	{	
		InsertEventHeaderData(*itr, event);
	}
	
	return Event(event);
}

}
