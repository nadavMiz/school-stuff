#ifndef REGISTRATION_HANDLER_H
#define REGISTRATION_HANDLER_H

#include "ihandler.h"
#include "networkAgent.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<NetworkAgent> NetworkAgentPtr;

class RegistrationHandler: public netcpp::IHandler
{
public:
	RegistrationHandler();
	virtual ~RegistrationHandler();

	//virtual EventStatus HandleError(SocketPtr _socket);
	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);
	
private:
	std::map<std::string, NetworkAgentPtr> m_networkAgents;
};

}
#endif /* REGISTRATION_HANDLER_H */

