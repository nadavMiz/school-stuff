#include <string>
#include <sstream>

#include "eventSerializer.h"
#include "eventImp.h"

namespace smartCampus
{

void EventSerializer::SerializeHeader(const Event& _event, ProtocolMsg& _msg) const
{
	_msg.m_topic = "event";
	
	_msg.m_values.push_back("type" + EventImp::m_keyValueDelim + _event->m_type);
	_msg.m_values.push_back("topic" + EventImp::m_keyValueDelim + _event->m_topic);
	_msg.m_values.push_back("section" + EventImp::m_keyValueDelim + _event->m_section);
	
	stringstream floor;
	floor << _event->m_floor;
	_msg.m_values.push_back("floor" + EventImp::m_keyValueDelim + floor.str());
	
	_msg.m_values.push_back("room" + EventImp::m_keyValueDelim + _event->m_room);
}

ProtocolMsg EventSerializer::Serialize(const Event& _event) const
{
	ProtocolMsg newMsg;
	
	SerializeHeader(_event, newMsg);
	
	newMsg.m_values.push_back(_event->SerializePayload());
	
	return newMsg;
}

}
