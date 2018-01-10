#ifndef __REGISTRATION_LISTENER_HANDLER_H__
#define __REGISTRATION_LISTENER_HANDLER_H__

#include "ihandler.h"
#include "server.h"
#include "registrationHandler.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<netcpp::Server> ServerPtr;
typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;

class RegistrationListenerHandler: public netcpp::IHandler
{
public:
	RegistrationListenerHandler(ServerPtr _server, RegistrationHandlerPtr _handler);
	//virtual ~RegistrationListenerHandler();

	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);
	//virtual EventStatus HandleError(SocketPtr _socket);

private:
	/* data */
	ServerPtr m_server;
	RegistrationHandlerPtr m_registrationHandler;
};

}
#endif /* __REGISTRATION_LISTENER_HANDLER_H__ */

