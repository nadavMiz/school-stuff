#ifndef __EVENT_LISTENER_HANDLER_H__
#define __EVENT_LISTENER_HANDLER_H__

#include <tr1/memory>

#include "server.h"
#include "ihandler.h"
#include "eventCommHandler.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<netcpp::Server> ServerPtr;
typedef std::tr1::shared_ptr<EventCommHandler> EventCommHandlerPtr;

class EventListenerHandler: public netcpp::IHandler
{
public:
	EventListenerHandler(ServerPtr _server, EventCommHandlerPtr _handler);
	//virtual ~EventListenerHandler();
	
	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);
	//virtual EventStatus HandleError(SocketPtr _socket);

private:
	/* data */
	ServerPtr m_server;
	EventCommHandlerPtr m_eventHandler;
	
};

}
#endif /* __EVENT_LISTENER_HANDLER_H__ */

