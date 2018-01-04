#ifndef __SERVER_H__
#define __SERVER_H__

#include <tr1/memory>

#include "ihandler.h"
#include "ireactor.h"
#include "iDispatcher.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<IHandler> IHandlerPtr;
typedef std::tr1::shared_ptr<IReactor> ReactorPtr;
typedef std::tr1::shared_ptr<IDispatcher> IDispatcherPtr;
typedef std::tr1::shared_ptr<Socket> SocketPtr;

class Server
{

public:
	Server();
	//~Server(); default DTOR
	void AddSocket(SocketPtr _socket, IHandlerPtr _handler);
	void RemoveSocket(SocketPtr _socket);
	void ServerRoutine();
	void ShutDown();

private:
	/* data */
	ReactorPtr m_reactor;
	IDispatcherPtr m_dispatcher;
};

inline void Server::AddSocket(SocketPtr _socket, IHandlerPtr _handler)
{
	m_reactor->AddSocket(_socket, _handler);
}

inline void Server::RemoveSocket(SocketPtr _socket)
{
	m_reactor->RemoveSocket(_socket);
}

}
#endif /* __SERVER_H__ */

