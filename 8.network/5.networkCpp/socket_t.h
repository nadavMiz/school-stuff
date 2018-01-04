#ifndef SOCKET_T_H
#define SOCKET_T_H

class Socket_t
{
public:
	Socket_t();
	explicit Socket_t(int _fd);
	
	operator int() const;
	void SetSocket(int _fd);

private:
	/* data */
	int m_socket;
	
};

inline Socket_t::Socket_t(): m_socket(0){}

inline Socket_t::Socket_t(int _fd): m_socket(_fd) {}

inline Socket_t::operator int() const
{
	return m_socket;
}

inline void Socket_t::SetSocket(int _fd)
{
	m_socket = _fd;
}

#endif /* SOCKET_T_H */

