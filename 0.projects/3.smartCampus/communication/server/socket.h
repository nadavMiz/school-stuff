#ifndef SOCKET_H
#define SOCKET_H

#include "socket_t.h"

namespace netcpp
{

class Socket
{
	public:
		//Socket();
		virtual ~Socket() = 0;
		
		const Socket_t& GetNativeHandler() const;

	protected:
		/* data */
		Socket_t m_socket;
};

inline Socket::~Socket(){}

inline const Socket_t& Socket::GetNativeHandler() const
{
	return m_socket;
}

}
#endif /* SOCKET_H */

