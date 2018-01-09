#ifndef __PROTOCOL_COMM_SOCKET_H__
#define __PROTOCOL_COMM_SOCKET_H__

#include <tr1/memory>

#include "socket.h"
#include "commSocket.h"
#include "protocol.h"
#include "protocolMsg.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<netcpp::CommSocket> CommSocketPtr;
typedef std::tr1::shared_ptr<Protocol> ProtocolPtr;

class ProtocolCommSocket: public netcpp::Socket
{
public:
	ProtocolCommSocket(const char* _ip, int _port, ProtocolPtr _protocol);
	ProtocolCommSocket(CommSocketPtr _socket, ProtocolPtr _protocol);
	//virtual ~ProtocolCommSocket();
	
	void Disconnect();
	void Send(const ProtocolMsg& _msg, netcpp::CommSocket::MsgFlag _flags = netcpp::CommSocket::e_noFlag);
	ProtocolMsg Recv(netcpp::CommSocket::MsgFlag _flags = netcpp::CommSocket::e_noFlag);
	void SendResponse(const std::string& _type, netcpp::CommSocket::MsgFlag _flag = netcpp::CommSocket::e_noFlag);
	
	int GetId() const;
	
	//socket_t GetNativeHandler();

protected:
	//socket_t m_socket;

private:
	/* data */
	CommSocketPtr m_commSocket;
	ProtocolPtr m_protocol;
};

inline void ProtocolCommSocket::Disconnect()
{
	m_commSocket->Disconnect();
}

inline int ProtocolCommSocket::GetId() const
{
	return m_commSocket->GetId();
}

}
#endif /* __PROTOCOL_COMM_SOCKET_H__ */

