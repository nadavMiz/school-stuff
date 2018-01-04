#ifndef INT_EVENT_FACTORY_H
#define INT_EVENT_FACTORY_H

#include "ieventFactory.h"
#include "event.h"
#include "intEvent.h"
#include "protocolMsg.h"

using namespace smartCampus;

namespace nadavElectric
{

class IntEventFactory: public IEventFactory
{
public:
	//IntEventFactory();
	virtual ~IntEventFactory();

	virtual Event CreateEvent(const ProtocolMsg& _msg);
	
private:
	void ParseKeyValue(const std::string& _str, std::string& _key, std::string& _value) const;
	void InsertEventHeaderData(const std::string& _str, IntEvent* _event) const;

};

}	

#endif /* INT_EVENT_FACTORY_H */

