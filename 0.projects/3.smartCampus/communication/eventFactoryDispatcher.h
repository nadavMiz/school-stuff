#ifndef EVENT_FCTORY_DISPATCHER_H
#define EVENT_FCTORY_DISPATCHER_H

#include "ieventFactory.h"

#include <map>
#include <string>
#include <tr1/memory>

namespace smartCampus
{

typedef std::tr1::shared_ptr<IEventFactory> IEventFactoryPtr;

class EventFactoryDispatcher
{
public:
	EventFactoryDispatcher();
	//~EventFactoryDispatcher(); using default DTOR
	Event CreateEvent(const ProtocolMsg& _msg);

private:
	std::string GetTopic(const std::string& _str) const;

private:
	/* data */
	std::map<std::string, IEventFactoryPtr > m_factories;
	IEventFactoryPtr m_defaultFactory;
};

}
#endif /* EVENT_FCTORY_DISPATCHER_H */

