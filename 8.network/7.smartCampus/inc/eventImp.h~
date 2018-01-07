#ifndef __EVENT_IMP_H__
#define __EVENT_IMP_H__

#include <string>

#include "payload.h"

class EventImp
{
public:
	virtual ~EventImp(){}
	virtual std::string SerializePayload() const{return std::string();}

	std::string m_type;
	std::string m_topic;
	std::string m_room;
	std::string m_section;
	unsigned int m_floor;
	
	static const char m_keyValueDelim = ':';
};

#endif /* __PAYLOAD_H__ */
