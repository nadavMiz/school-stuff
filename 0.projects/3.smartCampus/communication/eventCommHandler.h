#ifndef EVENT_COMM_HANDLER_H
#define EVENT_COMM_HANDLER_H

#include <tr1/memory>

#include "ihandler.h"
#include "eventFactoryDispatcher.h"
#include "event.h"
#include "hub.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<IEventFactory> IEventFactoryPtr;

class EventCommHandler: public netcpp::IHandler
{
public:
	EventCommHandler(Hub* _hub);
	virtual ~EventCommHandler();
	
	//virtual EventStatus HandleError(SocketPtr _socket);
	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);

private:
	/* data */
	EventFactoryDispatcher m_factoryDispatcher;
	Hub* m_hub;
	
};

}
#endif /* EVENT_COMM_HANDLER_H */

