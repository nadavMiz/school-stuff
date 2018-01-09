#ifndef __REGISTRATION_LISTENER_HANDLER_H__
#define __REGISTRATION_LISTENER_HANDLER_H__

#include "ihandler.h"
#include "server.h"
#include "registrationHandler.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;

class RegistrationListenerHandler: public netcpp::IHandler
{
public:
	RegistrationListenerHandler(netcpp::Server* _server, RegistrationHandlerPtr _handler);
	//virtual ~RegistrationListenerHandler();

	//virtual EventStatus HandleError(SocketPtr _socket);
	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);

private:
	/* data */
	netcpp::Server* m_server;
	RegistrationHandlerPtr m_registrationHandler;
};

}
#endif /* __REGISTRATION_LISTENER_HANDLER_H__ */

