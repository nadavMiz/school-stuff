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
	ProtocolCommSocket(CommSocketPtr _socket, ProtocolPtr _protocol);
	//virtual ~ProtocolCommSocket();
	
	void Disconnect();
	void Send(const ProtocolMsg& _msg, netcpp::CommSocket::MsgFlag _flags = netcpp::CommSocket::e_noFlag);
	ProtocolMsg Recv(netcpp::CommSocket::MsgFlag _flags = netcpp::CommSocket::e_noFlag);
	int GetId() const;

private:
	/* data */
	CommSocketPtr m_socket;
	ProtocolPtr m_protocol;
};

inline void ProtocolCommSocket::Disconnect()
{
	m_socket->Disconnect();
}

inline int ProtocolCommSocket::GetId() const
{
	return m_socket->GetId();
}

}
#endif /* __PROTOCOL_COMM_SOCKET_H__ */

