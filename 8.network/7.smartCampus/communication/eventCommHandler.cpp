#include "eventCommHandler.h"
#include "commSocket.h"
#include "event.h"

namespace smartCampus
{

const std::size_t MAX_MSG_SIZE = 4096;

EventCommHandler::EventCommHandler(ProtocolPtr _protocol, Hub* _hub):
	m_protocol(_protocol)
,	m_hub(_hub){}

EventCommHandler::~EventCommHandler(){}

netcpp::EventStatus EventCommHandler::HandleEvent(netcpp::SocketPtr _socket)
{
	char buffer[MAX_MSG_SIZE];
	
	std::size_t count = static_cast<netcpp::CommSocket*>(_socket.get())->Recv(buffer, MAX_MSG_SIZE);
	
	ProtocolMsgPtr msg = m_protocol->ParseMessage(buffer, count);
	
	Event event = m_factoryDispatcher.CreateEvent(*msg);
	
	m_hub->SendEvent(event);
	
	return netcpp::e_statusOk;
}



}
