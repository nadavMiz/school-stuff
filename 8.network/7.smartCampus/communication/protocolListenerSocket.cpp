#include "protocolListenerSocket.h"

namespace smartCampus
{

PrototcolListenerSocket::PrototcolListenerSocket(int _port, ProtocolPtr _protocol, std::size_t _backlogSize):
	m_socket(_port, _backlogSize)
,	m_protocol(_protocol){}

std::tr1::shared_ptr<ProtocolCommSocket> PrototcolListenerSocket::Accept()
{
	std::tr1::shared_ptr<netcpp::CommSocket> socket = m_socket.Accept();
	
	return std::tr1::shared_ptr<ProtocolCommSocket>(new ProtocolCommSocket(socket, m_protocol));
}

}
