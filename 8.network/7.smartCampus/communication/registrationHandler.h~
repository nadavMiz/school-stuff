#ifndef REGISTRATION_HANDLER_H
#define REGISTRATION_HANDLER_H

#include <tr1/memory>
#include <map>

#include "hub.h"
#include "ihandler.h"
#include "networkAgent.h"
#include "protocol.h"
#include "protocolMsg.h"
#include "registrarConector.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<NetworkAgent> NetworkAgentPtr;
typedef std::tr1::shared_ptr<RegistrarConnector> RegistrarConectorPtr;
typedef std::tr1::shared_ptr<Protocol> ProtocolPtr;

class RegistrationHandler: public netcpp::IHandler
{
public:
	RegistrationHandler(Hub* _hub, RegistrarConectorPtr _registrar, ProtocolPtr _protocol);
	//virtual ~RegistrationHandler();

	//virtual EventStatus HandleError(SocketPtr _socket);
	virtual netcpp::EventStatus HandleEvent(netcpp::SocketPtr _socket);
	
private:
	Hub* m_hub;
	RegistrarConectorPtr m_registrar;
	ProtocolPtr m_protocol;
	std::map<std::string, NetworkAgentPtr> m_networkAgents;
	
private:
	void HandleRequest(const ProtocolMsg& _msg);
	void SubcribeClient(const ProtocolMsg& _msg);
	void UnsubscribeClient(const ProtocolMsg& _msg);
	Query ParseMsg(const ProtocolMsg& _msg) const;
	NetworkAgentPtr GetNetworkAgent(const std::string& _section);
	NetworkAgentPtr CreateNetworkAgent(const std::string& _section);
	
	static void ParseMsgField(const std::string& _value, Query* _query);
};

}
#endif /* REGISTRATION_HANDLER_H */

