#ifndef DEFAULT_EVENT_H
#define DEFAULT_EVENT_H

#include <map>

#include "eventImp.h"

class DefaultEvent: public EventImp
{
public:
	//DefaultEvent(); default CTOR
	virtual ~DefaultEvent(){}
	// using default copy CTOR and assignment operator
	
	//virtual std::string SerializePayload() const;
	
	//string m_type;
	//string m_room;
	//string m_section;
	//unsigned int m_floor;
	std::map<std::string, std::string> m_payload;
};

#endif /* DEFAULT_EVENT_H */

