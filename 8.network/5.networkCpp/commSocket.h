#ifndef COM_SOCKET_H
#define COM_SOCKET_H

#include <cstddef> /* std::size_t */
#include <vector> /* vector */

#include "socket.h"

namespace netcpp
{

class CommSocket: public Socket
{

public:
	enum MsgFlag
    {
	    e_noFlag = 0,
	    e_noWait
    };


	CommSocket(){}
	virtual ~CommSocket() = 0;
	
	void Disconnect();
	std::size_t Send(void* _data, std::size_t _size, MsgFlag _flags = e_noFlag);
	std::size_t Recv(void* _data, std::size_t _size, MsgFlag _flags = e_noFlag);
	int GetId() const;
	//socket_t GetNativeHandler();

protected:
	int GetFlag(MsgFlag _flag) const;

protected:
	/* data */
	//Socket_t m_socket;

private:
	CommSocket(const CommSocket& _socket); // uncopyable
	CommSocket& operator=(const CommSocket& _socket); // uncopyable
	void MsgErrorHandler();
	
private:
	static std::vector<int> m_flags;
};

inline int CommSocket::GetId() const
{
	return m_socket;
}

}
#endif /* COM_SOCKET_H */

