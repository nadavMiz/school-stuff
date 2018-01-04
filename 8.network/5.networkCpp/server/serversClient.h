#ifndef __SERVERS_CLIENT_H__
#define __SERVERS_CLIENT_H__

#include <tr1/memory>

#include "commSocket.h"
#include "timeValue.h"
#include "serverSocket.h"

typedef std::tr1::shared_ptr<netcpp::ServerSocket> SocketPtr;

namespace netcpp
{

class ServersClient
{
friend class Server;

public:
	ServersClient(SocketPtr _socket, const TimeValue& _timeOut);
	int Send(void* _data, std::size_t _size, CommSocket::MsgFlag _flags = CommSocket::e_noFlag);
	int Recv(void* _data, std::size_t _size, CommSocket::MsgFlag _flags = CommSocket::e_noFlag);
	int GetId();
	void Disconnect();
	
private:
	SocketPtr m_socket;
	TimeValue m_timeOut;
	bool m_isActive;
};

inline int ServersClient::GetId()
{
	return m_socket->GetId();
}

inline void ServersClient::Disconnect()
{
	m_socket->Disconnect();
	m_isActive = false;
}

}

#endif /* __SERVERS_CLIENT_H__ */

