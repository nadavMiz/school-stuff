#include "protocolCommSocket.h"
#include "clientSocket.h"

namespace smartCampus
{

const std::size_t MAX_MSG_SIZE = 4096;

ProtocolCommSocket::ProtocolCommSocket(const char* _ip, int _port, ProtocolPtr _protocol):
	m_commSocket(new netcpp::ClientSocket(_ip, _port))
,	m_protocol(_protocol)
{
	m_socket = m_commSocket->GetNativeHandler();
}

ProtocolCommSocket::ProtocolCommSocket(CommSocketPtr _socket, ProtocolPtr _protocol):
	m_commSocket(_socket)
,	m_protocol(_protocol)
{
	m_socket = m_commSocket->GetNativeHandler();
}

void ProtocolCommSocket::Send(const ProtocolMsg& _msg, netcpp::CommSocket::MsgFlag _flags)
{
	std::string msg = m_protocol->CreateMsg(_msg);
	m_commSocket->Send(msg.c_str(), msg.size() + 1, _flags);
}

ProtocolMsg ProtocolCommSocket::Recv(netcpp::CommSocket::MsgFlag _flags)
{
	char data[MAX_MSG_SIZE];
	std::size_t count = m_commSocket->Recv(data, MAX_MSG_SIZE, _flags);
	
	return m_protocol->ParseMessage(data, count);
}

const std::string& ProtocolCommSocket::RecvResponse(netcpp::CommSocket::MsgFlag _flags)
{
	char data[MAX_MSG_SIZE];
	std::size_t count = m_commSocket->Recv(data, MAX_MSG_SIZE, _flags);
	
	return m_protocol->ParseResponse(data, count);
}

void ProtocolCommSocket::SendResponse(const std::string& _type, netcpp::CommSocket::MsgFlag _flag)
{
	std::string response = m_protocol->GetResponse(_type);
	m_commSocket->Send(response.c_str(), response.size() + 1, _flag);
}

}
