#ifndef __PROTOCOL_LISTENER_SOCKET_H__
#define __PROTOCOL_LISTENER_SOCKET_H__

#include <tr1/memory>

#include "socket.h"
#include "listenSocket.h"
#include "protocol.h"
#include "protocolCommSocket.h"

namespace smartCampus
{

class PrototcolListenerSocket: public netcpp::Socket
{

typedef std::tr1::shared_ptr<Protocol> ProtocolPtr;

public:
	PrototcolListenerSocket(int _port, ProtocolPtr _protocol, std::size_t _backlogSize = netcpp::ListenSocket::DEFAULT_BACKLOG_SIZE);
	//virtual ~PrototcolListenerSocket();

	void SetNoBlock();
	std::tr1::shared_ptr<ProtocolCommSocket> Accept();
	void CloseSocket();
	//socket_t GetNativeHandler();

private:
	/* data */
	netcpp::ListenSocket m_socket;
	ProtocolPtr m_protocol;
};

inline void PrototcolListenerSocket::SetNoBlock()
{
	m_socket.SetNoBlock();
}

inline void PrototcolListenerSocket::CloseSocket()
{
	m_socket.CloseSocket();
}

}
#endif /* __PROTOCOL_LISTENER_SOCKET_H__ */

