#include <stdexcept> //std::exception

#include "eventCommHandler.h"
#include "protocolCommSocket.h"
#include "event.h"
#include "netExceptions.h" //netcpp::BadRequest_error

namespace smartCampus
{

EventCommHandler::EventCommHandler(Hub* _hub):
	m_hub(_hub){}

EventCommHandler::~EventCommHandler(){}

netcpp::EventStatus EventCommHandler::HandleEvent(netcpp::SocketPtr _socket)
{
	ProtocolCommSocket* socket = static_cast<ProtocolCommSocket*>(_socket.get());
	std::string response = "ok";
	
	try
	{
		ProtocolMsg msg = socket->Recv();
		Event event = m_factoryDispatcher.CreateEvent(msg);
		m_hub->SendEvent(event);
	}
	catch(const netcpp::BadRequest_error& _err)
	{
		response = "badRequest";
	}
	catch(const netcpp::BrokenPipe_error& _err)
	{
		return netcpp::e_statusToDelete;
	}
	catch(const std::exception& _err)
	{
		response = "error";
	}
	
	socket->SendResponse(response);
	return netcpp::e_statusOk;
}



}
