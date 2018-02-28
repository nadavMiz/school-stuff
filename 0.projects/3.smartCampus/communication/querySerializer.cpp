#include "querySerializer.h"
#include "parsingFunctions.h"
#include "query.h"
#include "protocolMsg.h"

namespace smartCampus
{

void QuerySerializer::InsertPair(const std::string& _key, const std::string& _value, ProtocolMsg& _msg) const
{
	if(_value != "ALL")
	{
		_msg.m_values.push_back(ParsingFunctions::GetPair(_key, _value));
	}	
}

void QuerySerializer::Serialize(const Query& _query, ProtocolMsg& _msg) const
{	
	//always in message
	_msg.m_values.push_back(ParsingFunctions::GetPair("section", _query.m_section));
	_msg.m_values.push_back(ParsingFunctions::GetPair("topic", _query.m_topic));
	
	//not always in message
	InsertPair("floor", _query.m_floor, _msg);
	InsertPair("room", _query.m_room, _msg);
}

}
