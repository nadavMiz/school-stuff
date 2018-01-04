#ifndef __SERVER_H__
#define __SERVER_H__

#include <tr1/memory>

#include "ihandler.h"
#include "ireactor.h"
#include "iDispatcher.h"
#include "timeValue.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<IHandler> IHandlerPtr;
typedef std::tr1::shared_ptr<IReactor> ReactorPtr;
typedef std::tr1::shared_ptr<IDispatcher> IDispatcherPtr;
typedef std::tr1::shared_ptr<Socket> SocketPtr;

class Server
{
friend class MasterSocketHandler;

public:
	Server(int _port, IHandlerPtr _handler, const TimeValue& _timeOut, std::size_t _backlogSize = 32);
	//~Server(); default DTOR
	void ServerRoutine();

private:
	/* data */
	ReactorPtr m_reactor;
	IDispatcherPtr m_dispatcher;
};

}
#endif /* __SERVER_H__ */

