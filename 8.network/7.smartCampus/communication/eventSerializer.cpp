#include <string>
#include <iostream>

#include "eventSerializer.h"
#include "parsingFunctions.h"

namespace smartCampus
{

void EventSerializer::SerializeHeader(const Event& _event, ProtocolMsg& _msg) const
{
	_msg.m_topic = "event";
	_msg.m_values.push_back(ParsingFunctions::GetPair("type", _event->m_topic));
	_msg.m_values.push_back(ParsingFunctions::GetPair("topic", _event->m_type));
	_msg.m_values.push_back(ParsingFunctions::GetPair("section", _event->m_section));
	_msg.m_values.push_back(ParsingFunctions::GetPair("floor", _event->m_floor));
	_msg.m_values.push_back(ParsingFunctions::GetPair("room", _event->m_room));
}

ProtocolMsg EventSerializer::Serialize(const Event& _event) const
{
	ProtocolMsg newMsg;
	
	SerializeHeader(_event, newMsg);
	
	newMsg.m_values.push_back(_event->SerializePayload());
	
	return newMsg;
}

}
