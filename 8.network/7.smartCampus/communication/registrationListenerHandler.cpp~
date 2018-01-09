#include "registrationListenerHandler.h"
#include "protocolListenerSocket.h"

namespace smartCampus
{

RegistrationListenerHandler::RegistrationListenerHandler(netcpp::Server* _server, RegistrationHandlerPtr _handler):
	m_server(_server)
,	m_registrationHandler(_handler){}
	
netcpp::EventStatus RegistrationListenerHandler::HandleEvent(netcpp::SocketPtr _socket)
{
	PrototcolListenerSocket* listenSocket = static_cast<PrototcolListenerSocket*>(_socket.get());
	
	try
	{
		while(true)
		{
			netcpp::SocketPtr newSocket = listenSocket->Accept();
			m_server->AddSocket(newSocket, m_registrationHandler);
		}
	}
	catch(const std::underflow_error& _err){}
	
	return netcpp::e_statusOk;
}

}
