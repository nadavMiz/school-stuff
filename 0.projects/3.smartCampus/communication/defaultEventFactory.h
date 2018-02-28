#ifndef DEFAULT_EVENT_FACTORY_H
#define DEFAULT_EVENT_FACTORY_H

#include "ieventFactory.h"
#include "event.h"
#include "defaultEvent.h"
#include "protocolMsg.h"

namespace smartCampus
{

class DefaultEventFactory: public IEventFactory
{
public:
	//DefaultEventFactory();
	virtual ~DefaultEventFactory();

	virtual Event CreateEvent(const ProtocolMsg& _msg);
	
private:
	void ParseKeyValue(const std::string& _str, std::string& _key, std::string& _value) const;
	bool InsertEventHeaderData(const std::string& _str, DefaultEvent* _event) const;
	void InsertPayloadValue(const std::string& _str, DefaultEvent* _event) const;
	
};

}
#endif /* DEFAULT_EVENT_FACTORY_H */

