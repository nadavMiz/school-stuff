#include "protocolListenerSocket.h"

namespace smartCampus
{

PrototcolListenerSocket::PrototcolListenerSocket(int _port, ProtocolPtr _protocol, std::size_t _backlogSize):
	m_listenSocket(_port, _backlogSize)
,	m_protocol(_protocol)
{
	m_socket = m_listenSocket.GetNativeHandler();
}

std::tr1::shared_ptr<ProtocolCommSocket> PrototcolListenerSocket::Accept()
{
	std::tr1::shared_ptr<netcpp::CommSocket> socket = m_listenSocket.Accept();
	
	return std::tr1::shared_ptr<ProtocolCommSocket>(new ProtocolCommSocket(socket, m_protocol));
}

}
