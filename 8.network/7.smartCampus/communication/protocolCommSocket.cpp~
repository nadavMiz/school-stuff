#include "protocolCommSocket.h"

namespace smartCampus
{

const std::size_t MAX_MSG_SIZE = 4096;

ProtocolCommSocket::ProtocolCommSocket(CommSocketPtr _socket, ProtocolPtr _protocol):
	m_socket(_socket)
,	m_protocol(_protocol){}

void ProtocolCommSocket::Send(const ProtocolMsg& _msg, netcpp::CommSocket::MsgFlag _flags)
{
	std::string msg = m_protocol->CreateMsg(_msg);
	m_socket->Send(msg.c_str(), msg.size() + 1, _flags);
}

ProtocolMsg ProtocolCommSocket::Recv(netcpp::CommSocket::MsgFlag _flags)
{
	char data[MAX_MSG_SIZE];
	std::size_t count = m_socket->Recv(data, MAX_MSG_SIZE, _flags);
	
	return m_protocol->ParseMessage(data, count);
}

}
