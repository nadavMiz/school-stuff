#ifndef __MASTER_HANDLER_H__
#define __MASTER_HANDLER_H__

#include "ihandler.h"
#include "ireactor.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<IReactor> ReactorPtr;

class MasterSocketHandler: public IHandler
{
public:
	MasterSocketHandler(ReactorPtr _reactor, IHandlerPtr _handler);
	virtual ~MasterSocketHandler();
	virtual EventStatus HandleError(SocketPtr _socket);
	virtual EventStatus HandleEvent(SocketPtr _socket);
	
private:
	/* data */
	ReactorPtr m_reactor;
	IHandlerPtr m_handler;
	
private:
	void LoadNewClients(SocketPtr _socket);
};

}
#endif /* __MASTER_HANDLER_H__ */

