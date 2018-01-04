#ifndef EVENT_COMM_HANDLER_H
#define EVENT_COMM_HANDLER_H

#include <tr1/memory>

#include "ihandler.h"
#include "eventFactoryDispatcher.h"
#include "event.h"
#include "hub.h"
#include "protocol.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<IEventFactory> IEventFactoryPtr;
typedef std::tr1::shared_ptr<Protocol> ProtocolPtr;

class EventCommHandler: public netcpp::IHandler
{
public:
	EventCommHandler(ProtocolPtr _protocol, Hub* _hub);
	virtual ~EventCommHandler();
	
	//virtual EventStatus HandleError(SocketPtr _socket);
	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);

private:
	/* data */
	EventFactoryDispatcher m_factoryDispatcher;
	ProtocolPtr m_protocol;
	Hub* m_hub;
	
};

}
#endif /* EVENT_COMM_HANDLER_H */

