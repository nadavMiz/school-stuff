#ifndef IEVENT_FACTORY_H
#define IEVENT_FACTORY_H

#include <string>

#include "uncopyable.h"
#include "event.h"
#include "protocolMsg.h"

namespace smartCampus
{

class IEventFactory: private Uncopyable
{
public:
	virtual ~IEventFactory() = 0;
	
	virtual Event CreateEvent(const ProtocolMsg& _msg) = 0;
};

inline IEventFactory::~IEventFactory(){}

}
#endif /* EVENT_FACTORY_H */

