#include <stdexcept>

#include "eventListenerHandler.h"
#include "protocolListenerSocket.h"

namespace smartCampus
{

EventListenerHandler::EventListenerHandler(ServerPtr _server, EventCommHandlerPtr _handler):
	m_server(_server)
,	m_eventHandler(_handler){}

netcpp::EventStatus EventListenerHandler::HandleEvent(netcpp::SocketPtr _socket)
{
	PrototcolListenerSocket* listenSocket = static_cast<PrototcolListenerSocket*>(_socket.get());
	
	try
	{
		while(true)
		{
			netcpp::SocketPtr newSocket = listenSocket->Accept();
			m_server->AddSocket(newSocket, m_eventHandler);
		}
	}
	catch(const std::underflow_error& _err){}
	
	return netcpp::e_statusOk;
}

}
